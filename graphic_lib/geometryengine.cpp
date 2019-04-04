#include "geometryengine.h"

#include <QVector2D>
#include <QVector3D>
#include <QColor>
#include "boxmesh.h"

struct VertexData
{
    QVector3D   position;
    QColor      objectID;
    QColor      baseColor;
    QVector2D   texCoord;
};



GeometryEngine::GeometryEngine()
{
    initializeOpenGLFunctions();
}

GeometryEngine::~GeometryEngine()
{

}

void GeometryEngine::drawCubeGeometry(Shader *shader, QOpenGLShaderProgram* program)
{
    I_Mesh* mesh = BoxMesh::getInstance();

    // Tell OpenGL which VBOs to use
    //shader->bindShader();
    mesh->bindMesh();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    //int vertexLocation = program->attributeLocation("a_position");
    //program->enableAttributeArray(vertexLocation);
    //program->setAttributeBuffer("a_position",GL_FLOAT, offset, 3, mesh->getSizeVertexData());
    //program->setAttributeBuffer(vertexLocation, GL_FLOAT, mesh->getOffsetPosition(), mesh->getSizePosition(), mesh->getSizeVertexData());

    if(!shader->setLocateVertexPositionData(mesh))
        qDebug() << "EEEE" ;

    // Offset for texture coordinate
    offset += sizeof(QVector3D);
    offset += sizeof(QColor);
    offset += sizeof(QColor);

    //nalozyc baseColor
    //shader->setLocateVertexColorData(mesh);

    //tylko gdy textura jest wczytana
    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    //int texcoordLocation = program->attributeLocation("a_texcoord");
    //program->enableAttributeArray(texcoordLocation);
    //program->setAttributeBuffer(texcoordLocation, GL_FLOAT, mesh->getOffsetTexCoord(), mesh->getSizeTexCoord(), mesh->getSizeVertexData());
    //program->setAttributeBuffer("a_texcoord", GL_FLOAT, offset, 2, mesh->getSizeVertexData());

    if(!shader->setLocateVertexTextureCoordinateData(mesh))
        qDebug() << "EEE";

    // Draw cube geometry using indices from VBO 1
    mesh->drawMesh();

    //glReadPixels();

    mesh->releaseMesh();
}
