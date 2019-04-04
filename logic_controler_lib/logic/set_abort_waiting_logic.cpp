#include "set_abort_waiting_logic.h"

#include "logic_list.h"
#include "database.h"
#include "global_struct/player_info.h"

SetAbortWaitingLogic* SetAbortWaitingLogic::s_login_logic;
QString SetAbortWaitingLogic::s_logic_name;


SetAbortWaitingLogic::SetAbortWaitingLogic()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::SetAbortWaitingLogic);
}

bool SetAbortWaitingLogic::setArguments(QStringList arguments, QString& error)
{
    if(!m_logic_args.setArgsQuery(arguments))
    {
        error = "Nie odpowiednia liczba argumentow";
        m_logic_args.setArg(SetAbortWaitingLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(SetAbortWaitingLogicArgs::ArgumentsResponse::MESSAGE, error);
        m_logic_args.setArg(SetAbortWaitingLogicArgs::ArgumentsResponse::STATUS, -1);
        return false;
    }

    bool was_ok = false;

   m_set_abort_waiting.m_id_player = m_logic_args.getArg(SetAbortWaitingLogicArgs::ArgumentsQuery::ID_PLAYER, &was_ok).toLongLong();
    if(!was_ok  || m_set_abort_waiting.m_id_player < 1)
    {
        error = "argument 'id_player' jest pusty";
        m_logic_args.setArg(SetAbortWaitingLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(SetAbortWaitingLogicArgs::ArgumentsResponse::MESSAGE, error);
        m_logic_args.setArg(SetAbortWaitingLogicArgs::ArgumentsResponse::STATUS, -1);
        return false;
    }

    return true;
}

bool SetAbortWaitingLogic::work(QString dbConnectionNmae, QString& error)
{
    Database* db = Database::getInstance(dbConnectionNmae);

    if(false == db->execQuery(&m_set_abort_waiting))
    {
        error = db->getLastError();
        m_logic_args.setArg(SetAbortWaitingLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(SetAbortWaitingLogicArgs::ArgumentsResponse::MESSAGE, "Błąd bazy danych");
        m_logic_args.setArg(SetAbortWaitingLogicArgs::ArgumentsResponse::STATUS, -1);
        return false;
    }

    m_logic_args.setArg(SetAbortWaitingLogicArgs::ArgumentsResponse::WAS_OK, m_set_abort_waiting.getResult().was_ok);
    m_logic_args.setArg(SetAbortWaitingLogicArgs::ArgumentsResponse::STATUS, m_set_abort_waiting.getResult().status);
    m_logic_args.setArg(SetAbortWaitingLogicArgs::ArgumentsResponse::MESSAGE, m_set_abort_waiting.getResult().db_message);

    return true;
}

QString SetAbortWaitingLogic::getResult()
{
    return m_logic_args.getResponse();
}

SetAbortWaitingLogic* SetAbortWaitingLogic::getTemplate()
{
    if(s_login_logic == nullptr)
        s_login_logic = new SetAbortWaitingLogic();

    return s_login_logic;
}

QString SetAbortWaitingLogic::getLogicName()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::SetAbortWaitingLogic);
    return s_logic_name;
}

SetAbortWaitingLogic::~SetAbortWaitingLogic()
{
    if(s_login_logic != nullptr)
        delete s_login_logic;
}
