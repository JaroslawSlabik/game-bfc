#include "opengl_object_3d.h"

OpenGLObject3D::OpenGLObject3D()
{

}

void OpenGLObject3D::setPosition(float x, float y, float z)
{
    m_model_matrix.translate(x, y, z);
}

void OpenGLObject3D::setPosition(QVector3D position)
{
    m_model_matrix.translate(position);
}

void OpenGLObject3D::setRotate(float angle, float x, float y, float z)
{
    m_model_matrix.rotate(angle, x, y, z);
}

void OpenGLObject3D::setRotate(float angle, QVector3D rotate)
{
    m_model_matrix.rotate(angle, rotate);
}

void OpenGLObject3D::setRotate(QQuaternion rotate)
{
    m_model_matrix.rotate(rotate);
}

void OpenGLObject3D::setScale(float x, float y, float z)
{
    m_model_matrix.scale(x, y, z);
}

void OpenGLObject3D::setScale(QVector3D scale)
{
    m_model_matrix.scale(scale);
}

void OpenGLObject3D::setOrgin(float x, float y, float z)
{

}

/**/

QVector3D OpenGLObject3D::getPosition()
{

}

QQuaternion OpenGLObject3D::getRotate()
{

}

QVector3D OpenGLObject3D::getScale()
{

}

QVector3D OpenGLObject3D::getOrgin()
{

}

/**/

bool OpenGLObject3D::pointOnObject(QVector2D point)
{

}
