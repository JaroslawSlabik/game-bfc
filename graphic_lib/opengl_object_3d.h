#ifndef OPENGL_OBJECT_3D_H
#define OPENGL_OBJECT_3D_H

#include "opengl_object.h"

class OpenGLObject3D : public OpenGLObject
{
public:
    OpenGLObject3D();

    void setPosition(float x, float y, float z);
    void setPosition(QVector3D position);
    void setRotate(float angle, float x, float y, float z);
    void setRotate(float angle, QVector3D rotate);
    void setRotate(QQuaternion rotate);
    void setScale(float x, float y, float z);
    void setScale(QVector3D scale);
    void setOrgin(float x, float y, float z);

    /**/

    QVector3D getPosition();
    QQuaternion getRotate();
    QVector3D getScale();
    QVector3D getOrgin();

    /**/

    virtual bool pointOnObject(QVector2D point) override;

};

#endif // OPENGL_OBJECT_3D_H
