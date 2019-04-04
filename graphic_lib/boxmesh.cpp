#include "boxmesh.h"

I_Mesh* BoxMesh::mesh = nullptr;

BoxMesh::BoxMesh()
{
    indexBuf = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    arrayBuf = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);

    indexBuf.create();
    arrayBuf.create();
}

BoxMesh::~BoxMesh()
{
    indexBuf.destroy();
    arrayBuf.destroy();
}

void BoxMesh::initMesh()
{
    I_Mesh::VertexData vertices[] = {
        // Vertex data for face 0
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector3D(255,255,255), QVector4D(255,255,255, 255), QVector2D(0.0f, 0.0f), QVector3D()},  // v0
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector3D(255,255,255), QVector4D(255,255,255, 255), QVector2D(0.33f, 0.0f), QVector3D()}, // v1
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector3D(255,255,255), QVector4D(255,255,255, 255), QVector2D(0.0f, 0.5f), QVector3D()},  // v2
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector3D(255,255,255), QVector4D(255,255,255, 255), QVector2D(0.33f, 0.5f), QVector3D()}, // v3

        // Vertex data for face 1
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector3D(255,255,255), QVector4D(255,255,255, 255), QVector2D( 0.0f, 0.5f), QVector3D()}, // v4
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector3D(255,255,255), QVector4D(255,255,255, 255), QVector2D(0.33f, 0.5f), QVector3D()}, // v5
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector3D(255,255,255), QVector4D(255,255,255, 255), QVector2D(0.0f, 1.0f), QVector3D()},  // v6
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector3D(255,255,255), QVector4D(255,255,255, 255), QVector2D(0.33f, 1.0f), QVector3D()}, // v7

        // Vertex data for face 2
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector3D(255,255,255), QVector4D(255,255,255, 255), QVector2D(0.66f, 0.5f), QVector3D()}, // v8
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector3D(255,255,255), QVector4D(255,255,255, 255), QVector2D(1.0f, 0.5f), QVector3D()},  // v9
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector3D(255,255,255), QVector4D(255,255,255, 255), QVector2D(0.66f, 1.0f), QVector3D()}, // v10
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector3D(255,255,255), QVector4D(255,255,255, 255), QVector2D(1.0f, 1.0f), QVector3D()},  // v11

        // Vertex data for face 3
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector3D(255,255,255), QVector4D(255,255,255, 255), QVector2D(0.66f, 0.0f), QVector3D()}, // v12
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector3D(255,255,255), QVector4D(255,255,255, 255), QVector2D(1.0f, 0.0f), QVector3D()},  // v13
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector3D(255,255,255), QVector4D(255,255,255, 255), QVector2D(0.66f, 0.5f), QVector3D()}, // v14
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector3D(255,255,255), QVector4D(255,255,255, 255), QVector2D(1.0f, 0.5f), QVector3D()},  // v15

        // Vertex data for face 4
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector3D(255,255,255), QVector4D(255,255,255, 255), QVector2D(0.33f, 0.0f), QVector3D()}, // v16
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector3D(255,255,255), QVector4D(255,255,255, 255), QVector2D(0.66f, 0.0f), QVector3D()}, // v17
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector3D(255,255,255), QVector4D(255,255,255, 255), QVector2D(0.33f, 0.5f), QVector3D()}, // v18
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector3D(255,255,255), QVector4D(255,255,255, 255), QVector2D(0.66f, 0.5f), QVector3D()}, // v19

        // Vertex data for face 5
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector3D(255,255,255), QVector4D(255,255,255, 255), QVector2D(0.33f, 0.5f), QVector3D()}, // v20
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector3D(255,255,255), QVector4D(255,255,255, 255), QVector2D(0.66f, 0.5f), QVector3D()}, // v21
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector3D(255,255,255), QVector4D(255,255,255, 255), QVector2D(0.33f, 1.0f), QVector3D()}, // v22
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector3D(255,255,255), QVector4D(255,255,255, 255), QVector2D(0.66f, 1.0f), QVector3D()}  // v23
    };

    GLushort indices[] = {
         0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };

    indexBuf.bind();
    indexBuf.allocate(indices, 34 * sizeof(GLushort));
    indexBuf.release();

    arrayBuf.bind();
    arrayBuf.allocate(vertices, 24 * sizeof(I_Mesh::VertexData));
    arrayBuf.release();

    mode = GL_TRIANGLE_STRIP;
    count = 34;
}

I_Mesh* BoxMesh::getInstance()
{
    if(!mesh)
    {
        mesh = new BoxMesh();
        mesh->initMesh();
        return mesh;
    }

    return mesh;
}

void BoxMesh::destroy()
{
    if(mesh)
    {
        delete mesh;
        mesh = nullptr;
    }
}
