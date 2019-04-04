#include "get_battle_pawn_for_init_logic.h"

#include "logic_list.h"
#include "database.h"
#include "global_struct/player_info.h"

GetBattlePawnForInitLogic* GetBattlePawnForInitLogic::s_login_logic;
QString GetBattlePawnForInitLogic::s_logic_name;


GetBattlePawnForInitLogic::GetBattlePawnForInitLogic()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::GetBattlePawnForInitLogic);
}

bool GetBattlePawnForInitLogic::setArguments(QStringList arguments, QString& error)
{
    if(!m_logic_args.setArgsQuery(arguments))
    {
        error = "Nie odpowiednia liczba argumentow";
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::IDS_CREATURE, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::NAMES, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::DESCRIPTIONS, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::HEALTHS, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::SHIELDS, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::ATTACKS, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::POINTS_OF_MOVE, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::TEXTURES, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::POSITION_X, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::POSITION_Y, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::ELEMENT, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::ENEMY, QVariant());
        return false;
    }

    bool was_ok = false;
    m_get_battle_pawn_for_init.m_id_player = m_logic_args.getArg(GetBattlePawnForInitLogicArgs::ArgumentsQuery::ID_PLAYER, &was_ok).toLongLong();
    if(false == was_ok || m_get_battle_pawn_for_init.m_id_player < 1)
    {
        error = "argument 'id_player' jest pusty lub nieprawidlowy";
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::IDS_CREATURE, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::NAMES, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::DESCRIPTIONS, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::HEALTHS, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::SHIELDS, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::ATTACKS, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::POINTS_OF_MOVE, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::TEXTURES, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::POSITION_X, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::POSITION_Y, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::ELEMENT, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::ENEMY, QVariant());
        return false;
    }

    return true;
}

bool GetBattlePawnForInitLogic::work(QString dbConnectionNmae, QString& error)
{
    Database* db = Database::getInstance(dbConnectionNmae);

    if(!db->execQuery(&m_get_battle_pawn_for_init))
    {
        error = db->getLastError();
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::IDS_CREATURE, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::NAMES, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::DESCRIPTIONS, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::HEALTHS, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::SHIELDS, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::ATTACKS, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::POINTS_OF_MOVE, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::TEXTURES, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::POSITION_X, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::POSITION_Y, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::ELEMENT, QVariant());
        m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::ENEMY, QVariant());
        return false;
    }

    QStringList ids_creature;
    QStringList names;
    QStringList descriptions;
    QStringList healths;
    QStringList shields;
    QStringList attacks;
    QStringList points_of_move;
    QStringList textures;
    QStringList position_x;
    QStringList position_y;
    QStringList elements;
    QStringList enemy;
    for(DatabaseQueryGetBattlePawnForInit::DatabaseOut out :  m_get_battle_pawn_for_init.getResult())
    {
        ids_creature.push_back(QString::number(out.id_boahtera_gracza));
        names.push_back(out.nazwa);
        descriptions.push_back(out.opis);
        healths.push_back(QString::number(out.zdrowie));
        shields.push_back(QString::number(out.ochrona));
        attacks.push_back(QString::number(out.atak));
        points_of_move.push_back(QString::number(out.punkty_ruchu));
        textures.push_back(out.tekstura);
        position_x.push_back(QString::number(out.pozycja_x));
        position_y.push_back(QString::number(out.pozycja_y));
        elements.push_back(QString::number(out.zywiol));
        enemy.push_back(QString::number(out.wrog));
    }

    m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::IDS_CREATURE, ids_creature.join("}{"));
    m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::NAMES, names.join("}{"));
    m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::DESCRIPTIONS, descriptions.join("}{"));
    m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::HEALTHS, healths.join("}{"));
    m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::SHIELDS, shields.join("}{"));
    m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::ATTACKS, attacks.join("}{"));
    m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::POINTS_OF_MOVE, points_of_move.join("}{"));
    m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::TEXTURES, textures.join("}{"));
    m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::POSITION_X, position_x.join("}{"));
    m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::POSITION_Y, position_y.join("}{"));
    m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::ELEMENT, elements.join("}{"));
    m_logic_args.setArg(GetBattlePawnForInitLogicArgs::ArgumentsResponse::ENEMY, enemy.join("}{"));

    return true;
}

QString GetBattlePawnForInitLogic::getResult()
{
    return m_logic_args.getResponse();
}

GetBattlePawnForInitLogic* GetBattlePawnForInitLogic::getTemplate()
{
    if(s_login_logic == nullptr)
        s_login_logic = new GetBattlePawnForInitLogic();

    return s_login_logic;
}

QString GetBattlePawnForInitLogic::getLogicName()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::GetBattlePawnForInitLogic);
    return s_logic_name;
}

GetBattlePawnForInitLogic::~GetBattlePawnForInitLogic()
{
    if(s_login_logic != nullptr)
        delete s_login_logic;
}
