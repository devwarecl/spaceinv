
#include "DeviceGL.hpp"
#include <cassert>

#include "xe/gfx/gl3/TextureGL.hpp"
#include "xe/gfx/gl3/Util.hpp"

#include "spaceinv/ModelPart.hpp"

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
			{GLFW_OPENGL_DEBUG_CONTEXT, 1},
			
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

		XE_GL_CHECK_ERROR();

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

		XE_GL_CHECK_ERROR();
	}

	void DeviceGL::endFrame() {
		glFlush();
		glfwSwapBuffers(m_window);

		XE_GL_CHECK_ERROR();
	}

	int DeviceGL::getKey(int key) const {
		return ::glfwGetKey(m_window, key);
	}

	void DeviceGL::setProgram(Program *program) {
		m_program = static_cast<ProgramGL*>(program);

		glUseProgram(m_program->getId());

		XE_GL_CHECK_ERROR();
	}

	void DeviceGL::setMaterial(Material *material) {

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

		XE_GL_CHECK_ERROR();

		// apply texturing
		const auto &layers = material->layers;

		for (size_t i=0; i<layers.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);

			if (layers[i].texture) {
				auto textureGL = static_cast<TextureGL*>(layers[i].texture);

				glBindTexture(textureGL->getTarget(), textureGL->getId());

			} else {
				GLenum target = GL_TEXTURE_2D;

				//if (m_material && i < m_material->layers.size()) {
				//	auto textureGL = static_cast<TextureGL*>(m_material->layers[i].texture);
				//	target = textureGL->getTarget();
				//}

				glBindTexture(target, 0);
			}
		}

		XE_GL_CHECK_ERROR();

		// set the uniforms data
		this->setUniform(material->format, material->getUniformPointer());

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
		XE_GL_CHECK_ERROR();
	}

	void DeviceGL::setUniformMatrix(int location, int total, bool transpose, float *values) {
		glUniformMatrix4fv(location, total, transpose?GL_TRUE:GL_FALSE, values);
		XE_GL_CHECK_ERROR();
	}

	void DeviceGL::setUniform(const UniformDescriptor &desc, const void* uniform) {
		assert(desc.dim>=1);
		assert(desc.dim<=4);
		assert(desc.count>0);

		XE_GL_CHECK_ERROR();

		switch (desc.type) {
		case xe::DataType::Int32:
			switch (desc.dim) {

			case 1:
				if (desc.count==1) {
					glUniform1i(desc.location, *(const GLint*)uniform);
				} else {
					glUniform1iv(desc.location, desc.count, (const GLint*)uniform);
				};
				XE_GL_CHECK_ERROR();  
				break;

			case 2: 
				if (desc.count==1) {
					GLint v0 = *((const GLint*)(uniform) + 0);
					GLint v1 = *((const GLint*)(uniform) + 1);

					glUniform2i(desc.location, v0, v1);
				} else {
					glUniform2iv(desc.location, desc.count, (const GLint*)uniform);
				};
				XE_GL_CHECK_ERROR();  
				break;

			case 3: 
				if (desc.count==1) {
					GLint v0 = *((const GLint*)(uniform) + 0);
					GLint v1 = *((const GLint*)(uniform) + 1);
					GLint v2 = *((const GLint*)(uniform) + 2);

					glUniform3i(desc.location, v0, v1, v2);
				} else {
					glUniform3iv(desc.location, desc.count, (const GLint*)uniform);
				};
				XE_GL_CHECK_ERROR();  
				break;

			case 4: 
				if (desc.count==1) {
					GLint v0 = *((const GLint*)(uniform) + 0);
					GLint v1 = *((const GLint*)(uniform) + 1);
					GLint v2 = *((const GLint*)(uniform) + 2);
					GLint v3 = *((const GLint*)(uniform) + 3);

					glUniform4i(desc.location, v0, v1, v2, v3);
				} else {
					glUniform4iv(desc.location, desc.count, (const GLint*)uniform);
				};
				XE_GL_CHECK_ERROR();  
				break;
			}

			break;
			
		case xe::DataType::Float32:
			switch (desc.dim) {

			case 1:
				if (desc.count==1) {
					glUniform1f(desc.location, *(const GLfloat*)uniform);
				} else {
					glUniform1fv(desc.location, desc.count, (const GLfloat*)uniform);
				};
				XE_GL_CHECK_ERROR();  
				break;

			case 2: 
				if (desc.count==1) {
					GLfloat v0 = *((const GLfloat*)(uniform) + 0);
					GLfloat v1 = *((const GLfloat*)(uniform) + 1);

					glUniform2f(desc.location, v0, v1);
				} else {
					glUniform2fv(desc.location, desc.count, (const GLfloat*)uniform);
				};
				XE_GL_CHECK_ERROR();  
				break;

			case 3: 
				if (desc.count==1) {
					GLfloat v0 = *((const GLfloat*)(uniform) + 0);
					GLfloat v1 = *((const GLfloat*)(uniform) + 1);
					GLfloat v2 = *((const GLfloat*)(uniform) + 2);

					glUniform3f(desc.location, v0, v1, v2);
				} else {
					glUniform3fv(desc.location, desc.count, (const GLfloat*)uniform);
				};
				XE_GL_CHECK_ERROR();  
				break;

			case 4: 
				if (desc.count==1) {
					GLfloat v0 = *((const GLfloat*)(uniform) + 0);
					GLfloat v1 = *((const GLfloat*)(uniform) + 1);
					GLfloat v2 = *((const GLfloat*)(uniform) + 2);
					GLfloat v3 = *((const GLfloat*)(uniform) + 3);

					glUniform4f(desc.location, v0, v1, v2, v3);
				} else {
					glUniform4fv(desc.location, desc.count, (const GLfloat*)uniform);
				};
				XE_GL_CHECK_ERROR();  
				break;
			}

			break;

		case xe::DataType::UInt32:
			switch (desc.dim) {

			case 1:
				if (desc.count==1) {
					glUniform1ui(desc.location, *(const GLuint*)uniform);
				} else {
					glUniform1uiv(desc.location, desc.count, (const GLuint*)uniform);
				};
				XE_GL_CHECK_ERROR();  
				break;

			case 2: 
				if (desc.count==1) {
					GLuint v0 = *((const GLuint*)(uniform) + 0);
					GLuint v1 = *((const GLuint*)(uniform) + 1);

					glUniform2ui(desc.location, v0, v1);
				} else {
					glUniform2uiv(desc.location, desc.count, (const GLuint*)uniform);
				};
				XE_GL_CHECK_ERROR();  
				break;

			case 3: 
				if (desc.count==1) {
					GLuint v0 = *((const GLuint*)(uniform) + 0);
					GLuint v1 = *((const GLuint*)(uniform) + 1);
					GLuint v2 = *((const GLuint*)(uniform) + 2);

					glUniform3ui(desc.location, v0, v1, v2);
				} else {
					glUniform3uiv(desc.location, desc.count, (const GLuint*)uniform);
				};
				XE_GL_CHECK_ERROR();  
				break;

			case 4: 
				if (desc.count==1) {
					GLuint v0 = *((const GLuint*)(uniform) + 0);
					GLuint v1 = *((const GLuint*)(uniform) + 1);
					GLuint v2 = *((const GLuint*)(uniform) + 2);
					GLuint v3 = *((const GLuint*)(uniform) + 3);

					glUniform4ui(desc.location, v0, v1, v2, v3);
				} else {
					glUniform4uiv(desc.location, desc.count, (const GLuint*)uniform);
				};
				XE_GL_CHECK_ERROR();  
				break;
			}

			break;

		default:
			assert(false);
		}
	}

	void DeviceGL::setUniform(const UniformFormat *format, const void *uniforms) {
		assert(uniforms);
		assert(format->attribs.size() > 0);

		// auto mat = static_cast<const ModelMaterial::Attributes*>(uniforms);

		auto uniform = static_cast<const std::uint8_t*>(uniforms);

		for (const UniformDescriptor &desc : format->attribs) {
			this->setUniform(desc, uniform);

			const size_t size = desc.getSize();

			uniform += size;
		}
	}
}}}
