#ifndef RXMODEL_H__
#define RXMODEL_H__

#include "RxMesh.h"

/*
 * One multi-part model which can have multiple meshes with their own materials
 */
class RxModel
{
public:

    std::vector<RxMesh> m_meshes;
}

#endif // RXMODEL_H__
