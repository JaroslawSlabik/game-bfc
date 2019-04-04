#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#include "shader.h"

class GeometryEngine : protected QOpenGLFunctions
{
public:
    GeometryEngine();
    virtual ~GeometryEngine();

    void drawCubeGeometry(Shader *shader, QOpenGLShaderProgram* program);

private:
    void initCubeGeometry();

    ///QOpenGLBuffer arrayBuf;
    ///QOpenGLBuffer indexBuf;
};

#endif // GEOMETRYENGINE_H
