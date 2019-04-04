#ifndef HERO_H
#define HERO_H

#include <QString>

#include "texture.h"
#include "opengl_object_2d.h"

class Hero : public OpenGLObject2D
{
public:
    struct HeroInfo
    {
        unsigned long long m_id;
        int m_max_health;
        int m_max_shield;
        int m_max_move;
        int m_attack;
        int m_defence;
        int m_level;
        int m_actual_exp;
        int m_exp_next_level;
        QString m_name;
        I_Texture* m_texture;

    };

    Hero();

    HeroInfo getInfo();
    void setInfo(const HeroInfo& info);
    void setInfo(); //TODO: setInfo from DB

protected:
    HeroInfo m_hero_info;

    Texture* m_texture;
};

#endif // HERO_H
