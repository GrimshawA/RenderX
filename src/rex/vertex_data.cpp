#include "vertex_data.hpp"
#include <string>

namespace rex
{

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

void vertex_data::addAttribute(int32_t componentByteSize, int32_t numComponents)
{
    format.attributes.push_back(vertex_decl::Attribute(componentByteSize, numComponents));
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
    //Log("Starting vertex count: %d", varray.count);

    // Lets remove duplicate vertices to get a smaller varray, iarray stays the same.

    // For each vertex, find duplicates after it
//    for(std::size_t i = 0; i < varray.count ; ++i)
//    {
//        // For each i, iterate from i+1 to end
//        for(std::size_t j = i + 1; j < varray.count; ++j)
//        {
//            if(varray.isVertexEqual(i,j))
//            {
				
//                // swap two vertices, also swap their references
//                varray.swapVertices(j, varray.count-1);
//                iarray.swapIndices(j, varray.count-1);
				
//                varray.removeLast();

//                // whatever indices were pointing at j, which is now gone, now point to i
//                iarray.redirectFromTo(varray.count, i);
				

//                //Log("%d and %d are duplicates. Redirecting all references of %d to %d.", i, j, j, i);

//                j--;
//            }
//        }
//    }

    //Log("Done removing duplicated. Varray size: %d, IArray size %d", varray.count, iarray.indices.size());
}

}
