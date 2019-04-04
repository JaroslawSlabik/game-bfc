#include "get_creatures_logic.h"

#include "logic_list.h"
#include "database.h"
#include "global_struct/creature_info.h"

GetCreaturesLogic* GetCreaturesLogic::s_login_logic;
QString GetCreaturesLogic::s_logic_name;

GetCreaturesLogic::GetCreaturesLogic()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::GetCreatures);
}

bool GetCreaturesLogic::setArguments(QStringList arguments, QString& error)
{
    if(!m_logic_args.setArgsQuery(arguments))
    {
        error = "Nie odpowiednia liczba argumentow";
        return false;
    }

    bool was_ok = false;
    m_get_player_creatures.m_id_gracza = m_logic_args.getArg(GetCreaturesLogicArgs::ArgumentsQuery::ID_GAMER, &was_ok).toLongLong();
    if(!was_ok)
        return false;

    m_get_player_creatures.m_lp = m_logic_args.getArg(GetCreaturesLogicArgs::ArgumentsQuery::LP_CREATURE, &was_ok).toInt();
    if(!was_ok)
        return false;

    if(m_get_player_creatures.m_id_gracza < 1)
    {
        error = "argument 'id_gracza' jest pusty";
        return false;
    }
    if(m_get_player_creatures.m_lp < 0)
    {
        error = "argument 'lp' jest pusty";
        return false;
    }

    return true;
}

bool GetCreaturesLogic::work(QString dbConnectionNmae, QString& error)
{
    Database* db = Database::getInstance(dbConnectionNmae);

    if(!db->execQuery(&m_get_player_creatures))
    {
        error = db->getLastError();
        return false;
    }

    QStringList ids_creature;
    QStringList names;
    QStringList descriptions;
    QStringList healths;
    QStringList shields;
    QStringList attacks;
    QStringList points_of_move;
    QList<QString> textures;
    for(DatabaseQueryGetPlayerCreatures::DatabaseOut out :  m_get_player_creatures.getResult())
    {
        ids_creature.push_back(QString::number(out.id_potwora_gracza));
        names.push_back(out.nazwa);
        descriptions.push_back(out.opis);
        healths.push_back(QString::number(out.zdrowie));
        shields.push_back(QString::number(out.ochrona));
        attacks.push_back(QString::number(out.atak));
        points_of_move.push_back(QString::number(out.punkty_ruchu));
        textures.push_back(out.tekstura);
    }

    m_logic_args.setArg(GetCreaturesLogicArgs::ArgumentsResponse::IDS_CREATURE, ids_creature.join("}{"));
    m_logic_args.setArg(GetCreaturesLogicArgs::ArgumentsResponse::NAMES, names.join("}{"));
    m_logic_args.setArg(GetCreaturesLogicArgs::ArgumentsResponse::DESCRIPTIONS, descriptions.join("}{"));
    m_logic_args.setArg(GetCreaturesLogicArgs::ArgumentsResponse::HEALTHS, healths.join("}{"));
    m_logic_args.setArg(GetCreaturesLogicArgs::ArgumentsResponse::SHIELDS, shields.join("}{"));
    m_logic_args.setArg(GetCreaturesLogicArgs::ArgumentsResponse::ATTACKS, attacks.join("}{"));
    m_logic_args.setArg(GetCreaturesLogicArgs::ArgumentsResponse::POINTS_OF_MOVE, points_of_move.join("}{"));
    m_logic_args.setArg(GetCreaturesLogicArgs::ArgumentsResponse::TEXTURES, textures.join("}{"));

    return true;
}

QString GetCreaturesLogic::getResult()
{
    return m_logic_args.getResponse();
}

GetCreaturesLogic* GetCreaturesLogic::getTemplate()
{
    if(s_login_logic == nullptr)
        s_login_logic = new GetCreaturesLogic();

    return s_login_logic;
}

QString GetCreaturesLogic::getLogicName()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::GetCreatures);
    return s_logic_name;
}

GetCreaturesLogic::~GetCreaturesLogic()
{
    if(s_login_logic != nullptr)
        delete s_login_logic;
}
