Pipelines
===========

In RenderX, there is a logical object called pipeline, which is a grouping
of multiple rendering states needed to render a given object.

Whenever a rendering command occurs, one given pipeline must be choosen to render it.

It is highly recommended that all draw operations that use the same pipeline are done
consecutively, for performance reasons.

Note that in Vulkan backends, the pipeline is an actual vulkan concept, while in OpenGL
for example, its just a logical grouping with state.