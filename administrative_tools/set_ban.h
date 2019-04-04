#ifndef SET_BAN_H
#define SET_BAN_H
#include "i_tool.h"
#include <QSqlDatabase>

class SetBan : public ITool
{
public:
    SetBan(const QSqlDatabase& database = QSqlDatabase::database());

    virtual bool setOptionFromComandLine(const QMap<QString, QString>& comand_line_option, QString& error) override;
    virtual bool work(QString& error) override;

private:
    qlonglong m_id_player;
    QString m_date_from;
    QString m_date_to;

    QSqlDatabase m_database;
};

#endif // SET_BAN_H
