#ifndef GTL_OGL_OPENGLEXCEPTION_H
#define GTL_OGL_OPENGLEXCEPTION_H

#include <exception>
#include <string>


namespace gtl {
namespace ogl {

class OpenGLException : public std::exception
{
public:
	OpenGLException(const std::string &message);
	virtual ~OpenGLException() noexcept = default;

	virtual const char *what() const noexcept override;

private:
	std::string mMessage;

};


inline OpenGLException::OpenGLException(const std::string &message) :
	mMessage(message)
{
}

inline const char *OpenGLException::what() const noexcept
{
	return mMessage.c_str();
}

} // namespace ogl
} // namespace gtl

#endif // GTL_OGL_OPENGLEXCEPTION_H
