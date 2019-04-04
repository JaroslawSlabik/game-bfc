#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H
#include <QHash>
#include <QString>
#include <QObject>

typedef enum
{
    health = 0,
    shield,
    attack,
    move,
    AttributeTypeCount
}AttributeType_e;

Q_DECLARE_METATYPE(AttributeType_e);

static const QHash<AttributeType_e, QString> s_attributeTypeHash = [] () -> const QHash<AttributeType_e, QString> {
    QHash<AttributeType_e, QString> d;
    d.insert(AttributeType_e::health, QString("Zdrowie"));
    d.insert(AttributeType_e::shield, QString("Obrona"));
    d.insert(AttributeType_e::attack, QString("Atak"));
    d.insert(AttributeType_e::move, QString("Ruchy"));
    return d;
} ();

#endif // ATTRIBUTES_H
