#ifndef REX_GL_DEFAULT_SHADERS_HPP_
#define REX_GL_DEFAULT_SHADERS_HPP_

namespace rex
{
    static const char gVertexSource[] =
        "#version 120\n"
        "attribute vec4 vertex;\n"
        "attribute vec4 color;\n"
        "attribute vec2 texCoord;\n"
        "uniform mat4 projection = mat4(1);\n"
        "uniform mat4 model = mat4(1);\n"
        "uniform mat4 view = mat4(1);\n"
        "varying vec4 outColor;\n"
        "varying vec2 texUV;\n"
        "void main() {\n"
        "  gl_Position = projection * view * model * vertex;\n"
        "  outColor = color;\n"
        "  texUV = texCoord;\n"
        "}\n";

    static const char gFragmentSource[] =
        "#version 120\n"
        "uniform sampler2D texture;\n"
        "varying vec4 outColor;\n"
        "varying vec2 texUV;\n"
        "void main() {\n"
        " if(texture2D(texture,texUV).a == 0) discard;"
        "   gl_FragColor = texture2D(texture, texUV) * outColor;\n"
        "   vec4 c = texture2D(texture, texUV) * outColor;"
        "   gl_FragColor = c * c.a;"
        "}\n";
}

#endif // REX_GL_DEFAULT_SHADERS_HPP_
