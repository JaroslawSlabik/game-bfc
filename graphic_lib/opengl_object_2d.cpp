#include "opengl_object_2d.h"

OpenGLObject2D::OpenGLObject2D()
{

}

void OpenGLObject2D::setPosition(float x, float y)
{
    m_model_matrix.data()[12] = x;
    m_model_matrix.data()[13] = y;
    m_model_matrix.data()[14] = 0.0f;
}

void OpenGLObject2D::setPosition(QVector2D position)
{
    m_model_matrix.data()[12] = position.x();
    m_model_matrix.data()[13] = position.y();
    m_model_matrix.data()[14] = 0.0f;
}

void OpenGLObject2D::setRotate(float angle)
{
    m_model_matrix.rotate(angle, 0.0f, 0.0f, 1.0f);
}

void OpenGLObject2D::setScale(float x, float y)
{
     m_model_matrix.data()[0] = x;
     m_model_matrix.data()[5] = y;
     m_model_matrix.data()[10] = 1.f;
}

void OpenGLObject2D::setScale(QVector2D scale)
{
    m_model_matrix.data()[0] = scale.x();
    m_model_matrix.data()[5] = scale.y();
    m_model_matrix.data()[10] = 1.f;
}

void OpenGLObject2D::setOrgin(float x, float y)
{

}

/**/

void OpenGLObject2D::translate(float x, float y)
{
    m_model_matrix.translate(x, y, 0.0f);
}

void OpenGLObject2D::translate(QVector2D position)
{
    m_model_matrix.translate(position.x(), position.y(), 0.0f);
}

void OpenGLObject2D::scale(float x, float y)
{
     m_model_matrix.scale(x, y, 1.0f);
}

void OpenGLObject2D::scale(QVector2D scale)
{
    m_model_matrix.scale(scale.x(), scale.y(), 1.0f);
}

/**/

QVector2D OpenGLObject2D::getPosition()
{
    return QVector2D(m_model_matrix.data()[12], m_model_matrix.data()[13]);
}

float OpenGLObject2D::getRotate()
{

}

QVector2D OpenGLObject2D::getScale()
{
    return QVector2D(m_model_matrix.data()[0], m_model_matrix.data()[5]);
}

QVector2D OpenGLObject2D::getOrgin()
{

}

/**/

bool OpenGLObject2D::pointOnObject(QVector2D point)
{
    if(!m_visible)
        return false;

    if(getPosition().x()                    <= point.x() &&
       getPosition().x() + getScale().x()   >= point.x() &&
       getPosition().y()                    <= point.y() &&
       getPosition().y() + getScale().y()   >= point.y())
        return true;

    return false;
}
