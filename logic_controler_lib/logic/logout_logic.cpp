#include "logout_logic.h"

#include "logic_list.h"
#include "database.h"

LogOutLogic* LogOutLogic::s_logout_logic;
QString LogOutLogic::s_logic_name;

LogOutLogic::LogOutLogic()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::LogOut);
}

bool LogOutLogic::setArguments(QStringList arguments, QString& error)
{
    if(ArgumentNames::COUNT != arguments.size())
    {
        error = "Nie odpowiednia liczba argumentow";
        return false;
    }

    //m_select_gracze.m_login = arguments.at(ArgumentNames::ID_GRACZA);
    //m_select_gracze.m_password = arguments.at(ArgumentNames::PASSWORD);
    //
    //if(m_select_gracze.m_login.isEmpty())
    //{
    //    error = "argument 'login' jest pusty";
    //    return false;
    //}
    //if(m_select_gracze.m_password.isEmpty())
    //{
    //    error = "argument 'password' jest pusty";
    //    return false;
    //}

    return true;
}

bool LogOutLogic::work(QString dbConnectionNmae, QString& error)
{
    Database* db = Database::getInstance(dbConnectionNmae);

    //if(!db->execQuery(&m_select_gracze))
    //{
    //    error = db->getLastError();
    //    result += "0;Błąd bazy danych.Skontaktuj się z Administratorem;" + error + ";";
    //    return false;
    //}
    //
    //result = QString::number(m_select_gracze.getResult().was_ok) + ";" +
    //         m_select_gracze.getResult().db_message + ";" +
    //         QString::number(m_select_gracze.getResult().id_gracza);

    return true;
}

QString LogOutLogic::getResult()
{
    return s_logic_name + ";" + result;
}

LogOutLogic* LogOutLogic::getTemplate()
{
    if(s_logout_logic == nullptr)
        s_logout_logic = new LogOutLogic();

    return s_logout_logic;
}

QString LogOutLogic::getLogicName()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::LogOut);
    return s_logic_name;
}

LogOutLogic::~LogOutLogic()
{
    if(s_logout_logic != nullptr)
        delete s_logout_logic;
}
