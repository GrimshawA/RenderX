#ifndef RXMESH_H__
#define RXMESH_H__

#include <bitcore/Config.h>
#include "RxVertexArray.h"
#include "RxIndexArray.h"
#include "RxVertexDecl.h"
#include <vector>

/**
    \class RxMesh
    \brief In memory representation of one mesh
*/
class DAEVA_API RxMesh
{
public:
    explicit RxMesh();

private:
    RxVertexArray m_geometry;
    RxIndexArray  m_indices;
    RxVertexDecl  m_decl;
};
#endif // RXMESH_H__
