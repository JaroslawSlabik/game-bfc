#ifndef PROGRES_BAR_H
#define PROGRES_BAR_H

#include "i_texture.h"
#include "opengl_object_2d.h"
#include "shader.h"

class ProgresBar
{
public:
    ProgresBar();
    ProgresBar(float status, const QVector2D& pos, const QVector2D& size = QVector2D(100,20));
    ~ProgresBar();

    bool setStatus(float status);
    void setPosition(const QVector2D& pos);
    void setSize(const QVector2D& size);
    void setTextureBackground(I_Texture* texture);
    void setTextureStatus(I_Texture* texture);
    void setColorBackground(const QColor& color);
    void setColorStatus(const QColor& color);

    float getStatus();

    bool draw(Shader *shader);

private:
    float m_actual_status = 0.0f;

    OpenGLObject2D* m_background;
    OpenGLObject2D* m_status;

    int m_lenght;
};

#endif // PROGRES_BAR_H
