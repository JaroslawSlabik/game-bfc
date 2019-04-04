#include "get_battle_map_for_init_logic.h"
#include "logic_list.h"
#include "database.h"

GetBattleMapForInitLogic* GetBattleMapForInitLogic::s_login_logic;
QString GetBattleMapForInitLogic::s_logic_name;


GetBattleMapForInitLogic::GetBattleMapForInitLogic()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::GetBattleMapForInitLogic);
}

bool GetBattleMapForInitLogic::setArguments(QStringList arguments, QString& error)
{
    if(!m_logic_args.setArgsQuery(arguments))
    {
        error = "Nie odpowiednia liczba argumentow";
        m_logic_args.setArg(GetBattleMapForInitLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(GetBattleMapForInitLogicArgs::ArgumentsResponse::MESSAGE, error);
        m_logic_args.setArg(GetBattleMapForInitLogicArgs::ArgumentsResponse::STATUS, -1);
        m_logic_args.setArg(GetBattleMapForInitLogicArgs::ArgumentsResponse::MAP_FILE, QVariant());
        m_logic_args.setArg(GetBattleMapForInitLogicArgs::ArgumentsResponse::MAP_ELEMENT, QVariant());
        return false;
    }

    bool was_ok = false;

    m_get_battle_map_for_init.m_id_player = m_logic_args.getArg(GetBattleMapForInitLogicArgs::ArgumentsQuery::ID_PLAYER, &was_ok).toLongLong();
    if(!was_ok || m_get_battle_map_for_init.m_id_player < 1)
    {
        error = "argument 'id_player' jest pusty";
        m_logic_args.setArg(GetBattleMapForInitLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(GetBattleMapForInitLogicArgs::ArgumentsResponse::MESSAGE, error);
        m_logic_args.setArg(GetBattleMapForInitLogicArgs::ArgumentsResponse::STATUS, -1);
        m_logic_args.setArg(GetBattleMapForInitLogicArgs::ArgumentsResponse::MAP_FILE, QVariant());
        m_logic_args.setArg(GetBattleMapForInitLogicArgs::ArgumentsResponse::MAP_ELEMENT, QVariant());
        return false;
    }

    return true;
}

bool GetBattleMapForInitLogic::work(QString dbConnectionNmae, QString& error)
{
    Database* db = Database::getInstance(dbConnectionNmae);

    if(false == db->execQuery(&m_get_battle_map_for_init))
    {
        error = db->getLastError();
        m_logic_args.setArg(GetBattleMapForInitLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(GetBattleMapForInitLogicArgs::ArgumentsResponse::MESSAGE, "Błąd bazy danych");
        m_logic_args.setArg(GetBattleMapForInitLogicArgs::ArgumentsResponse::STATUS, -1);
        m_logic_args.setArg(GetBattleMapForInitLogicArgs::ArgumentsResponse::MAP_FILE, QVariant());
        m_logic_args.setArg(GetBattleMapForInitLogicArgs::ArgumentsResponse::MAP_ELEMENT, QVariant());
        return false;
    }

    m_logic_args.setArg(GetBattleMapForInitLogicArgs::ArgumentsResponse::WAS_OK, m_get_battle_map_for_init.getResult().was_ok);
    m_logic_args.setArg(GetBattleMapForInitLogicArgs::ArgumentsResponse::STATUS, m_get_battle_map_for_init.getResult().status);
    m_logic_args.setArg(GetBattleMapForInitLogicArgs::ArgumentsResponse::MESSAGE, m_get_battle_map_for_init.getResult().db_message);
    m_logic_args.setArg(GetBattleMapForInitLogicArgs::ArgumentsResponse::MAP_FILE, m_get_battle_map_for_init.getResult().map_file);
    m_logic_args.setArg(GetBattleMapForInitLogicArgs::ArgumentsResponse::MAP_ELEMENT, m_get_battle_map_for_init.getResult().map_element);

    return true;
}

QString GetBattleMapForInitLogic::getResult()
{
    return m_logic_args.getResponse();
}

GetBattleMapForInitLogic* GetBattleMapForInitLogic::getTemplate()
{
    if(s_login_logic == nullptr)
        s_login_logic = new GetBattleMapForInitLogic();

    return s_login_logic;
}

QString GetBattleMapForInitLogic::getLogicName()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::GetBattleMapForInitLogic);
    return s_logic_name;
}

GetBattleMapForInitLogic::~GetBattleMapForInitLogic()
{
    if(s_login_logic != nullptr)
        delete s_login_logic;
}
