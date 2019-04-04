#ifndef PAWN_H
#define PAWN_H

#include <QObject>

#include "hero.h"
#include "shader.h"
#include "opengl_object_2d.h"
#include "progres_bar.h"
#include "creature.h"
#include "power_icon.h"
#include "../logic_controler_lib/global_struct/creature_info.h"
#include "../logic_controler_lib/global_struct/elements.h"

class Pawn : public QObject
{
public:
    explicit Pawn(QObject* parent = 0);
    explicit Pawn(CreatureInfo info, QObject* parent = 0);

    CreatureInfo getInfo();
    void setInfo(CreatureInfo info);

    void setPosition(float x, float y);

    void setSize(float x, float y);
    QVector2D getSize();

    bool draw(Shader *shader);

private:
    QVector2D m_position;
    QVector2D m_size;

    int m_actual_health;
    int m_actual_shield;
    int m_actual_move;

    OpenGLObject2D* m_background;

    ProgresBar* m_health_bar;
    ProgresBar* m_shield_bar;

    Creature* m_creature = nullptr;
    ElementIcon* m_element_icon = nullptr;

    void resize();

    Q_OBJECT
};

#endif // PAWN_H
