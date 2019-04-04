#include "login_logic.h"

#include "logic_list.h"
#include "database.h"

LogInLogic* LogInLogic::s_login_logic;
QString LogInLogic::s_logic_name;

LogInLogic::LogInLogic()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::LogIn);
}

bool LogInLogic::setArguments(QStringList arguments, QString& error)
{
    if(!m_logic_args.setArgsQuery(arguments))
    {
        error = "Nieodpowiednia liczba argumentow";
        return false;
    }

    bool was_ok = false;
    m_select_gracze.m_login = m_logic_args.getArg(LogInLogicArgs::ArgumentsQuery::LOGIN, &was_ok).toString();
    if(!was_ok)
        return false;

    m_select_gracze.m_password = m_logic_args.getArg(LogInLogicArgs::ArgumentsQuery::PASSWORD, &was_ok).toString();
    if(!was_ok)
        return false;

    if(m_select_gracze.m_login.isEmpty())
    {
        error = "argument 'login' jest pusty";
        return false;
    }
    if(m_select_gracze.m_password.isEmpty())
    {
        error = "argument 'password' jest pusty";
        return false;
    }

    return true;
}

bool LogInLogic::work(QString dbConnectionNmae, QString& error)
{
    Database* db = Database::getInstance(dbConnectionNmae);

    if(!db->execQuery(&m_select_gracze))
    {
        error = db->getLastError();
        m_logic_args.setArg(LogInLogicArgs::ArgumentsResponse::WAS_OK, 0);
        m_logic_args.setArg(LogInLogicArgs::ArgumentsResponse::MESSAGE, "Błąd bazy danych.Skontaktuj się z Administratorem");
        m_logic_args.setArg(LogInLogicArgs::ArgumentsResponse::kERROR, error);
        m_logic_args.setArg(LogInLogicArgs::ArgumentsResponse::ID_GAMER, -1);
        return false;
    }

    m_logic_args.setArg(LogInLogicArgs::ArgumentsResponse::WAS_OK, m_select_gracze.getResult().was_ok);
    m_logic_args.setArg(LogInLogicArgs::ArgumentsResponse::MESSAGE, m_select_gracze.getResult().db_message);
    m_logic_args.setArg(LogInLogicArgs::ArgumentsResponse::ID_GAMER, m_select_gracze.getResult().id_gracza);

    return true;
}

QString LogInLogic::getResult()
{
    return m_logic_args.getResponse();
}

LogInLogic* LogInLogic::getTemplate()
{
    if(s_login_logic == nullptr)
        s_login_logic = new LogInLogic();

    return s_login_logic;
}

QString LogInLogic::getLogicName()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::LogIn);
    return s_logic_name;
}

LogInLogic::~LogInLogic()
{
    if(s_login_logic != nullptr)
        delete s_login_logic;
}
