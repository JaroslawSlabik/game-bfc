#ifndef CREATE_BATTLE_MAP_H
#define CREATE_BATTLE_MAP_H
#include "i_tool.h"
#include <QMap>
#include <QSqlDatabase>

class CreateBattleMap : public ITool
{
public:
    CreateBattleMap(const QSqlDatabase& database = QSqlDatabase::database());

    virtual bool setOptionFromComandLine(const QMap<QString, QString>& comand_line_option, QString& error) override;
    virtual bool work(QString& error) override;

private:
    QString m_name;
    QString m_description;
    QString m_map;
    int m_id_element;
    QString m_texture;

    QSqlDatabase m_database;

    QString convertMapToMyType(QString path_to_map, bool* was_ok = nullptr);
};

#endif // CREATE_BATTLE_MAP_H
