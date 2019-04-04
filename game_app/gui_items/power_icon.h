#ifndef POWER_ICON_H
#define POWER_ICON_H

#include "texture.h"
#include "plate_mesh.h"
#include "opengl_object_2d.h"
#include "shader.h"
#include "../logic_controler_lib/global_struct/elements.h"

class ElementIcon : public OpenGLObject2D
{
public:
    ElementIcon();
    ElementIcon(ElementType_e element, const QVector2D& pos, const QVector2D& size = QVector2D(100,20));
    ~ElementIcon();

    void setElement(ElementType_e element);

    ElementType_e getElement();

private:
    ElementType_e m_element;
    Texture* m_texture;
    void initPowerTextureRect();

    struct PowerTextureRect
    {
        ElementType_e element;
        int x;
        int y;
        int height;
        int width;
    }powerTextureRect[ElementType_e::count];
};

#endif // POWER_ICON_H
