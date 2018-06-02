#ifndef RXVERTEXDECL_H__
#define RXVERTEXDECL_H__

#include "config.hpp"
#include <vector>
#include <stdint.h>

namespace rex {

/**
    \class Format
    \brief Vertex format specification
*/
class REX_API vertex_decl
{
public:

    enum PresetTypes
    {
        FLOAT3,
        FLOAT2
    };

    /// \class Attribute
    /// \brief One of the vertex components
    class REX_API Attribute
    {
    public:
        Attribute();
        Attribute(PresetTypes type);
        Attribute(int32_t attributeByteSize, int32_t attributeNumComponents);

        int32_t         size;            ///< Size, in bytes, of the data type
        int32_t         numComponents;   ///< Number of components that make up this attribute's data
    };

    explicit vertex_decl();
    explicit vertex_decl(std::initializer_list<Attribute> list);
    explicit vertex_decl(const std::vector<Attribute>& attributes);

    bool                   segmented;  ///< Is each vertex contiguous or segmented in multiple arrays?
    std::vector<Attribute> attributes; ///< List of attributes that define the vertex format
};

}

#endif // RXVERTEXDECL_H__
