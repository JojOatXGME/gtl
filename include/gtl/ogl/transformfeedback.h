#ifndef GTL_OGL_TRANSFORMFEEDBACK_H
#define GTL_OGL_TRANSFORMFEEDBACK_H

#include <GL/glew.h>

#include "gtl/ogl/buffer.h"


namespace gtl {
namespace ogl {

class TransformFeedback final
{
public:
	TransformFeedback(bool create);
	explicit TransformFeedback(GLuint objectName = 0) noexcept;
	~TransformFeedback() noexcept;

	TransformFeedback(TransformFeedback &&other) noexcept;
	TransformFeedback &operator = (TransformFeedback &&other) noexcept;
	explicit operator bool () const noexcept;

	void create();
	void reset(GLuint objectName = 0) noexcept;
	GLuint release() noexcept;

	GLuint get() const noexcept;
	void bind() const;
	void unbind() const;

	void setBufferBase(GLuint index, const Buffer &buffer);
	void setBufferRange(GLuint index, const Buffer &buffer, GLintptr offset, GLsizeiptr size);

	// TODO getParameter

	static void begin(GLenum primitiveMode);
	static void pause();
	static void resume();
	static void end();

private:
	TransformFeedback(const TransformFeedback &) = delete;
	TransformFeedback &operator=(const TransformFeedback &) = delete;

	GLuint mId;

};


inline TransformFeedback::TransformFeedback(bool create) :
	TransformFeedback()
{
	if (create) {
		this->create();
	}
}

inline TransformFeedback::TransformFeedback(GLuint objectName) noexcept :
	mId(objectName)
{
}

inline TransformFeedback::~TransformFeedback() noexcept
{
	reset();
}

inline TransformFeedback::TransformFeedback(TransformFeedback &&other) noexcept :
	mId(other.release())
{
}

inline TransformFeedback &TransformFeedback::operator =(TransformFeedback &&other) noexcept
{
	reset(other.release());
	return *this;
}

inline TransformFeedback::operator bool() const noexcept
{
	return (mId != 0);
}

inline void TransformFeedback::create()
{
	reset();
	glCreateTransformFeedbacks(1, &mId);
}

inline void TransformFeedback::reset(GLuint objectName) noexcept
{
	if (mId != 0) {
		glDeleteTransformFeedbacks(1, &mId);
	}
	mId = objectName;
}

inline GLuint TransformFeedback::release() noexcept
{
	GLuint tmp = mId;
	mId = 0;
	return tmp;
}

inline GLuint TransformFeedback::get() const noexcept
{
	return mId;
}

inline void TransformFeedback::bind() const
{
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, mId);
}

inline void TransformFeedback::unbind() const
{
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
}

inline void TransformFeedback::setBufferBase(GLuint index, const Buffer &buffer)
{
	glTransformFeedbackBufferBase(mId, index, buffer.get());
}

inline void TransformFeedback::setBufferRange(GLuint index, const Buffer &buffer, GLintptr offset, GLsizeiptr size)
{
	glTransformFeedbackBufferRange(mId, index, buffer.get(), offset, size);
}

inline void TransformFeedback::begin(GLenum primitiveMode)
{
	glBeginTransformFeedback(primitiveMode);
}

inline void TransformFeedback::pause()
{
	glPauseTransformFeedback();
}

inline void TransformFeedback::resume()
{
	glResumeTransformFeedback();
}

inline void TransformFeedback::end()
{
	glEndTransformFeedback();
}

} // namespace ogl
} // namespace gtl

#endif // GTL_OGL_TRANSFORMFEEDBACK_H
