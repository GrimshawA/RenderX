#ifndef RXVERTEXARRAY_H__
#define RXVERTEXARRAY_H__

#include <bitcore/Color.h>
#include <bitcore/math/Rect.h>
#include <RenderX/RxGlobal.h>
#include "RxVertexDecl.h"

#include <vector>
#include <cstddef>

class RxIndexArray;

/**
    \class RxVertexArray
	\brief This structure holds vertex data

	1. This class is only a container for vertex data.
	2. It contains N vertices at once.
	3. All vertices have the same format.
	4. The format is dynamic and user specified
	5. Data for each vertex can be contiguous or segmented within the container
*/
class DAEVA_API RxVertexArray
{
public:

    RxVertexDecl       format; ///< Format of the vertex data
	std::vector<char>  _data;   ///< The vertex raw data
    std::size_t        count;  ///< Number of allocated vertices


	/// Default initialization
    RxVertexArray();

	/// Get the stride between vertices
	std::size_t stride() const;

	/// Get the raw pointer to the vertex data
	const void* data() const;

    void addAttribute(int32_t componentByteSize, int32_t numComponents, RxVertexDecl::AttributeHint hint);

	void removeLast();

	int32_t getVertexSize() const;

	/// Get the byte size of the current buffer
	int32_t getMemorySize() const;

	void swapVertices(int32_t index, int32_t goesTo);

	/// Get the pointer to the attribute data of a given vertex
	char* getAttribute(int32_t attributeIndex, int32_t vertexIndex);

	int32_t getAttributeOffset(int32_t attributeIndex) const;
	int32_t getAttributeSize(int32_t attributeIndex) const;

	bool isVertexEqual(int32_t index1, int32_t index2);

	void setVertexAttribute(int32_t vertexIndex, int32_t attributeIndex, void* data);

	void allocateData(int32_t vertexCount);

    static void removeDuplicateVertices(RxVertexArray& varray, RxIndexArray& iarray);
};

/**
\class VertexArray2D
\brief Small and focused geometry container

VertexArray2D is a simple class to compose 2D geometry.
It allows you to make objects with position, color and texture coordinates only.

You can draw geometry in VertexArray2D with Renderer::draw directly.
*/
class DAEVA_API VertexArray2D
{
public:

	/// \ingroup Graphics
	/// \class Vertex
	/// \brief Represents one unique vertex
	/// Vertices are composed by a 2D position, a Color and a UV coordinate. This representation is exclusive to VertexArray2D usage.
	class DAEVA_API Vertex
	{
	public:
		Vertex(){}

		Vertex(Vector2 pos, Color col, Vector2 tex){
			position = pos;
			color = col;
			texCoords = tex;
		}

		Vector2 position;
		Color color;
		Vector2 texCoords;
	};

	/// Constructs an empty vertex array with default primitive type - Quads
	VertexArray2D();

	VertexArray2D(Render::Primitive::Type primitiveType, unsigned int vertexCount);

	/// Compute the bounds from the points in the array
	FloatRect getBounds();

	/// Clear the contents of the vertex array
	void clear();

	/// Append the vertex v to the current list
	void append(const Vertex& v);


	Vertex& operator[](unsigned int index);

	std::vector<Vertex> m_vertices;
	bool m_textured;

	Render::Primitive::Type geometryType;
};

#endif // RXVERTEXARRAY_H__
