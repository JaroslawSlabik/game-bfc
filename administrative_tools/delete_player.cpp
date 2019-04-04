#include "delete_player.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

DeletePlayer::DeletePlayer(const QSqlDatabase& database)
{
    m_database = database;
}

bool DeletePlayer::setOptionFromComandLine(const QMap<QString, QString>& comand_line_option, QString& error)
{
    qDebug() << "You choice tool: DeletePlayer";

    bool was_ok = false;

    m_id_player = comand_line_option.value("i", "").toLongLong(&was_ok);
    if(1 > m_id_player || false == was_ok)
    {
        error += "Id player is empty";
        return false;
    }

    return true;
}

bool DeletePlayer::work(QString& error)
{
    QSqlQuery query(m_database);
    QString exec_query = QString("SELECT was_ok_ret, message_ret FROM delete_player(%1);")
            .arg(m_id_player);
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
        qDebug() << "Player is not deleted: " << query.value("message_ret").toString();
        return false;
    }

    qDebug() << "Player is deleted";

    return true;
}
