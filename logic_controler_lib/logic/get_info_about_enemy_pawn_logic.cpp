#include "get_info_about_enemy_pawn_logic.h"

#include "logic_list.h"
#include "database.h"
#include "global_struct/player_info.h"

GetInfoAboutEnemyPawnLogic* GetInfoAboutEnemyPawnLogic::s_login_logic;
QString GetInfoAboutEnemyPawnLogic::s_logic_name;


GetInfoAboutEnemyPawnLogic::GetInfoAboutEnemyPawnLogic()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::GetInfoAboutEnemyPawnLogic);
}

bool GetInfoAboutEnemyPawnLogic::setArguments(QStringList arguments, QString& error)
{
    if(!m_logic_args.setArgsQuery(arguments))
    {
        error = "Nie odpowiednia liczba argumentow";
        m_logic_args.setArg(GetInfoAboutEnemyPawnLogicArgs::ArgumentsResponse::IDS_CREATURE, QVariant());
        m_logic_args.setArg(GetInfoAboutEnemyPawnLogicArgs::ArgumentsResponse::HEALTH, QVariant());
        m_logic_args.setArg(GetInfoAboutEnemyPawnLogicArgs::ArgumentsResponse::SHIELD, QVariant());
        m_logic_args.setArg(GetInfoAboutEnemyPawnLogicArgs::ArgumentsResponse::POINTS_OF_MOVE, QVariant());
        m_logic_args.setArg(GetInfoAboutEnemyPawnLogicArgs::ArgumentsResponse::POSITION_X, QVariant());
        m_logic_args.setArg(GetInfoAboutEnemyPawnLogicArgs::ArgumentsResponse::POSITION_Y, QVariant());
        return false;
    }

    bool was_ok = false;
    m_get_info_about_enemy_pawn.m_id_player = m_logic_args.getArg(GetInfoAboutEnemyPawnLogicArgs::ArgumentsQuery::ID_PLAYER, &was_ok).toLongLong();
    if(false == was_ok || m_get_info_about_enemy_pawn.m_id_player < 1)
    {
        error = "argument 'id_player' jest pusty lub nieprawidlowy";
        m_logic_args.setArg(GetInfoAboutEnemyPawnLogicArgs::ArgumentsResponse::IDS_CREATURE, QVariant());
        m_logic_args.setArg(GetInfoAboutEnemyPawnLogicArgs::ArgumentsResponse::HEALTH, QVariant());
        m_logic_args.setArg(GetInfoAboutEnemyPawnLogicArgs::ArgumentsResponse::SHIELD, QVariant());
        m_logic_args.setArg(GetInfoAboutEnemyPawnLogicArgs::ArgumentsResponse::POINTS_OF_MOVE, QVariant());
        m_logic_args.setArg(GetInfoAboutEnemyPawnLogicArgs::ArgumentsResponse::POSITION_X, QVariant());
        m_logic_args.setArg(GetInfoAboutEnemyPawnLogicArgs::ArgumentsResponse::POSITION_Y, QVariant());
        return false;
    }

    return true;
}

bool GetInfoAboutEnemyPawnLogic::work(QString dbConnectionNmae, QString& error)
{
    Database* db = Database::getInstance(dbConnectionNmae);

    if(!db->execQuery(&m_get_info_about_enemy_pawn))
    {
        error = db->getLastError();
        m_logic_args.setArg(GetInfoAboutEnemyPawnLogicArgs::ArgumentsResponse::IDS_CREATURE, QVariant());
        m_logic_args.setArg(GetInfoAboutEnemyPawnLogicArgs::ArgumentsResponse::HEALTH, QVariant());
        m_logic_args.setArg(GetInfoAboutEnemyPawnLogicArgs::ArgumentsResponse::SHIELD, QVariant());
        m_logic_args.setArg(GetInfoAboutEnemyPawnLogicArgs::ArgumentsResponse::POINTS_OF_MOVE, QVariant());
        m_logic_args.setArg(GetInfoAboutEnemyPawnLogicArgs::ArgumentsResponse::POSITION_X, QVariant());
        m_logic_args.setArg(GetInfoAboutEnemyPawnLogicArgs::ArgumentsResponse::POSITION_Y, QVariant());
        return false;
    }

    QStringList ids_creature;
    QStringList healths;
    QStringList shields;
    QStringList points_of_move;
    QStringList position_x;
    QStringList position_y;
    for(DatabaseQueryGetInfoAboutEnemyPawn::DatabaseOut out :  m_get_info_about_enemy_pawn.getResult())
    {
        ids_creature.push_back(QString::number(out.id_boahtera_gracza));
        healths.push_back(QString::number(out.zdrowie));
        shields.push_back(QString::number(out.ochrona));
        points_of_move.push_back(QString::number(out.punkty_ruchu));
        position_x.push_back(QString::number(out.pozycja_x));
        position_y.push_back(QString::number(out.pozycja_y));
    }

    m_logic_args.setArg(GetInfoAboutEnemyPawnLogicArgs::ArgumentsResponse::IDS_CREATURE, ids_creature.join("}{"));
    m_logic_args.setArg(GetInfoAboutEnemyPawnLogicArgs::ArgumentsResponse::HEALTH, healths.join("}{"));
    m_logic_args.setArg(GetInfoAboutEnemyPawnLogicArgs::ArgumentsResponse::SHIELD, shields.join("}{"));
    m_logic_args.setArg(GetInfoAboutEnemyPawnLogicArgs::ArgumentsResponse::POINTS_OF_MOVE, points_of_move.join("}{"));
    m_logic_args.setArg(GetInfoAboutEnemyPawnLogicArgs::ArgumentsResponse::POSITION_X, position_x.join("}{"));
    m_logic_args.setArg(GetInfoAboutEnemyPawnLogicArgs::ArgumentsResponse::POSITION_Y, position_y.join("}{"));

    return true;
}

QString GetInfoAboutEnemyPawnLogic::getResult()
{
    return m_logic_args.getResponse();
}

GetInfoAboutEnemyPawnLogic* GetInfoAboutEnemyPawnLogic::getTemplate()
{
    if(s_login_logic == nullptr)
        s_login_logic = new GetInfoAboutEnemyPawnLogic();

    return s_login_logic;
}

QString GetInfoAboutEnemyPawnLogic::getLogicName()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::GetInfoAboutEnemyPawnLogic);
    return s_logic_name;
}

GetInfoAboutEnemyPawnLogic::~GetInfoAboutEnemyPawnLogic()
{
    if(s_login_logic != nullptr)
        delete s_login_logic;
}
