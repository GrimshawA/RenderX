#ifndef RENDERXGL_SHADER_COMPILER_HPP_
#define RENDERXGL_SHADER_COMPILER_HPP_

#include "../shader_lang.hpp"
#include <sstream>

//std::string vsSrc {
//"#version 330\n"
//"uniform mat4 MVP;\n"
//"layout(location = 1) in vec3 vCol;\n"
//"layout(location = 0) in vec2 vPos;\n"
//"out vec3 color;\n"
//"void main()\n"
//"{\n"
//"    gl_Position = mat4(1) * vec4(vPos, 0.0, 1.0);\n"
//"    color = vCol;\n"
//"}\n"};

//std::string fsSrc {
//        "varying vec3 color;\n"
//        "void main()\n"
//        "{\n"
//        "    gl_FragColor = vec4(color, 1.0);\n"
//        "}\n"};


namespace rex {

    class gl_shader_compiler
    {
    public:

        enum modes {
            vertex_mode,
            fragment_mode
        };

        explicit gl_shader_compiler (modes m)
            : _mode(m)
        {

        }

        std::string build_expression(const sl::node& o)
        {
            std::string str;

            if (o.type == sl::operation_t)
            {
                str = build_expression(o.nodes[0]) + " " + o.s1 + " " + build_expression(o.nodes[1]);
            }
            else if (o.type == sl::identifier_t)
            {
                return o.s1;
            }

            return str;
        }

        void build_function(const sl::function& f, std::stringstream& s)
        {
            auto isUsableFunction = [this, &f]()
            {
                if (f.s1 == "main")
                    return true;

                if (_mode == vertex_mode && f.s1 == "vertex_main")
                    return true;

                if (_mode == fragment_mode && f.s1 == "fragment_main")
                    return true;

                return false;
            };

            if (!isUsableFunction())
                return;

            s << "\nvoid main() {\n";

            for (int i = 0; i < f.nodes.size(); ++i)
            {
                switch (f.nodes[i].type)
                {
                case sl::operation_t: {
                    sl::operation& a = (sl::operation&)f.nodes[i];
                    s << "    " << build_expression(a) << ";\n";
                    break;
                }
                }
            }

            s << "}\n";
        }

        std::string build(const sl::module& m)
        {
            std::stringstream vs;

            vs << "#version 330\n";

            for (int i = 0; i < m.nodes.size(); ++i)
            {
                switch (m.nodes[i].type)
                {
                case sl::attribute_t: {
                    sl::attribute& a = (sl::attribute&)m.nodes[i];

                    std::string type;
                    switch(a.t1)
                    {
                    case sl::types::vec2:
                        type = "vec2"; break;

                    case sl::types::vec3:
                        type = "vec3"; break;

                    case sl::types::vec4:
                        type = "vec4"; break;

                    default:
                        type = "void";
                    }

                    vs << "layout(location = " << a.location() << ") in " << type << " " << a.name() << ";\n";
                    break;
                }

                case sl::fwd_t: {
                    sl::fwd& f = (sl::fwd&)m.nodes[i];

                    std::string type;
                    switch(f.t1)
                    {
                    case sl::types::vec2:
                        type = "vec2"; break;

                    case sl::types::vec3:
                        type = "vec3"; break;

                    case sl::types::vec4:
                        type = "vec4"; break;

                    default:
                        type = "void";
                    }

                    vs << "varying " << type << " " << f.s1 << ";\n";
                    break;
                }

                case sl::emitter_t: {
                    sl::emitter& e = (sl::emitter&)m.nodes[i];
                    vs << "out vec3 " << e.s1 << ";\n";
                    break;
                }

                case sl::function_t: {
                    sl::function& f = (sl::function&)m.nodes[i];
                    build_function(f, vs);
                    break;
                }
                }
            }

            return vs.str();
        }

        modes _mode;
    };
}

#endif // RENDERXGL_SHADER_COMPILER_HPP_
