* RenderX (abreviated as REX)

This is a graphics abstraction layer. The role of this library is to provide a public API to manage high end graphics,
in such a way that works equally well with OpenGL, Vulkan, Direct3D or other possible implementations.

The frontend should remain consistent and robust over versions and the backend is then free to be explored by specific implementations.

* REX IR

RenderX Intermediate Representation is an abstract data structure to describe shader code. Any language frontend,
like a visual programming language or a written one, can output REX IR, which the library is able to understand;

Each specific backend is then able to convert IR into something final which runs within that specific domain (SPIRV, GLSL, etc).

* Goals

Currently, REX is tightly bound to the daeva engine. In the future its meant to be provided as librex, a standalone, open-source library.
Then, it should be used as a submodule in the daeva project.