#include "create_player.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

CreatePlayer::CreatePlayer(const QSqlDatabase& database)
{
    m_database = database;
}

bool CreatePlayer::setOptionFromComandLine(const QMap<QString, QString>& comand_line_option, QString& error)
{
    qDebug() << "You choice tool: CreatePlayer";

    m_name = comand_line_option.value("n", "");
    if(true == m_name.isEmpty())
    {
        error += "Name is empty";
        return false;
    }

    m_surname = comand_line_option.value("s", "");
    if(true == m_surname.isEmpty())
    {
        error += "Surname is empty";
        return false;
    }

    m_email = comand_line_option.value("e", "");
    if(true == m_email.isEmpty())
    {
        error += "Email is empty";
        return false;
    }

    m_password = comand_line_option.value("p", "");
    if(true == m_password.isEmpty())
    {
        error += "Password is empty";
        return false;
    }

    return true;
}

bool CreatePlayer::work(QString& error)
{
    QSqlQuery query(m_database);
    QString exec_query = QString("SELECT was_ok_ret, message_ret FROM registration_player('%1', '%2', '%3', '%4');")
            .arg(m_name)
            .arg(m_surname)
            .arg(m_email)
            .arg(m_password);
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
        qDebug() << "Player is not added: " << query.value("message_ret").toString();
        return false;
    }

    qDebug() << "Player is added";

    return true;
}
