#pragma once

#include "xe/DataType.hpp"
#include "xe/gfx/Texture.hpp"
#include "xe/gfx/ShaderType.hpp"
#include "xe/gfx/gl3/OpenGL.hpp"

#include <iostream>

namespace xe { namespace gfx { namespace gl3 {
	inline GLenum convertFormat(xe::gfx::PixelFormat pixelFormat) {
		switch (pixelFormat) {
		case PixelFormat::R8G8B8: return GL_RGB;
		case PixelFormat::R8G8B8A8: return GL_RGBA;
		case PixelFormat::R5G5B5A1: 
		case PixelFormat::R5G5B5X1:
			return GL_RGB5_A1;

		case PixelFormat::B8G8R8: return GL_BGR;
		case PixelFormat::B8G8R8A8: return GL_BGR;

		default: assert(false); 
		}

		return GLenum();
	}

	inline GLenum convertTarget(TextureType textureType) {
		switch (textureType) {
		case TextureType::Tex1D: return GL_TEXTURE_1D;
		case TextureType::Tex2D: return GL_TEXTURE_2D;
		case TextureType::Tex3D: return GL_TEXTURE_3D;
		case TextureType::TexCube: return GL_TEXTURE_CUBE_MAP;
		default: assert(false);
		}

		return GLenum();
	}

	inline GLenum convertCubeFace(TextureCubeSide face) {
		switch (face) {
		case TextureCubeSide::PosX: return GL_TEXTURE_CUBE_MAP_POSITIVE_X;
		case TextureCubeSide::PosY: return GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
		case TextureCubeSide::PosZ: return GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
		case TextureCubeSide::NegX: return GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
		case TextureCubeSide::NegY: return GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
		case TextureCubeSide::NegZ: return GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;
		default: assert(false);
		}

		return GLenum();
	}

	inline GLenum convertDataType(DataType dataType) {
		switch (dataType) {
		case DataType::UInt8:	return GL_UNSIGNED_BYTE;
		case DataType::UInt16:	return GL_UNSIGNED_SHORT;
		case DataType::UInt32:	return GL_UNSIGNED_INT;
		case DataType::Int8:	return GL_BYTE;
		case DataType::Int16:	return GL_SHORT;
		case DataType::Int32:	return GL_INT;
		case DataType::Float32:	return GL_FLOAT;
		default: assert(false);
		}

		return GLenum();
	}

	inline GLenum converShaderType(ShaderType shaderType) {
		switch (shaderType) {
		case ShaderType::Vertex: return GL_VERTEX_SHADER;
		case ShaderType::Fragment: return GL_FRAGMENT_SHADER;
		case ShaderType::Geometry: return GL_GEOMETRY_SHADER;
		default: assert(false);
		}

		return GLenum();
	}

	inline std::string convertErrorCode(GLenum errorCode) {
		switch (errorCode) {
			case GL_INVALID_ENUM:	return "GL_INVALID_ENUM";
			case GL_INVALID_VALUE:	return "GL_INVALID_VALUE";
			case GL_INVALID_OPERATION:	return "GL_INVALID_OPERATION";
			// case GL_STACK_OVERFLOW:	return "";
			// case GL_STACK_UNDERFLOW:	return "";
			case GL_OUT_OF_MEMORY:	return "GL_OUT_OF_MEMORY";
			case GL_INVALID_FRAMEBUFFER_OPERATION:	return "GL_INVALID_FRAMEBUFFER_OPERATION";
			// case GL_CONTEXT_LOST:	return "";
			// case GL_TABLE_TOO_LARGE:	return "";
			default: return "";
		}
	}

	inline void checkError(const std::string &file, const int line) {
#if defined(_DEBUG)
		GLenum error;

		while ( (error = glGetError()) != GL_NO_ERROR) {
			std::string str = convertErrorCode(error);
			std::cout << "OpenGL error '"<< str << "' ocurred at " << file << ":" << line << std::endl;
		}
#endif
	}

}}}

#define XE_GL_CHECK_ERROR() xe::gfx::gl3::checkError(__FILE__, __LINE__)
