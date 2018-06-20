#ifndef RENDERX_SHADERLANG_HPP_
#define RENDERX_SHADERLANG_HPP_

#include <vector>
#include <string>

namespace rex { namespace sl {

enum class types
{
    vec2,
    vec3,
    vec4,
    mat4
};

enum node_t
{
    module_t,
    attribute_t,
    function_t,
    operation_t,
    identifier_t,
    uniform_t,
    emitter_t,
    fwd_t
};

class node
{
public:
    explicit node(node_t t) : type(t) {}

    node& operator<<(node n)
    {
        nodes.push_back(n);
        return *this;
    }

//protected:
    node_t type;
    std::string s1;
    types t1;
    int i1;
    std::vector<node> nodes;
};

class module : public node
{
public:
    explicit module() : node (module_t) {}
};

class attribute : public node
{
public:
    explicit attribute() : node (attribute_t) {}
    explicit attribute(const std::string& name, types t, const int layout)
        : node (attribute_t)
    {
        s1 = name;
        i1 = layout;
        t1 = t;
    }

    const int location()
    {
        return i1;
    }

    const std::string& name()
    {
        return s1;
    }
};

class uniform : public node
{
public:
    explicit uniform() : node (uniform_t) {}
    explicit uniform(const std::string& name, types t)
        : node (uniform_t)
    {
        s1 = name;
        t1 = t;
    }
};

class emitter : public node
{
public:
    explicit emitter() : node (emitter_t) {}
    explicit emitter(const std::string& name, types t)
        : node (emitter_t)
    {
        s1 = name;
        t1 = t;
    }
};

class fwd : public node
{
public:
    explicit fwd() : node (fwd_t) {}
    explicit fwd(const std::string& name, types t)
        : node (fwd_t)
    {
        s1 = name;
        t1 = t;
    }
};

class function : public node
{
public:
    explicit function() : node (function_t) {}
    explicit function(const std::string& name) : node (function_t) {
        s1 = name;
    }
};

class identifier : public node
{
public:
    explicit identifier() : node (identifier_t) {}
    explicit identifier(const std::string& name) : node (identifier_t) {
        s1 = name;
    }

    const std::string& name()
    {
        return s1;
    }
};

class operation : public node
{
public:
    explicit operation() : node (operation_t) {}
    explicit operation(const std::string& oper, const std::string& ident1, const std::string& ident2)
        : node (operation_t) {

        s1 = oper;
        *this << identifier {ident1};
        *this << identifier {ident2};
    }
};

}
}

#endif // RENDERX_SHADERLANG_HPP_
