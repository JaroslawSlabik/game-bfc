#ifndef CREATURE_H
#define CREATURE_H

#include <QString>
#include "texture.h"
#include "opengl_object_2d.h"
#include "../logic_controler_lib/global_struct/creature_info.h"

class Creature : public OpenGLObject2D
{
public:
    Creature();
    Creature(const CreatureInfo& info);
    ~Creature();
    CreatureInfo getInfo();
    void setInfo(const CreatureInfo& info);
    virtual bool draw(Shader* shader) override;

protected:
    CreatureInfo m_info;
    Texture* m_texture = nullptr;
};

#endif // CREATURE_H
