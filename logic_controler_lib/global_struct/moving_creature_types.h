#ifndef MOVING_CREATURE_TYPES_H
#define MOVING_CREATURE_TYPES_H
#include <QObject>

typedef enum
{
    walk = 1,
    fly,
    MovingPawnTypeCount
}MovingCreatureType_e;

Q_DECLARE_METATYPE(MovingCreatureType_e);

#endif // MOVING_CREATURE_TYPES_H
