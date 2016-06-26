
#include "DeviceGL.hpp"
#include <cassert>

#include "xe/gfx/gl3/TextureGL.hpp"
#include "xe/gfx/gl3/Util.hpp"

namespace xe { namespace gfx { namespace gl3  {
	void window_size_callback(GLFWwindow* m_window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	DeviceGL::DeviceGL() {
		::glfwInit();
    
		int hints[][2] = {
			// version
			{GLFW_CONTEXT_VERSION_MAJOR, 3},
			{GLFW_CONTEXT_VERSION_MINOR, 3},
			{GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE},
        
			// framebuffer
			{GLFW_RED_BITS, 8},
			{GLFW_GREEN_BITS, 8},
			{GLFW_BLUE_BITS, 8},
			{GLFW_ALPHA_BITS, 8} ,
			{GLFW_DEPTH_BITS,  24},
			{GLFW_STENCIL_BITS, 8}
		};
    
		for (auto hint : hints) {
			::glfwWindowHint(hint[0], hint[1]);
		}
		
		m_window = ::glfwCreateWindow(1024, 768, "test", nullptr, nullptr);
    
		glfwMakeContextCurrent(m_window);
        
		glbinding::Binding::useCurrentContext();
		glbinding::Binding::initialize(true);

		assert(glGetError() == GL_NO_ERROR);

		glfwSetWindowSizeCallback(m_window, window_size_callback);
	}

	DeviceGL::~DeviceGL() {
		::glfwDestroyWindow(m_window);
		::glfwTerminate();
	}

	void DeviceGL::pollEvents() {
		glfwPollEvents();
	}

    BufferPtr DeviceGL::createBuffer(const BufferType type, const std::size_t size, const void *data) { 
		GLenum target;

		switch (type) {
		case BufferType::Vertex: target=GL_ARRAY_BUFFER; break;
		case BufferType::Index: target=GL_ELEMENT_ARRAY_BUFFER; break;
		}

		GLenum usage = GL_DYNAMIC_DRAW;

		return std::make_unique<BufferGL>(target, usage, size, data);
	}

	TexturePtr DeviceGL::createTexture(const TextureDesc &desc, const PixelFormat sourceFormat, const DataType sourceType, const void* sourceData)   { 
		return std::make_unique<TextureGL>(desc, sourceFormat, sourceType, sourceData);
	}
	
	MeshPtr DeviceGL::createMesh(const MeshFormat &format, std::vector<BufferPtr> buffers)   { 
		return std::make_unique<MeshGL>(format, std::move(buffers));
	}

	ProgramPtr DeviceGL::createProgram(const std::list<ShaderSource> &sources)  { 
		ShaderGLVector shaders;
		for (const ShaderSource source : sources) {
			shaders.emplace_back(new ShaderGL(converShaderType(source.type), source.source));
		}

		return std::make_unique<ProgramGL>(std::move(shaders));
	}

	void DeviceGL::beginFrame(const ClearFlags flags, const ClearParams &params) {
		gl::ClearBufferMask clearFlags = GL_NONE_BIT;

		if (flags&ClearFlags::Color) {
			clearFlags |= GL_COLOR_BUFFER_BIT;
		}

		if (flags&ClearFlags::Depth) {
			clearFlags |= GL_DEPTH_BUFFER_BIT;
		}

		if (flags&ClearFlags::Stencil) {
			clearFlags |= GL_STENCIL_BUFFER_BIT;
		}

		glClearColor(params.color.x, params.color.y, params.color.z, params.color.w);
		glClearDepth(params.depth);
		glClearStencil(params.stencil);
		glClear(clearFlags);

		assert(glGetError() == GL_NO_ERROR);
	}

	void DeviceGL::endFrame() {
		glFlush();
		glfwSwapBuffers(m_window);

		assert(glGetError() == GL_NO_ERROR);
	}

	int DeviceGL::getKey(int key) const {
		return ::glfwGetKey(m_window, key);
	}

	void DeviceGL::setProgram(Program *program) {
		m_program = static_cast<ProgramGL*>(program);

		glUseProgram(m_program->getId());

		assert(glGetError() == GL_NO_ERROR);
	}

	void DeviceGL::setMaterial(Material *material) {
		if (m_material == material) {
			return;
		}

		// set rendering flags
		auto flags = material->flags;

		if (flags.isEnabled(Material::DepthTest)) {
			glEnable(GL_DEPTH_TEST);
		} else {
			glDisable(GL_DEPTH_TEST);
		}

		if (flags.isEnabled(Material::CullFace)) {
			glEnable(GL_CULL_FACE);
		} else {
			glDisable(GL_CULL_FACE);
		}

		if (flags.isEnabled(Material::Blending)) {
			glEnable(GL_BLEND);
		} else {
			glDisable(GL_BLEND);
		}

		assert(glGetError() == GL_NO_ERROR);

		// apply texturing
		const auto &layers = material->layers;

		for (size_t i=0; i<layers.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);

			if (layers[i].texture) {
				auto textureGL = static_cast<TextureGL*>(layers[i].texture);

				glBindTexture(textureGL->getTarget(), textureGL->getId());

			} else {
				GLenum target = GL_TEXTURE_2D;

				if (m_material && i < m_material->layers.size()) {
					auto textureGL = static_cast<TextureGL*>(m_material->layers[i].texture);
					target = textureGL->getTarget();
				}

				glBindTexture(target, 0);
			}
		}

		assert(glGetError() == GL_NO_ERROR);

		// set the uniforms data
		this->setUniform(material->format, material->uniforms);

		// change the current material
		m_material = material;
	}

