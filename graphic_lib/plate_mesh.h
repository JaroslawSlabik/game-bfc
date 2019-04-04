#ifndef PLATE_MESH_H
#define PLATE_MESH_H

#include "i_mesh.h"

class PlateMesh : public I_Mesh
{
public:
    PlateMesh();
    ~PlateMesh();

private:
    static I_Mesh* mesh;

    virtual void initMesh() override;

};

#endif // PLATE_MESH_H
