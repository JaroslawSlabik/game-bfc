#ifndef ELEMENTS_H
#define ELEMENTS_H
#include <QHash>
#include <QString>
#include <QObject>

typedef enum
{
    earth = 1,
    water,
    fire,
    air,
    count
}ElementType_e;

Q_DECLARE_METATYPE(ElementType_e);

static const QHash<ElementType_e, QString> s_elementTypeHash = [] () -> const QHash<ElementType_e, QString> {
    QHash<ElementType_e, QString> d;
    d.insert(ElementType_e::earth, QString("ZIEMIA"));
    d.insert(ElementType_e::water, QString("WODA"));
    d.insert(ElementType_e::fire, QString("OGIEŃ"));
    d.insert(ElementType_e::air, QString("POWIETRZE"));
    return d;
} ();

#endif // ELEMENTS_H
