#ifndef I_MESH_H
#define I_MESH_H

#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QColor>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>

class I_Mesh : protected QOpenGLFunctions
{
private:
    bool isBind = false;

protected:
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
    GLenum mode;
    GLsizei count;

    struct VertexData
    {
        QVector3D   position;
        QVector3D   objectID;
        QVector4D   baseColor;
        QVector2D   texCoord;
        QVector3D   normal;
    };


public:
    virtual bool bindMesh();
    virtual bool releaseMesh();

    /**/

    virtual void setFill(bool fill = true);

    /**/

    virtual int getSizeVertexData();
    virtual GLenum getMode();
    virtual GLsizei getCountVertex();
    virtual QOpenGLBuffer getIndexBuffer();
    virtual QOpenGLBuffer getVertexBuffer();
    virtual int getOffsetPosition();
    virtual int getOffsetObjectID();
    virtual int getOffsetBaseColor();
    virtual int getOffsetTexCoord();
    virtual int getOffsetNormal();
    virtual int getSizePosition();
    virtual int getSizeObjectID();
    virtual int getSizeBaseColor();
    virtual int getSizeTexCoord();
    virtual int getSizeNormal();

    /**/

    virtual void initMesh() = 0;
};
#endif // I_MESH_H
