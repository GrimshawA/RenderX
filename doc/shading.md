Shaders can be kept around as resources, as rex::shader instances.
However, they normally get disposed because they aren't needed.

Once multiple shaders are compiled into a program, the shaders no longer matter.

In this library, programs are represented by pipelines, which carry other additional state.

1 pipeline is 1 shader program, making it unnecessary to have an additional program API.