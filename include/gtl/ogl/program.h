#ifndef GTL_OGL_PROGRAM_H
#define GTL_OGL_PROGRAM_H

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "gtl/ogl/shader.h"
#include "gtl/ogl/shaderexception.h"


namespace gtl {
namespace ogl {

class Program final
{
public:
	Program(bool create);
	Program(Shader::Type type, const std::string &source);
	Program(Shader::Type type, GLsizei count, const char **strings);
	explicit Program(GLuint programName = 0) noexcept;
	~Program() noexcept;

	Program(Program &&other) noexcept;
	Program &operator = (Program &&other) noexcept;
	explicit operator bool () const noexcept;

	void create();
	void create(Shader::Type type, const std::string &source);
	void create(Shader::Type type, GLsizei count, const char **strings);
	void reset(GLuint programName = 0) noexcept;
	GLuint release() noexcept;

	GLuint get() const noexcept;
	void use() const;

	void attachShader(const Shader &shader);
	void detachShader(const Shader &shader);
	void bindFragDataLocation(GLuint location, const std::string &name);
	void bindAttribLocation(GLuint location, const std::string &name);
	void setTransformFeedbackVaryings(GLsizei count, const char **varyings, GLenum bufferMode);
	void link();
	void validate();

	std::string getInfoLog() const;
	// TODO getFragDataLocation ?
	GLint getAttribLocation(const std::string &name) const;
	GLint getUniformLocation(const std::string &name) const;

	void setUniform(GLint location, GLint value) const;
	void setUniform(GLint location, GLfloat value) const;
	void setUniform(GLint location, const glm::vec3 &value) const;
	void setUniform(GLint location, const glm::vec4 &value) const;
	void setUniform(GLint location, const glm::mat3 &value) const;
	void setUniform(GLint location, const glm::mat4 &value) const;

private:
	Program(const Program &) = delete;
	Program &operator=(const Program &) = delete;

	GLuint mId;
};


inline Program::Program(bool create) :
	Program()
{
	if (create) {
		this->create();
	}
}

inline Program::Program(Shader::Type type, const std::string &source) :
	Program()
{
	create(type, source);
}

inline Program::Program(Shader::Type type, GLsizei count, const char **strings) :
	Program()
{
	create(type, count, strings);
}

inline Program::Program(GLuint programName) noexcept :
	mId(programName)
{
}

inline Program::~Program() noexcept
{
	reset();
}

inline Program::Program(Program &&other) noexcept :
	mId(other.release())
{
}

inline Program &Program::operator =(Program &&other) noexcept
{
	reset(other.release());
	return *this;
}

inline Program::operator bool() const noexcept
{
	return (mId != 0);
}

inline void Program::create()
{
	reset(glCreateProgram());
}

inline void Program::create(Shader::Type type, const std::string &source)
{
	const char *strings = source.c_str();
	create(type, 1, &strings);
}

inline void Program::create(Shader::Type type, GLsizei count, const char **strings)
{
	reset(glCreateShaderProgramv(static_cast<GLenum>(type), count, strings));
}

inline void Program::reset(GLuint programName) noexcept
{
	if (mId != 0) {
		glDeleteProgram(mId);
	}
	mId = programName;
}

inline GLuint Program::release() noexcept
{
	GLuint tmp = mId;
	mId = 0;
	return tmp;
}

inline GLuint Program::get() const noexcept
{
	return mId;
}

inline void Program::use() const
{
	glUseProgram(mId);
}

inline void Program::attachShader(const Shader &shader)
{
	glAttachShader(mId, shader.get());
}

inline void Program::detachShader(const Shader &shader)
{
	glDetachShader(mId, shader.get());
}

inline void Program::bindFragDataLocation(GLuint location, const std::string &name)
{
	glBindFragDataLocation(mId, location, name.c_str());
}

inline void Program::bindAttribLocation(GLuint location, const std::string &name)
{
	glBindAttribLocation(mId, location, name.c_str());
}

inline void Program::setTransformFeedbackVaryings(GLsizei count, const char **varyings, GLenum bufferMode)
{
	glTransformFeedbackVaryings(mId, count, varyings, bufferMode);
}

inline void Program::link()
{
	GLint status;
	glLinkProgram(mId);
	glGetProgramiv(mId, GL_LINK_STATUS, &status);
	if (status != GL_TRUE) {
		throw ShaderException("Error while linking shader program");
	}
}

inline void Program::validate()
{
	GLint status;
	glValidateProgram(mId);
	glGetProgramiv(mId, GL_VALIDATE_STATUS, &status);
	if (status != GL_TRUE) {
		throw ShaderException("Shader program is invalid");
	}
}

inline std::string Program::getInfoLog() const
{
	GLint lenght;
	glGetProgramiv(mId, GL_INFO_LOG_LENGTH, &lenght);
	if (lenght != 0) {
		std::vector<GLchar> buffer(lenght);
		glGetProgramInfoLog(mId, lenght, &lenght, buffer.data());
		return std::string(buffer.data(), lenght);
	} else {
		return std::string();
	}
}

inline GLint Program::getAttribLocation(const std::string &name) const
{
	return glGetAttribLocation(mId, name.c_str());
}

inline GLint Program::getUniformLocation(const std::string &name) const
{
	return glGetUniformLocation(mId, name.c_str());
}

inline void Program::setUniform(GLint location, GLint value) const
{
	glProgramUniform1i(mId, location, value);
}

inline void Program::setUniform(GLint location, GLfloat value) const
{
	glProgramUniform1f(mId, location, value);
}

inline void Program::setUniform(GLint location, const glm::vec3 &value) const
{
	glProgramUniform3fv(mId, location, 1, glm::value_ptr(value));
}

inline void Program::setUniform(GLint location, const glm::vec4 &value) const
{
	glProgramUniform4fv(mId, location, 1, glm::value_ptr(value));
}

inline void Program::setUniform(GLint location, const glm::mat3 &value) const
{
	glProgramUniformMatrix3fv(mId, location, 1, GL_FALSE, glm::value_ptr(value));
}

inline void Program::setUniform(GLint location, const glm::mat4 &value) const
{
	glProgramUniformMatrix4fv(mId, location, 1, GL_FALSE, glm::value_ptr(value));
}

} // namespace ogl
} // namespace gtl

#endif // GTL_OGL_SHADERPROGRAM_H
