#ifndef GTL_OGL_SHADEREXCEPTION_H
#define GTL_OGL_SHADEREXCEPTION_H

#include "gtl/ogl/openglexception.h"


namespace gtl {
namespace ogl {

class ShaderException : public OpenGLException
{
public:
	ShaderException(const std::string &message) :
		OpenGLException(message)
	{}

};

} // namespace ogl
} // namespace gtl

#endif // GTL_OGL_SHADEREXCEPTION_H
