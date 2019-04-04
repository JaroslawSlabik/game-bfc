#ifndef CREATE_CREATURE_H
#define CREATE_CREATURE_H
#include "i_tool.h"
#include <QMap>
#include <QSqlDatabase>

class CreateCreature : public ITool
{
public:
    CreateCreature(const QSqlDatabase& database = QSqlDatabase::database());

    virtual bool setOptionFromComandLine(const QMap<QString, QString>& comand_line_option, QString& error) override;
    virtual bool work(QString& error) override;

private:
    QString m_name;
    QString m_description;
    int m_method_move;
    int m_health;
    int m_shield;
    int m_attack;
    int m_point_move;
    QString m_texture;

    QSqlDatabase m_database;
};

#endif // CREATE_CREATURE_H
