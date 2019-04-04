#include "i_mesh.h"

bool I_Mesh::bindMesh()
{
    if(!arrayBuf.isCreated() || !indexBuf.isCreated())
        return false;

    isBind = (arrayBuf.bind() && indexBuf.bind())? true : isBind;

    return isBind;
}

bool I_Mesh::releaseMesh()
{
    if(!arrayBuf.isCreated() || !indexBuf.isCreated())
        return false;

    arrayBuf.release();
    indexBuf.release();

    isBind = (isBind)? false : isBind;

    return !isBind;
}

/**/

void I_Mesh::setFill(bool fill)
{
    if(fill)
    {
        if(mode == GL_LINE_STRIP)
            mode = GL_TRIANGLE_STRIP;
    }
    else
    {
        if(mode == GL_TRIANGLE_STRIP)
            mode = GL_LINE_STRIP;
    }
}

/**/

int I_Mesh::getSizeVertexData()
{
    return sizeof(VertexData);
}

GLenum I_Mesh::getMode()
{
    return mode;
}

GLsizei I_Mesh::getCountVertex()
{
    return count;
}

QOpenGLBuffer I_Mesh::getIndexBuffer()
{
    return indexBuf;
}

QOpenGLBuffer I_Mesh::getVertexBuffer()
{
    return arrayBuf;
}

int I_Mesh::getOffsetPosition()
{
    int offset = 0;
    return offset;
}

int I_Mesh::getOffsetObjectID()
{
    int offset = 0;
    offset += sizeof(QVector3D);

    return offset;
}

int I_Mesh::getOffsetBaseColor()
{
    int offset = 0;
    offset += sizeof(QVector3D);
    offset += sizeof(QVector3D);

    return offset;
}

int I_Mesh::getOffsetTexCoord()
{
    int offset = 0;
    offset += sizeof(QVector3D);
    offset += sizeof(QVector3D);
    offset += sizeof(QVector4D);

    return offset;
}

int I_Mesh::getOffsetNormal()
{
    int offset = 0;
    offset += sizeof(QVector3D);
    offset += sizeof(QVector3D);
    offset += sizeof(QVector4D);
    offset += sizeof(QVector2D);

    return offset;
}

int I_Mesh::getSizePosition()
{
    return 3;
}

int I_Mesh::getSizeObjectID()
{
    return 3;
}

int I_Mesh::getSizeBaseColor()
{
    return 4;
}

int I_Mesh::getSizeTexCoord()
{
    return 2;
}

int I_Mesh::getSizeNormal()
{
    return 3;
}
