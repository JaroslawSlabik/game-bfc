#include "get_player_info_logic.h"

#include "logic_list.h"
#include "database.h"
#include "global_struct/player_info.h"

GetPlayerInfoLogic* GetPlayerInfoLogic::s_login_logic;
QString GetPlayerInfoLogic::s_logic_name;


GetPlayerInfoLogic::GetPlayerInfoLogic()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::GetPlayerInfo);
}

bool GetPlayerInfoLogic::setArguments(QStringList arguments, QString& error)
{
    if(!m_logic_args.setArgsQuery(arguments))
    {
        error = "Nie odpowiednia liczba argumentow";
        return false;
    }

    bool was_ok = false;
    m_get_player_info.m_id_gracza = m_logic_args.getArg(GetPlayerInfoLogicArgs::ArgumentsQuery::ID_GAMER, &was_ok).toLongLong();
    if(!was_ok)
        return false;

    if(m_get_player_info.m_id_gracza < 1)
    {
        error = "argument 'id_gracza' jest pusty";
        return false;
    }

    return true;
}

bool GetPlayerInfoLogic::work(QString dbConnectionNmae, QString& error)
{
    Database* db = Database::getInstance(dbConnectionNmae);

    if(!db->execQuery(&m_get_player_info))
    {
        error = db->getLastError();
        return false;
    }

    m_logic_args.setArg(GetPlayerInfoLogicArgs::ArgumentsResponse::NAME, m_get_player_info.getResult().imie);
    m_logic_args.setArg(GetPlayerInfoLogicArgs::ArgumentsResponse::LEVEL, m_get_player_info.getResult().level);
    m_logic_args.setArg(GetPlayerInfoLogicArgs::ArgumentsResponse::EXPERIENCE, m_get_player_info.getResult().exp);
    m_logic_args.setArg(GetPlayerInfoLogicArgs::ArgumentsResponse::EXPERIENCE_TO_NEXT_LEVEL, m_get_player_info.getResult().exp_next_level);
    m_logic_args.setArg(GetPlayerInfoLogicArgs::ArgumentsResponse::POINTS_TO_DISTRIBUTION, m_get_player_info.getResult().points_to_distribute);

    return true;
}

QString GetPlayerInfoLogic::getResult()
{
    return m_logic_args.getResponse();
}

GetPlayerInfoLogic* GetPlayerInfoLogic::getTemplate()
{
    if(s_login_logic == nullptr)
        s_login_logic = new GetPlayerInfoLogic();

    return s_login_logic;
}

QString GetPlayerInfoLogic::getLogicName()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::GetPlayerInfo);
    return s_logic_name;
}

GetPlayerInfoLogic::~GetPlayerInfoLogic()
{
    if(s_login_logic != nullptr)
        delete s_login_logic;
}
