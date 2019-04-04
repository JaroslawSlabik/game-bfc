#ifndef OPENGL_OBJECT_2D_H
#define OPENGL_OBJECT_2D_H

#include "opengl_object.h"

class OpenGLObject2D : public OpenGLObject
{
public:
    OpenGLObject2D();

    void setPosition(float x, float y);
    void setPosition(QVector2D position);
    void setRotate(float angle);
    void setScale(float x, float y);
    void setScale(QVector2D scale);
    void setOrgin(float x, float y);

    /**/

    void translate(float x, float y);
    void translate(QVector2D position);
    void scale(float x, float y);
    void scale(QVector2D scale);

    /**/

    QVector2D getPosition();
    float getRotate();
    QVector2D getScale();
    QVector2D getOrgin();

    /**/

    virtual bool pointOnObject(QVector2D point) override;
};

#endif // OPENGL_OBJECT_2D_H
