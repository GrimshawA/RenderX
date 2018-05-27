#include "vertex_data.hpp"

namespace rex
{

RxVertexDecl::Attribute::Attribute()
{
}

RxVertexDecl::Attribute::Attribute(int32_t attributeByteSize, int32_t attributeNumComponents, AttributeHint attributeHint)
: size(attributeByteSize)
, numComponents(attributeNumComponents)
, hint(attributeHint)
{
}

vertex_data::vertex_data()
{
}

std::size_t vertex_data::stride() const
{
    return getVertexSize();
}

const void* vertex_data::data() const
{
    return reinterpret_cast<const void*>(&this->_data[0]);
}

void vertex_data::addAttribute(int32_t componentByteSize, int32_t numComponents, RxVertexDecl::AttributeHint hint)
{
    format.attributes.push_back(RxVertexDecl::Attribute(componentByteSize, numComponents, hint));
}

void vertex_data::setVertexAttribute(int32_t vertexIndex, int32_t attributeIndex, void* data)
{
    char* dataAddress = reinterpret_cast<char*>(data);

    char* addressOfTarget = &dataAddress[0] + (getVertexSize() * vertexIndex) + getAttributeOffset(attributeIndex);

    memcpy(addressOfTarget, data, format.attributes[attributeIndex].size * format.attributes[attributeIndex].numComponents);
}

int32_t vertex_data::getAttributeOffset(int32_t attributeIndex) const
{
    int32_t localOffset = 0;
    for(std::size_t i = 0; i < format.attributes.size(); ++i)
    {
        if(i == attributeIndex)
        {
            return localOffset;
        }

        localOffset += getAttributeSize(i);
    }
    return localOffset;
}

int32_t vertex_data::getAttributeSize(int32_t attributeIndex) const
{
    return format.attributes[attributeIndex].size * format.attributes[attributeIndex].numComponents;
}

int32_t vertex_data::getVertexSize() const
{
    int32_t bytesPerVertex = 0;
    for(std::size_t i = 0; i < format.attributes.size(); ++i)
    {
        bytesPerVertex += format.attributes[i].numComponents * format.attributes[i].size;
    }
    return bytesPerVertex;
}

void vertex_data::allocateData(int32_t vertexCount)
{
    int32_t bytesPerVertex = getVertexSize();

    _data.resize(bytesPerVertex * vertexCount);

    count = vertexCount;
}

bool vertex_data::isVertexEqual(int32_t index1, int32_t index2)
{
    char* v1 = &_data[0] + getVertexSize() * index1;
    char* v2 = &_data[0] + getVertexSize() * index2;

    return true;

    /*if(memcmp(v1,v2, getVertexSize()) == 0)
    {
        return true;
    }
    else
        return false;*/
}

char* vertex_data::getAttribute(int32_t attributeIndex, int32_t vertexIndex)
{
    return &_data[0] + (getVertexSize() * vertexIndex) + getAttributeOffset(attributeIndex);
}

void vertex_data::removeLast()
{
    _data.resize(_data.size() - getVertexSize());
    count--;
}

int32_t vertex_data::getMemorySize() const
{
    return _data.size();
}

void vertex_data::swapVertices(int32_t index, int32_t goesTo)
{
    char* tbuffer = new char[getVertexSize()];

    // get the temp buffer from the index vertex
    memcpy(tbuffer, &_data[0] + getVertexSize() * index, getVertexSize());

    // copy goesTo to the index vertex
    memcpy(&_data[0] + getVertexSize() * index, &_data[0] + getVertexSize() * goesTo, getVertexSize());
	
    // copy temp buffer to goesTo now
    memcpy(&_data[0] + getVertexSize() * goesTo, tbuffer, getVertexSize());

    delete[] tbuffer;
}

void vertex_data::removeDuplicateVertices(vertex_data& varray, RxIndexArray& iarray)
{
    Log("Starting vertex count: %d", varray.count);
	
    // Lets remove duplicate vertices to get a smaller varray, iarray stays the same.

    // For each vertex, find duplicates after it
    for(std::size_t i = 0; i < varray.count ; ++i)
    {
        // For each i, iterate from i+1 to end
        for(std::size_t j = i + 1; j < varray.count; ++j)
        {
            if(varray.isVertexEqual(i,j))
            {
				
                // swap two vertices, also swap their references
                varray.swapVertices(j, varray.count-1);
                iarray.swapIndices(j, varray.count-1);
				
                varray.removeLast();

                // whatever indices were pointing at j, which is now gone, now point to i
                iarray.redirectFromTo(varray.count, i);
				

                //Log("%d and %d are duplicates. Redirecting all references of %d to %d.", i, j, j, i);

                j--;
            }
        }
    }

    Log("Done removing duplicated. Varray size: %d, IArray size %d", varray.count, iarray.indices.size());
}

VertexArray2D::VertexArray2D()
: m_textured(false){
    geometryType = Render::Primitive::TriangleFan;
};

VertexArray2D::VertexArray2D(Render::Primitive::Type primitiveType, unsigned int vertexCount)
: m_textured(false)
{
    geometryType = primitiveType;
    m_vertices.resize(vertexCount);
}

VertexArray2D::Vertex& VertexArray2D::operator[](unsigned int index)
{
    return m_vertices[index];
}

FloatRect VertexArray2D::getBounds()
{
    if (!m_vertices.empty())
    {
        float left = m_vertices[0].position.x;
        float top = m_vertices[0].position.y;
        float right = m_vertices[0].position.x;
        float bottom = m_vertices[0].position.y;

        for (std::size_t i = 0; i < m_vertices.size(); ++i)
        {
            Vector2 position = m_vertices[i].position;

            // Update left and right
            if (position.x < left)
                left = position.x;
            else if (position.x > right)
                right = position.x;

            // Update top and bottom
            if (position.y < top)
                top = position.y;
            else if (position.y > bottom)
                bottom = position.y;
        }

        return FloatRect(left, top, right - left, bottom - top);
    }
    else
    {
        // Array is empty
        return FloatRect();
    }
}

void VertexArray2D::append(const Vertex& v)
{
    m_vertices.push_back(v);
}

void VertexArray2D::clear()
{
    m_vertices.clear();
}

}
