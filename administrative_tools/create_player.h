#ifndef CREATE_PLAYER_H
#define CREATE_PLAYER_H
#include "i_tool.h"
#include <QSqlDatabase>

class CreatePlayer : public ITool
{
public:
    CreatePlayer(const QSqlDatabase& database = QSqlDatabase::database());

    virtual bool setOptionFromComandLine(const QMap<QString, QString>& comand_line_option, QString& error) override;
    virtual bool work(QString& error) override;

private:
    QString m_name;
    QString m_surname;
    QString m_email;
    QString m_password;

    QSqlDatabase m_database;
};

#endif // CREATE_PLAYER_H
