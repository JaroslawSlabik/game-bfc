#include "set_ban.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

SetBan::SetBan(const QSqlDatabase& database)
{
    m_database = database;
}

bool SetBan::setOptionFromComandLine(const QMap<QString, QString>& comand_line_option, QString& error)
{
    qDebug() << "You choice tool: SetBan";

    bool was_ok = false;

    m_id_player = comand_line_option.value("i", "").toLongLong(&was_ok);
    if(1 > m_id_player || false == was_ok)
    {
        error += "Id player is empty";
        return false;
    }

    m_date_from = comand_line_option.value("f", "");
    if(true == m_date_from.isEmpty())
    {
        error += "Date from is empty";
        return false;
    }

    m_date_to = comand_line_option.value("d", "");
    if(true == m_date_to.isEmpty())
    {
        error += "Date to is empty";
        return false;
    }

    return true;
}

bool SetBan::work(QString& error)
{
    QSqlQuery query(m_database);
    QString exec_query = QString("SELECT was_ok_ret, message_ret FROM set_ban(%1, '%2', '%3');")
            .arg(m_id_player)
            .arg(m_date_from)
            .arg(m_date_to);
    if(false == query.exec(exec_query))
    {
        error = "Error during exec query: " + exec_query + "\nError: " + query.lastError().text();
        return false;
    }

    if(false == query.first())
    {
        error = "Error during exec query: " + exec_query + "\nError: " + query.lastError().text();
        return false;
    }

    if(false == query.value("was_ok_ret").toBool())
    {
        qDebug() << "Ban is not set: " << query.value("message_ret").toString();
        return false;
    }

    qDebug() << "Ban is set";

    return true;
}
