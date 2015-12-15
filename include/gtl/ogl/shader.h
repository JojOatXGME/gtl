#ifndef GTL_OGL_SHADER_H
#define GTL_OGL_SHADER_H

#include <limits>
#include <string>

#include <GL/glew.h>

#include "gtl/ogl/shaderexception.h"


namespace gtl {
namespace ogl {

class Shader final
{
public:
	enum class Type {
		VERTEX = GL_VERTEX_SHADER,
		TESS_CONTROL = GL_TESS_CONTROL_SHADER,
		TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
		GEOMETRY = GL_GEOMETRY_SHADER,
		FRAGMENT = GL_FRAGMENT_SHADER,
		COMPUTE = GL_COMPUTE_SHADER
	};

	Shader(Type type);
	Shader(Type type, const std::string &source);
	explicit Shader(GLuint shaderName = 0) noexcept;
	~Shader() noexcept;

	Shader(Shader &&other) noexcept;
	Shader &operator = (Shader &&other) noexcept;
	explicit operator bool () const noexcept;

	void create(Type type);
	void create(Type type, const std::string &source);
	void reset(GLuint shaderName = 0) noexcept;
	GLuint release() noexcept;

	GLuint get() const noexcept;

	void setSource(const std::string &source);
	void setSource(GLsizei count, const GLchar **sources, GLint *length);
	void compile();
	std::string getInfoLog() const;

private:
	Shader(const Shader &) = delete;
	Shader &operator=(const Shader &) = delete;

	GLuint mId;

};


inline Shader::Shader(Shader::Type type) :
	Shader()
{
	create(type);
}

inline Shader::Shader(Type type, const std::string &source) :
	Shader()
{
	create(type, source);
}

inline Shader::Shader(GLuint shaderName) noexcept :
	mId(shaderName)
{
}

inline Shader::~Shader()
{
	reset();
}

inline Shader::Shader(Shader &&other) noexcept :
	mId(other.release())
{
}

inline Shader &Shader::operator =(Shader &&other) noexcept
{
	reset(other.release());
	return *this;
}

inline Shader::operator bool() const noexcept
{
	return (mId != 0);
}

inline void Shader::create(Shader::Type type)
{
	reset(glCreateShader(static_cast<GLenum>(type)));
}

inline void Shader::create(Shader::Type type, const std::string &source)
{
	create(type);
	setSource(source);
}

inline void Shader::reset(GLuint shaderName) noexcept
{
	if (mId != 0) {
		glDeleteShader(mId);
	}
	mId = shaderName;
}

inline GLuint Shader::release() noexcept
{
	GLuint tmp = mId;
	mId = 0;
	return tmp;
}

inline GLuint Shader::get() const noexcept
{
	return mId;
}

inline void Shader::setSource(const std::string &source)
{
	if (source.size() > std::numeric_limits<GLint>::max()) {
		throw ShaderException("Shader source too large.");
	}

	const auto *buf = source.data();
	GLint bufLen = static_cast<GLint>(source.size());
	setSource(1, &buf, &bufLen);
}

inline void Shader::setSource(GLsizei count, const GLchar **sources, GLint *length)
{
	glShaderSource(mId, count, sources, length);
}

inline void Shader::compile()
{
	GLint status;
	glCompileShader(mId);
	glGetShaderiv(mId, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		throw ShaderException("Error while compiling shader");
	}
}

inline std::string Shader::getInfoLog() const
{
	GLint lenght;
	glGetShaderiv(mId, GL_INFO_LOG_LENGTH, &lenght);
	if (lenght != 0) {
		std::vector<GLchar> buffer(lenght);
		glGetShaderInfoLog(mId, lenght, &lenght, buffer.data());
		return std::string(buffer.data(), lenght);
	} else {
		return std::string();
	}
}

} // namespace ogl
} // namespace gtl

#endif // GTL_OGL_SHADER_H
