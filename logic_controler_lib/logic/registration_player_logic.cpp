#include "registration_player_logic.h"

#include "logic_list.h"
#include "database.h"
#include "global_struct/player_info.h"

RegistrationPlayerLogic* RegistrationPlayerLogic::s_login_logic;
QString RegistrationPlayerLogic::s_logic_name;


RegistrationPlayerLogic::RegistrationPlayerLogic()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::RegistrationPlayerLogic);
}

bool RegistrationPlayerLogic::setArguments(QStringList arguments, QString& error)
{
    if(!m_logic_args.setArgsQuery(arguments))
    {
        error = "Nie odpowiednia liczba argumentow";
        m_logic_args.setArg(RegistrationPlayerLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(RegistrationPlayerLogicArgs::ArgumentsResponse::MESSAGE, error);
        m_logic_args.setArg(RegistrationPlayerLogicArgs::ArgumentsResponse::STATUS, -1);
        return false;
    }

    m_registration_player.m_name = m_logic_args.getArg(RegistrationPlayerLogicArgs::ArgumentsQuery::NAME).toString();
    if(true == m_registration_player.m_name.isEmpty())
    {
        error = "argument 'name' jest pusty";
        m_logic_args.setArg(RegistrationPlayerLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(RegistrationPlayerLogicArgs::ArgumentsResponse::MESSAGE, error);
        m_logic_args.setArg(RegistrationPlayerLogicArgs::ArgumentsResponse::STATUS, -1);
        return false;
    }

    m_registration_player.m_surname = m_logic_args.getArg(RegistrationPlayerLogicArgs::ArgumentsQuery::SURNAME).toString();
    if(true == m_registration_player.m_surname.isEmpty())
    {
        error = "argument 'surname' jest pusty";
        m_logic_args.setArg(RegistrationPlayerLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(RegistrationPlayerLogicArgs::ArgumentsResponse::MESSAGE, error);
        m_logic_args.setArg(RegistrationPlayerLogicArgs::ArgumentsResponse::STATUS, -1);
        return false;
    }

    m_registration_player.m_email = m_logic_args.getArg(RegistrationPlayerLogicArgs::ArgumentsQuery::EMAIL).toString();
    if(true == m_registration_player.m_email.isEmpty())
    {
        error = "argument 'email' jest pusty";
        m_logic_args.setArg(RegistrationPlayerLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(RegistrationPlayerLogicArgs::ArgumentsResponse::MESSAGE, error);
        m_logic_args.setArg(RegistrationPlayerLogicArgs::ArgumentsResponse::STATUS, -1);
        return false;
    }

    m_registration_player.m_password = m_logic_args.getArg(RegistrationPlayerLogicArgs::ArgumentsQuery::PASSWORD).toString();
    if(true == m_registration_player.m_password.isEmpty())
    {
        error = "argument 'password' jest pusty";
        m_logic_args.setArg(RegistrationPlayerLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(RegistrationPlayerLogicArgs::ArgumentsResponse::MESSAGE, error);
        m_logic_args.setArg(RegistrationPlayerLogicArgs::ArgumentsResponse::STATUS, -1);
        return false;
    }

    return true;
}

bool RegistrationPlayerLogic::work(QString dbConnectionNmae, QString& error)
{
    Database* db = Database::getInstance(dbConnectionNmae);

    if(false == db->execQuery(&m_registration_player))
    {
        error = db->getLastError();
        m_logic_args.setArg(RegistrationPlayerLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(RegistrationPlayerLogicArgs::ArgumentsResponse::MESSAGE, "Błąd bazy danych");
        m_logic_args.setArg(RegistrationPlayerLogicArgs::ArgumentsResponse::STATUS, -1);
        return false;
    }

    m_logic_args.setArg(RegistrationPlayerLogicArgs::ArgumentsResponse::WAS_OK, m_registration_player.getResult().was_ok);
    m_logic_args.setArg(RegistrationPlayerLogicArgs::ArgumentsResponse::STATUS, m_registration_player.getResult().status);
    m_logic_args.setArg(RegistrationPlayerLogicArgs::ArgumentsResponse::MESSAGE, m_registration_player.getResult().db_message);

    return true;
}

QString RegistrationPlayerLogic::getResult()
{
    return m_logic_args.getResponse();
}

RegistrationPlayerLogic* RegistrationPlayerLogic::getTemplate()
{
    if(s_login_logic == nullptr)
        s_login_logic = new RegistrationPlayerLogic();

    return s_login_logic;
}

QString RegistrationPlayerLogic::getLogicName()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::RegistrationPlayerLogic);
    return s_logic_name;
}

RegistrationPlayerLogic::~RegistrationPlayerLogic()
{
    if(s_login_logic != nullptr)
        delete s_login_logic;
}