	void DeviceGL::setMesh(Mesh *mesh) {
		m_mesh = static_cast<MeshGL*>(mesh);
	}

	void DeviceGL::render(Primitive primitive, size_t start, size_t count) {
		GLenum mode;

		glBindVertexArray(m_mesh->getId());

		switch (primitive) {
			case Primitive::PointList: mode=GL_POINTS; break;
			case Primitive::LineList: mode=GL_LINES; break;
			case Primitive::LineStrip: mode=GL_LINE_STRIP; break;
			case Primitive::LineLoop: mode=GL_LINE_LOOP; break;
			case Primitive::TriangleList: mode=GL_TRIANGLES; break;
			case Primitive::TriangleStrip: mode=GL_TRIANGLE_STRIP; break;
			case Primitive::TriangleFan: mode=GL_TRIANGLE_FAN; break;
		}

		if (m_mesh->isIndexed()) {
			//!TODO: Get the index datatype from the buffer format
			GLenum type = GL_UNSIGNED_INT;

			if (start==0) {
				glDrawElements(mode, count, type, nullptr);	
			} else {
				glDrawElementsBaseVertex(mode, count, type, nullptr, start);
			}
		} else {
			glDrawArrays(mode, start, count);
		}

		glBindVertexArray(0);
		assert(glGetError() == GL_NO_ERROR);
	}

	void DeviceGL::setUniform(const UniformDescriptor &desc, void* uniform) {
		assert(desc.count>=1);
		assert(desc.count<=4);

		switch (desc.type) {
		case xe::DataType::Int32:
			switch (desc.count) {
			case 1: glUniform1iv(desc.location, desc.size, (const GLint*)uniform); break;
			case 2: glUniform2iv(desc.location, desc.size, (const GLint*)uniform); break;
			case 3: glUniform3iv(desc.location, desc.size, (const GLint*)uniform); break;
			case 4: glUniform4iv(desc.location, desc.size, (const GLint*)uniform); break;
			}

			break;
			
		case xe::DataType::Float32:
			switch (desc.count) {
			case 1: glUniform1fv(desc.location, desc.size, (const GLfloat*)uniform); break;
			case 2: glUniform2fv(desc.location, desc.size, (const GLfloat*)uniform); break;
			case 3: glUniform3fv(desc.location, desc.size, (const GLfloat*)uniform); break;
			case 4: glUniform4fv(desc.location, desc.size, (const GLfloat*)uniform); break;
			}

			break;

		case xe::DataType::UInt32:
			switch (desc.count) {
			case 1: glUniform1uiv(desc.location, desc.size, (const GLuint*)uniform); break;
			case 2: glUniform2uiv(desc.location, desc.size, (const GLuint*)uniform); break;
			case 3: glUniform3uiv(desc.location, desc.size, (const GLuint*)uniform); break;
			case 4: glUniform4uiv(desc.location, desc.size, (const GLuint*)uniform); break;
			}

			break;

		default:
			assert(false);
		}

		assert(glGetError() == GL_NO_ERROR);
	}

	void DeviceGL::setUniform(const UniformFormat *format, void *uniforms) {
		assert(uniforms);
		assert(format->attribs.size() > 0);

		auto uniform = static_cast<std::uint8_t*>(uniforms);

		for (const UniformDescriptor &desc : format->attribs) {
			this->setUniform(desc, uniform);

			const size_t size = desc.getSize();

			uniform += size;
		}
	}
}}}
