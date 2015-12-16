#ifndef GTL_OGL_BUFFER_H
#define GTL_OGL_BUFFER_H

#include <cstdint>

#include <GL/glew.h>


namespace gtl {
namespace ogl {

class Buffer final
{
public:
	enum class Target {
		ARRAY = GL_ARRAY_BUFFER,
		COPY_READ = GL_COPY_READ_BUFFER,
		COPY_WRITE = GL_COPY_WRITE_BUFFER,
		ELEMENT_ARRAY = GL_ELEMENT_ARRAY_BUFFER,
		PIXEL_PACK = GL_PIXEL_PACK_BUFFER,
		PIXEL_UNPACK = GL_PIXEL_UNPACK_BUFFER,
		TEXTURE = GL_TEXTURE_BUFFER,
		TRANSFORM_FEEDBACK = GL_TRANSFORM_FEEDBACK_BUFFER,
		UNIFORM = GL_UNIFORM_BUFFER
	};

	enum class UsageHint {
		STREAM_DRAW = GL_STREAM_DRAW,
		STREAM_READ = GL_STREAM_READ,
		STREAM_COPY = GL_STREAM_COPY,
		STATIC_DRAW = GL_STATIC_DRAW,
		STATIC_READ = GL_STATIC_READ,
		STATIC_COPY = GL_STATIC_COPY,
		DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
		DYNAMIC_READ = GL_DYNAMIC_READ,
		DYNAMIC_COPY = GL_DYNAMIC_COPY
	};

	enum class AccessPolicy {
		READ_ONLY = GL_READ_ONLY,
		WRITE_ONLY = GL_WRITE_ONLY,
		READ_WRITE = GL_READ_WRITE
	};
public:
	Buffer(bool create);
	explicit Buffer(GLuint bufferName = 0) noexcept;
	~Buffer() noexcept;

	Buffer(Buffer &&other) noexcept;
	Buffer &operator = (Buffer &&other) noexcept;
	explicit operator bool () const noexcept;

	void create();
	void reset(GLuint bufferName = 0) noexcept;
	GLuint release() noexcept;

	GLuint get() const noexcept;
	void bind(Target target) const;

	void storage(GLsizeiptr size, const GLvoid *data, GLbitfield flags);
	void data(std::size_t size, const void *data, UsageHint usage);

	void setSubData(GLintptr offset, GLsizeiptr size, const GLvoid *data);
	// TODO glCopyNamedBufferSubData
	// TODO glClearNamedBufferData
	// TODO glClearNamedBufferSubData

	void *map(AccessPolicy access);
	void *map(GLintptr offset, GLsizeiptr length, GLbitfield access);
	void flush(GLintptr offset, GLsizeiptr length);
	bool unmap();

	void getSubData(GLintptr offset, GLsizeiptr size, GLvoid *data) const;

	// TODO getParameter

	static GLenum toEnum(Target target) noexcept;
	static GLenum toEnum(UsageHint usageHint) noexcept;
	static GLenum toEnum(AccessPolicy accessPolicy) noexcept;

private:
	Buffer(const Buffer &) = delete;
	Buffer &operator=(const Buffer &) = delete;

	GLuint mId;

};


inline Buffer::Buffer(bool create) :
	Buffer()
{
	if (create) {
		this->create();
	}
}

inline Buffer::Buffer(GLuint bufferName) noexcept :
	mId(bufferName)
{
}

inline Buffer::~Buffer() noexcept
{
	reset();
}

inline Buffer::Buffer(Buffer &&other) noexcept :
	mId(other.release())
{
}

inline Buffer &Buffer::operator =(Buffer &&other) noexcept
{
	reset(other.release());
	return *this;
}

inline Buffer::operator bool() const noexcept
{
	return (mId != 0);
}

inline void Buffer::create()
{
	reset();
	//glGenBuffers(1, &mId);
	glCreateBuffers(1, &mId);
}

inline void Buffer::reset(GLuint bufferName) noexcept
{
	if (mId != 0) {
		glDeleteBuffers(1, &mId);
	}
	mId = bufferName;
}

inline GLuint Buffer::release() noexcept
{
	GLuint tmp = mId;
	mId = 0;
	return tmp;
}

inline GLuint Buffer::get() const noexcept
{
	return mId;
}

inline void Buffer::bind(Buffer::Target target) const
{
	glBindBuffer(toEnum(target), mId);
}

inline void Buffer::storage(GLsizeiptr size, const GLvoid *data, GLbitfield flags)
{
	glNamedBufferStorage(mId, size, data, flags);
}

inline void Buffer::data(std::size_t size, const void *data, UsageHint usage)
{
	//bind(target);
	//glBufferData(toEnum(target), size, data, toEnum(usage));
	glNamedBufferData(mId, size, data, toEnum(usage));
}

inline void Buffer::setSubData(GLintptr offset, GLsizeiptr size, const GLvoid *data)
{
	glNamedBufferSubData(mId, offset, size, data);
}

inline void *Buffer::map(AccessPolicy access)
{
	//bind(target);
	//return glMapBuffer(toEnum(target), toEnum(access));
	return glMapNamedBuffer(mId, toEnum(access));
}

inline void *Buffer::map(GLintptr offset, GLsizeiptr length, GLbitfield access)
{
	return glMapNamedBufferRange(mId, offset, length, access);
}

inline void Buffer::flush(GLintptr offset, GLsizeiptr length)
{
	glFlushMappedNamedBufferRange(mId, offset, length);
}

inline bool Buffer::unmap()
{
	//bind(target);
	//return glUnmapBuffer(toEnum(target)) == GL_TRUE
	return glUnmapNamedBuffer(mId);
}

inline void Buffer::getSubData(GLintptr offset, GLsizeiptr size, GLvoid *data) const
{
	glGetNamedBufferSubData(mId, offset, size, data);
}

inline GLenum Buffer::toEnum(Buffer::Target target) noexcept
{
	return static_cast<GLenum>(target);
}

inline GLenum Buffer::toEnum(Buffer::UsageHint usageHint) noexcept
{
	return static_cast<GLenum>(usageHint);
}

inline GLenum Buffer::toEnum(Buffer::AccessPolicy accessPolicy) noexcept
{
	return static_cast<GLenum>(accessPolicy);
}

} // namespace ogl
} // namespace gtl

#endif // GTL_OGL_BUFFER_H
