#include "vertex_decl.hpp"

namespace rex {

vertex_decl::vertex_decl()
{

}

vertex_decl::vertex_decl(std::initializer_list<Attribute> list)
{
    for (auto& c : list)
    {
        attributes.push_back(c);
    }
}

vertex_decl::vertex_decl(const std::vector<Attribute>& attributes)
{
    this->attributes = attributes;
}

vertex_decl::Attribute::Attribute()
{
}

vertex_decl::Attribute::Attribute(PresetTypes type)
{
    switch(type)
    {
    case FLOAT2: size = 2;
                 numComponents = sizeof(float);
        break;

    case FLOAT3: size = 3;
                 numComponents = sizeof(float);
        break;
    }
}

vertex_decl::Attribute::Attribute(int32_t attributeByteSize, int32_t attributeNumComponents)
: size(attributeByteSize)
, numComponents(attributeNumComponents)
{
}

}
