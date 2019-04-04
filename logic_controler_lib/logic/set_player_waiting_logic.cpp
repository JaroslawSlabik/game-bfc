#include "set_player_waiting_logic.h"

#include "logic_list.h"
#include "database.h"
#include "global_struct/player_info.h"

SetPlayerWaitingLogic* SetPlayerWaitingLogic::s_login_logic;
QString SetPlayerWaitingLogic::s_logic_name;

SetPlayerWaitingLogic::SetPlayerWaitingLogic()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::SetPlayerWaiting);
}

bool SetPlayerWaitingLogic::setArguments(QStringList arguments, QString& error)
{
    if(!m_logic_args.setArgsQuery(arguments))
    {
        error = "Nie odpowiednia liczba argumentow";
        m_logic_args.setArg(SetPlayerWaitingLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(SetPlayerWaitingLogicArgs::ArgumentsResponse::MESSAGE, error);
        m_logic_args.setArg(SetPlayerWaitingLogicArgs::ArgumentsResponse::STATUS, -1);
        return false;
    }

    bool was_ok = false;

    m_set_player_waiting.m_id_player = m_logic_args.getArg(SetPlayerWaitingLogicArgs::ArgumentsQuery::ID_PLAYER, &was_ok).toLongLong();
    if(!was_ok || m_set_player_waiting.m_id_player < 1)
    {
        error = "argument 'id_player' jest pusty";
        m_logic_args.setArg(SetPlayerWaitingLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(SetPlayerWaitingLogicArgs::ArgumentsResponse::MESSAGE, error);
        m_logic_args.setArg(SetPlayerWaitingLogicArgs::ArgumentsResponse::STATUS, -1);
        return false;
    }

    m_set_player_waiting.m_id_game_mode = m_logic_args.getArg(SetPlayerWaitingLogicArgs::ArgumentsQuery::ID_GAME_MODE, &was_ok).toInt();
    if(!was_ok || m_set_player_waiting.m_id_game_mode < 1)
    {
        error = "argument 'id_game_mode' jest pusty";
        m_logic_args.setArg(SetPlayerWaitingLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(SetPlayerWaitingLogicArgs::ArgumentsResponse::MESSAGE, error);
        m_logic_args.setArg(SetPlayerWaitingLogicArgs::ArgumentsResponse::STATUS, -1);
        return false;
    }

    return true;
}

bool SetPlayerWaitingLogic::work(QString dbConnectionNmae, QString& error)
{
    Database* db = Database::getInstance(dbConnectionNmae);

    if(false == db->execQuery(&m_set_player_waiting))
    {
        error = db->getLastError();
        m_logic_args.setArg(SetPlayerWaitingLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(SetPlayerWaitingLogicArgs::ArgumentsResponse::MESSAGE, "Błąd bazy danych");
        m_logic_args.setArg(SetPlayerWaitingLogicArgs::ArgumentsResponse::STATUS, -1);
        return false;
    }

    m_logic_args.setArg(SetPlayerWaitingLogicArgs::ArgumentsResponse::WAS_OK, m_set_player_waiting.getResult().was_ok);
    m_logic_args.setArg(SetPlayerWaitingLogicArgs::ArgumentsResponse::MESSAGE, m_set_player_waiting.getResult().db_message);
    m_logic_args.setArg(SetPlayerWaitingLogicArgs::ArgumentsResponse::STATUS, m_set_player_waiting.getResult().status);

    return true;
}

QString SetPlayerWaitingLogic::getResult()
{
    return m_logic_args.getResponse();
}

SetPlayerWaitingLogic* SetPlayerWaitingLogic::getTemplate()
{
    if(s_login_logic == nullptr)
        s_login_logic = new SetPlayerWaitingLogic();

    return s_login_logic;
}

QString SetPlayerWaitingLogic::getLogicName()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::SetPlayerWaiting);
    return s_logic_name;
}

SetPlayerWaitingLogic::~SetPlayerWaitingLogic()
{
    if(s_login_logic != nullptr)
        delete s_login_logic;
}
