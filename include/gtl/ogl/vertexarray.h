#ifndef GTL_OGL_VERTEXARRAY_H
#define GTL_OGL_VERTEXARRAY_H

#include <GL/glew.h>

#include "gtl/ogl/buffer.h"


namespace gtl {
namespace ogl {

class VertexArray final
{
public:
	VertexArray(bool create);
	explicit VertexArray(GLuint vertexArrayName = 0) noexcept;
	~VertexArray() noexcept;

	VertexArray(VertexArray &&other) noexcept;
	VertexArray &operator = (VertexArray &&other) noexcept;
	explicit operator bool () const noexcept;

	void create();
	void reset(GLuint vertexArrayName = 0) noexcept;
	GLuint release() noexcept;

	GLuint get() const noexcept;
	void bind() const;

	void enableAttrib(GLuint location);
	void disableAttrib(GLuint location);
	void setElementArray(const Buffer &buf);
	void setAttribBinding(GLuint attribindex, GLuint bindingindex);
	void setBindingDivisor(GLuint bindingindex, GLuint divisor);

	void setVertexBuffer(GLuint bindingindex, const Buffer &buffer, GLintptr offset, GLsizei stride);
	void setVertexBuffers(GLuint first, GLsizei count, const Buffer *buffers, const GLintptr *offsets, const GLsizei *strides);

	void setAttribFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
	void setAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
	void setAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
	void setAttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);

	// TODO getParameter

private:
	VertexArray(const VertexArray &) = delete;
	VertexArray &operator=(const VertexArray &) = delete;

	GLuint mId;
};


inline VertexArray::VertexArray(bool create) :
	VertexArray()
{
	if (create) {
		this->create();
	}
}

inline VertexArray::VertexArray(GLuint vertexArrayName) noexcept :
	mId(vertexArrayName)
{
}

inline VertexArray::~VertexArray()
{
	reset();
}

inline VertexArray::VertexArray(VertexArray &&other) noexcept :
	mId(other.release())
{
}

inline VertexArray &VertexArray::operator =(VertexArray &&other) noexcept
{
	reset(other.release());
	return *this;
}

inline VertexArray::operator bool() const noexcept
{
	return (mId != 0);
}

inline void VertexArray::create()
{
	reset();
	//glGenVertexArrays(1, &mId);
	glCreateVertexArrays(1, &mId);
}

inline void VertexArray::reset(GLuint vertexArrayName) noexcept
{
	if (mId != 0) {
		glDeleteVertexArrays(1, &mId);
	}
	mId = vertexArrayName;
}

inline GLuint VertexArray::release() noexcept
{
	GLuint tmp = mId;
	mId = 0;
	return tmp;
}

inline GLuint VertexArray::get() const noexcept
{
	return mId;
}

inline void VertexArray::bind() const
{
	glBindVertexArray(mId);
}

inline void VertexArray::enableAttrib(GLuint location)
{
	//bind();
	//glEnableVertexAttribArray(location);
	glEnableVertexArrayAttrib(mId, location);
}

inline void VertexArray::disableAttrib(GLuint location)
{
	//bind();
	//glDisableVertexAttribArray(location);
	glDisableVertexArrayAttrib(mId, location);
}

inline void VertexArray::setElementArray(const Buffer &buf)
{
	//bind();
	//buf.bind(Buffer::Target::ELEMENT_ARRAY);
	glVertexArrayElementBuffer(mId, buf.get());
}

inline void VertexArray::setAttribBinding(GLuint attribindex, GLuint bindingindex)
{
	glVertexArrayAttribBinding(mId, attribindex, bindingindex);
}

inline void VertexArray::setBindingDivisor(GLuint bindingindex, GLuint divisor)
{
	glVertexArrayBindingDivisor(mId, bindingindex, divisor);
}

inline void VertexArray::setVertexBuffer(GLuint bindingindex, const Buffer &buffer, GLintptr offset, GLsizei stride)
{
	glVertexArrayVertexBuffer(mId, bindingindex, buffer.get(), offset, stride);
}

inline void VertexArray::setVertexBuffers(GLuint first, GLsizei count, const Buffer *buffers, const GLintptr *offsets, const GLsizei *strides)
{
	if (buffers == nullptr) {
		glVertexArrayVertexBuffers(mId, first, count, nullptr, nullptr, nullptr);
	} else {
		GLuint bufs[count];
		// TODO would it be acceptable to do reinterpret_cast<GLuint*>(buffers)
		// if sizeof(Buffer) == sizeof(GLuint)?
		for (GLsizei i = 0; i < count; ++i) {
			bufs[i] = buffers[i].get();
		}
		glVertexArrayVertexBuffers(mId, first, count, bufs, offsets, strides);
	}
}

inline void VertexArray::setAttribFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
{
	glVertexArrayAttribFormat(mId, attribindex, size, type, GL_FALSE, relativeoffset);
}

inline void VertexArray::setAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset)
{
	glVertexArrayAttribFormat(mId, attribindex, size, type, normalized, relativeoffset);
}

inline void VertexArray::setAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
{
	glVertexArrayAttribIFormat(mId, attribindex, size, type, relativeoffset);
}

inline void VertexArray::setAttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
{
	glVertexArrayAttribLFormat(mId, attribindex, size, type, relativeoffset);
}

} // namespace ogl
} // namespace gtl

#endif // GTL_OGL_VERTEXARRAY_H
