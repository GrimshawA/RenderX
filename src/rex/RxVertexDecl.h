#ifndef RXVERTEXDECL_H__
#define RXVERTEXDECL_H__

#include <bitcore/Config.h>
#include <vector>

/**
    \class Format
    \brief Vertex format specification
*/
class REX_API RxVertexDecl
{
public:

    ///< Hints about what an attribute is
    enum AttributeHint
    {
        Position,
        Color,
        TexCoord
    };

    /// \class Attribute
    /// \brief One of the vertex components
    class REX_API Attribute
    {
    public:
        Attribute();
        Attribute(int32_t attributeByteSize, int32_t attributeNumComponents, AttributeHint attributeHint);

        int32_t         size;            ///< Size, in bytes, of the data type
        int32_t         numComponents;   ///< Number of components that make up this attribute's data
        AttributeHint hint;            ///< Hint about what this attribute actually is
    };

    bool                   segmented;  ///< Is each vertex contiguous or segmented in multiple arrays?
    std::vector<Attribute> attributes; ///< List of attributes that define the vertex format
};

#endif // RXVERTEXDECL_H__
