#include "get_waiting_info_logic.h"

#include "logic_list.h"
#include "database.h"
#include "global_struct/player_info.h"

GetWaitingInfoLogic* GetWaitingInfoLogic::s_login_logic;
QString GetWaitingInfoLogic::s_logic_name;


GetWaitingInfoLogic::GetWaitingInfoLogic()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::GetWaitingInfoLogic);
}

bool GetWaitingInfoLogic::setArguments(QStringList arguments, QString& error)
{
    if(!m_logic_args.setArgsQuery(arguments))
    {
        error = "Nie odpowiednia liczba argumentow";
        m_logic_args.setArg(GetWaitingInfoLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(GetWaitingInfoLogicArgs::ArgumentsResponse::MESSAGE, error);
        m_logic_args.setArg(GetWaitingInfoLogicArgs::ArgumentsResponse::STATUS, -1);
        m_logic_args.setArg(GetWaitingInfoLogicArgs::ArgumentsResponse::ID_BATTLE, QVariant());
        return false;
    }

    bool was_ok = false;

    m_get_waiting_info.m_id_player = m_logic_args.getArg(GetWaitingInfoLogicArgs::ArgumentsQuery::ID_PLAYER, &was_ok).toLongLong();
    if(!was_ok || m_get_waiting_info.m_id_player < 1)
    {
        error = "argument 'id_player' jest pusty";
        m_logic_args.setArg(GetWaitingInfoLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(GetWaitingInfoLogicArgs::ArgumentsResponse::MESSAGE, error);
        m_logic_args.setArg(GetWaitingInfoLogicArgs::ArgumentsResponse::STATUS, -1);
        m_logic_args.setArg(GetWaitingInfoLogicArgs::ArgumentsResponse::ID_BATTLE, QVariant());
        return false;
    }

    return true;
}

bool GetWaitingInfoLogic::work(QString dbConnectionNmae, QString& error)
{
    Database* db = Database::getInstance(dbConnectionNmae);

    if(false == db->execQuery(&m_get_waiting_info))
    {
        error = db->getLastError();
        m_logic_args.setArg(GetWaitingInfoLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(GetWaitingInfoLogicArgs::ArgumentsResponse::MESSAGE, "Błąd bazy danych");
        m_logic_args.setArg(GetWaitingInfoLogicArgs::ArgumentsResponse::STATUS, -1);
        m_logic_args.setArg(GetWaitingInfoLogicArgs::ArgumentsResponse::ID_BATTLE, QVariant());
        return false;
    }

    m_logic_args.setArg(GetWaitingInfoLogicArgs::ArgumentsResponse::WAS_OK, m_get_waiting_info.getResult().was_ok);
    m_logic_args.setArg(GetWaitingInfoLogicArgs::ArgumentsResponse::STATUS, m_get_waiting_info.getResult().status);
    m_logic_args.setArg(GetWaitingInfoLogicArgs::ArgumentsResponse::MESSAGE, m_get_waiting_info.getResult().db_message);
    m_logic_args.setArg(GetWaitingInfoLogicArgs::ArgumentsResponse::ID_BATTLE, m_get_waiting_info.getResult().id_bitwy);

    return true;
}

QString GetWaitingInfoLogic::getResult()
{
    return m_logic_args.getResponse();
}

GetWaitingInfoLogic* GetWaitingInfoLogic::getTemplate()
{
    if(s_login_logic == nullptr)
        s_login_logic = new GetWaitingInfoLogic();

    return s_login_logic;
}

QString GetWaitingInfoLogic::getLogicName()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::GetWaitingInfoLogic);
    return s_logic_name;
}

GetWaitingInfoLogic::~GetWaitingInfoLogic()
{
    if(s_login_logic != nullptr)
        delete s_login_logic;
}
