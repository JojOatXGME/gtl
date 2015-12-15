Graphics Tool Library for C++
=============================
The goal of this library is to simplify the work with OpenGL. The
library was created with OpenGL 3.3 and C++11 in mind. It uses
`ARB_direct_state_access` and `ARB_separate_shader_objects`. It should
be possible to use this library with OpenGL 4.1 without extensions. It
is designed for personal use but other persons can use them too.

Current Features
----------------
 *  Wrapper classes for some OpenGL Objects:

     *  Buffer Object (`gtl::ogl::Buffer` in `gtl/ogl/buffer.h`)
     *  Program Object (`gtl::ogl::Program` in `gtl/ogl/program.h`)
     *  Shader Object (`gtl::ogl::Shader` in `gtl/ogl/shader.h`)
     *  Texture Object (`gtl::ogl::Texture` in `gtl/ogl/texture.h`)
     *  Vertex Array Object (`gtl::ogl::VertexArray` in
        `gtl/ogl/vertexarray.h`)

    More information [below](#wrapper-classes). Note that Program
    Objects and Shader Objects doesn't use the [OpenGL Object
    model](https://www.opengl.org/wiki/OpenGL_Object).

Wrapper Classes
---------------

Every of this classes has a default constructor which doesn't create
such object in OpenGL. You can create the object with a `create` method
or with another constructor:

    Buffer buffer();
    buffer.create();
    // -- or --
    Buffer buffer(true);

You can check if the instance contains an OpenGL Object except for the
zero Object.

    if (buffer) { ...

There is also a constructor which takes the name (`GLuint`) of an
already created OpenGL Object. With `reset` you can destroy the current
OpenGL object and may pass another name of an already created OpenGL
Object.

    GLuint bufferName;
    glCreateBuffers(1, &bufferName);
    // -----------------------------
    Buffer buffer();
    buffer.reset(bufferName);
    // -- or --
    Buffer buffer(bufferName);

Each of this classes are movable but not copyable.
