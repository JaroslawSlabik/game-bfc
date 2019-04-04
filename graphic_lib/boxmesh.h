#ifndef BOXMESH_H
#define BOXMESH_H

#include "i_mesh.h"

class BoxMesh : public I_Mesh
{
private:
    BoxMesh();
    ~BoxMesh();

    static I_Mesh* mesh;

    virtual void initMesh() override;

public:
    static I_Mesh* getInstance();
    static void destroy();
};

#endif // BOXMESH_H
