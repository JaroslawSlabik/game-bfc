#ifndef CREATURE_INFO_H
#define CREATURE_INFO_H
#include <QString>
#include <QObject>

#include "elements.h"
#include "moving_creature_types.h"

struct CreatureInfo
{
    CreatureInfo()
    {
        m_id = -1;
        m_name = "";
        m_description = "";
        m_texture = QByteArray();
        m_health = 0;
        m_shield = 0;
        m_attack = 0;
        m_point_of_move = 0;

        m_actual_health = 0;
        m_actual_shield = 0;
        m_actual_move = 0;

        m_enemy = false;
        m_element = ElementType_e::earth;
        m_move_type = MovingCreatureType_e::walk;
    }

    qlonglong m_id;
    QString m_name;
    QString m_description;
    QByteArray m_texture;
    int m_health;
    int m_shield;
    int m_attack;
    int m_point_of_move;

    int m_actual_health;
    int m_actual_shield;
    int m_actual_move;

    bool m_enemy;
    ElementType_e m_element;
    MovingCreatureType_e m_move_type;
};

Q_DECLARE_METATYPE(CreatureInfo)

#endif // CREATURE_INFO_H
