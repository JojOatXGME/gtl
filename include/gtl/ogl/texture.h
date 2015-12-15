#ifndef TEXTURE_H
#define TEXTURE_H

#include <cassert>

#include <GL/glew.h>


namespace gtl {
namespace ogl {

class Texture final
{
public:
	enum class Target {
		T_1D = GL_TEXTURE_1D,
		T_2D = GL_TEXTURE_2D,
		T_3D = GL_TEXTURE_3D,
		T_1D_ARRAY = GL_TEXTURE_1D_ARRAY,
		T_2D_ARRAY = GL_TEXTURE_2D_ARRAY,
		T_RECTANGLE = GL_TEXTURE_RECTANGLE,
		T_CUBE_MAP = GL_TEXTURE_CUBE_MAP,
		T_CUBE_MAP_ARRAY = GL_TEXTURE_CUBE_MAP_ARRAY,
		T_BUFFER = GL_TEXTURE_BUFFER,
		T_2D_MULTISAMPLE = GL_TEXTURE_2D_MULTISAMPLE,
		T_2D_MULTISAMPLE_ARRAY = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
	};

	Texture(Target target);
	explicit Texture(GLuint textureName = 0) noexcept;
	~Texture() noexcept;

	Texture(Texture &&other) noexcept;
	Texture &operator = (Texture &&other) noexcept;
	explicit operator bool () const noexcept;

	void create(Target target);
	void reset(GLuint textureName = 0) noexcept;
	GLuint release() noexcept;

	GLuint get() const noexcept;
	void bind(GLuint unit) const;

	// TODO glTextureBuffer and glTextureBufferRange
	void storage(GLsizei levels, GLenum internalformat, GLsizei width);
	void storage(GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
	void storage(GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
	void storageMultisample(GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
	void storageMultisample(GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);

	void setSubImage(GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels);
	void setSubImage(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
	void setSubImage(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels);
	void setCompressedSubImage(GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data);
	void setCompressedSubImage(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data);
	void setCompressedSubImage(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data);

	// TODO glCopyTextureSubImage

	void getImage(GLint level, GLenum format, GLenum type, GLsizei bufSize, GLvoid *pixels) const;
	void getCompressedImage(GLint level, GLsizei bufSize, GLvoid *pixels) const;

	void setParameter(GLenum pname, GLfloat param);
	void setParameter(GLenum pname, const GLfloat *param);
	void setParameter(GLenum pname, GLint param);
	void setParameter(GLenum pname, const GLint *param);
	void setParameterI(GLenum pname, const GLint *params);
	void setParameterI(GLenum pname, const GLuint *params);

	// TODO getParameter
	// TODO getLevelParameter

	void generateMipmap();

private:
	Texture(const Texture &) = delete;
	Texture &operator=(const Texture &) = delete;

	GLuint mId;
};


inline Texture::Texture(Target target)
{
	this->create(target);
}

inline Texture::Texture(GLuint textureName) noexcept :
	mId(textureName)
{
}

inline Texture::~Texture() noexcept
{
	reset();
}

inline Texture::Texture(Texture &&other) noexcept :
	mId(other.release())
{
}

inline Texture &Texture::operator =(Texture &&other) noexcept
{
	reset(other.release());
	return *this;
}

inline Texture::operator bool() const noexcept
{
	return (mId != 0);
}

inline void Texture::create(Target target)
{
	reset();
	glCreateTextures(static_cast<GLenum>(target), 1, &mId);
}

inline void Texture::reset(GLuint textureName) noexcept
{
	if (mId != 0) {
		glDeleteTextures(1, &mId);
	}
	mId = textureName;
}

inline GLuint Texture::release() noexcept
{
	GLuint tmp = mId;
	mId = 0;
	return tmp;
}

inline GLuint Texture::get() const noexcept
{
	return mId;
}

inline void Texture::bind(GLuint unit) const
{
	glBindTextureUnit(unit, mId);
}

inline void Texture::storage(GLsizei levels, GLenum internalformat, GLsizei width)
{
	glTextureStorage1D(mId, levels, internalformat, width);
}

inline void Texture::storage(GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
{
	glTextureStorage2D(mId, levels, internalformat, width, height);
}

inline void Texture::storage(GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
{
	glTextureStorage3D(mId, levels, internalformat, width, height, depth);
}

inline void Texture::storageMultisample(GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
	glTextureStorage2DMultisample(mId, samples, internalformat, width, height, fixedsamplelocations);
}

inline void Texture::storageMultisample(GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
	glTextureStorage3DMultisample(mId, samples, internalformat, width, height, depth, fixedsamplelocations);
}

inline void Texture::setSubImage(GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels)
{
	glTextureSubImage1D(mId, level, xoffset, width, format, type, pixels);
}

inline void Texture::setSubImage(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels)
{
	glTextureSubImage2D(mId, level, xoffset, yoffset, width, height, format, type, pixels);
}

inline void Texture::setSubImage(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels)
{
	glTextureSubImage3D(mId, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}

inline void Texture::setCompressedSubImage(GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data)
{
	glCompressedTextureSubImage1D(mId, level, xoffset, width, format, imageSize, data);
}

inline void Texture::setCompressedSubImage(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data)
{
	glCompressedTextureSubImage2D(mId, level, xoffset, yoffset, width, height, format, imageSize, data);
}

inline void Texture::setCompressedSubImage(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data)
{
	glCompressedTextureSubImage3D(mId, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
}

inline void Texture::getImage(GLint level, GLenum format, GLenum type, GLsizei bufSize, GLvoid *pixels) const
{
	glGetTextureImage(mId, level, format, type, bufSize, pixels);
}

inline void Texture::getCompressedImage(GLint level, GLsizei bufSize, GLvoid *pixels) const
{
	glGetCompressedTextureImage(mId, level, bufSize, pixels);
}

inline void Texture::setParameter(GLenum pname, GLfloat param)
{
	glTextureParameterf(mId, pname, param);
}

inline void Texture::setParameter(GLenum pname, const GLfloat *param)
{
	glTextureParameterfv(mId, pname, param);
}

inline void Texture::setParameter(GLenum pname, GLint param)
{
	glTextureParameteri(mId, pname, param);
}

inline void Texture::setParameter(GLenum pname, const GLint *param)
{
	glTextureParameteriv(mId, pname, param);
}

inline void Texture::setParameterI(GLenum pname, const GLint *params)
{
	glTextureParameterIiv(mId, pname, params);
}

inline void Texture::setParameterI(GLenum pname, const GLuint *params)
{
	glTextureParameterIuiv(mId, pname, params);
}

inline void Texture::generateMipmap()
{
	glGenerateTextureMipmap(mId);
}

} // namespace ogl
} // namespace gtl

#endif // TEXTURE_H
