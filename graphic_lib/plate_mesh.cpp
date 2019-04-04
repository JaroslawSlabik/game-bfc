#include "plate_mesh.h"

I_Mesh* PlateMesh::mesh = nullptr;

PlateMesh::PlateMesh()
{
    indexBuf = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    arrayBuf = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);

    indexBuf.create();
    arrayBuf.create();

    initMesh();
}

PlateMesh::~PlateMesh()
{
    indexBuf.destroy();
    arrayBuf.destroy();
}

void PlateMesh::initMesh()
{
    I_Mesh::VertexData vertices[] = {
        // Vertex data for face 0
        {QVector3D( 1.0f, 0.0f, 0.0f), QVector3D(255,255,255), QVector4D(255,255,255, 255), QVector2D(1.0f, 1.0f), QVector3D()}, // v0
        {QVector3D(0.0f, 0.0f, 0.0f), QVector3D(255,255,255), QVector4D(255,255,255, 255), QVector2D(0.0f, 1.0f), QVector3D()},  // v1
        {QVector3D( 1.0f,  1.0f, 0.0f), QVector3D(255,255,255), QVector4D(255,255,255, 255), QVector2D(1.0f, 0.0f), QVector3D()}, // v2
        {QVector3D(0.0f,  1.0f, 0.0f), QVector3D(255,255,255), QVector4D(255,255,255, 255), QVector2D(0.0f, 0.0f), QVector3D()},  // v3
    };

    GLushort indices[] = {
         0,  1,  2,  3,  3  // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
    };

    indexBuf.bind();
    indexBuf.allocate(indices, 5 * sizeof(GLushort));
    indexBuf.release();

    arrayBuf.bind();
    arrayBuf.allocate(vertices, 4 * sizeof(I_Mesh::VertexData));
    arrayBuf.release();

    mode = GL_TRIANGLE_STRIP;
    count = 4;
}
