#ifndef GTL_OGL_DRAW_H
#define GTL_OGL_DRAW_H

#include <GL/glew.h>


namespace gtl {
namespace ogl {

void draw(GLenum mode, GLint first, GLsizei count);
void draw(GLenum mode, GLint first, GLsizei count, GLsizei instances);
void drawElements(GLenum mode, GLint first, GLsizei count, GLenum type);
void drawElements(GLenum mode, GLint first, GLsizei count, GLenum type, GLsizei instances);


inline void draw(GLenum mode, GLint first, GLsizei count)
{
	glDrawArrays(mode, first, count);
}

inline void draw(GLenum mode, GLint first, GLsizei count, GLsizei instances)
{
	glDrawArraysInstanced(mode, first, count, instances);
}

inline void drawElements(GLenum mode, GLint first, GLsizei count, GLenum type)
{
	glDrawElements(mode, count, type, reinterpret_cast<GLvoid*>(first));
}

inline void drawElements(GLenum mode, GLint first, GLsizei count, GLenum type, GLsizei instances)
{
	glDrawElementsInstanced(mode, count, type, reinterpret_cast<GLvoid*>(first), instances);
}

} // namespace ogl
} // namespace gtl

#endif // GTL_OGL_DRAW_H
