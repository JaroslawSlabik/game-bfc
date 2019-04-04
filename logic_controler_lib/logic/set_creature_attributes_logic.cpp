#include "set_creature_attributes_logic.h"

#include "logic_list.h"
#include "database.h"
#include "global_struct/player_info.h"

SetCreatureAttributesLogic* SetCreatureAttributesLogic::s_login_logic;
QString SetCreatureAttributesLogic::s_logic_name;


SetCreatureAttributesLogic::SetCreatureAttributesLogic()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::SetCreatureAttributes);
}

bool SetCreatureAttributesLogic::setArguments(QStringList arguments, QString& error)
{
    if(!m_logic_args.setArgsQuery(arguments))
    {
        error = "Nie odpowiednia liczba argumentow";
        return false;
    }

    bool was_ok = false;
    m_set_creature_attributes.m_id = m_logic_args.getArg(SetCreatureAttributesLogicArgs::ArgumentsQuery::ID_CREATURE, &was_ok).toLongLong();
    if(!was_ok)
        return false;

    m_set_creature_attributes.m_health = m_logic_args.getArg(SetCreatureAttributesLogicArgs::ArgumentsQuery::HEALTHS, &was_ok).toInt();
    if(!was_ok)
        return false;

    m_set_creature_attributes.m_shield = m_logic_args.getArg(SetCreatureAttributesLogicArgs::ArgumentsQuery::SHIELDS, &was_ok).toInt();
    if(!was_ok)
        return false;

    m_set_creature_attributes.m_attack = m_logic_args.getArg(SetCreatureAttributesLogicArgs::ArgumentsQuery::ATTACKS, &was_ok).toInt();
    if(!was_ok)
        return false;

    m_set_creature_attributes.m_move = m_logic_args.getArg(SetCreatureAttributesLogicArgs::ArgumentsQuery::POINTS_OF_MOVE, &was_ok).toInt();
    if(!was_ok)
        return false;

    if(m_set_creature_attributes.m_id < 1)
    {
        error = "argument 'id' jest pusty";
        return false;
    }

    if(m_set_creature_attributes.m_health < 0)
    {
        error = "argument 'health' jest pusty";
        return false;
    }

    if(m_set_creature_attributes.m_shield < 0)
    {
        error = "argument 'shield' jest pusty";
        return false;
    }

    if(m_set_creature_attributes.m_attack < 0)
    {
        error = "argument 'attack' jest pusty";
        return false;
    }

    if(m_set_creature_attributes.m_move < 0)
    {
        error = "argument 'move' jest pusty";
        return false;
    }

    return true;
}

bool SetCreatureAttributesLogic::work(QString dbConnectionNmae, QString& error)
{
    Database* db = Database::getInstance(dbConnectionNmae);

    if(!db->execQuery(&m_set_creature_attributes))
    {
        error = db->getLastError();
        return false;
    }

    m_logic_args.setArg(SetCreatureAttributesLogicArgs::ArgumentsResponse::WAS_OK, m_set_creature_attributes.getResult().was_ok);
    m_logic_args.setArg(SetCreatureAttributesLogicArgs::ArgumentsResponse::MESSAGE, m_set_creature_attributes.getResult().db_message);

    return true;
}

QString SetCreatureAttributesLogic::getResult()
{
    return m_logic_args.getResponse();
}

SetCreatureAttributesLogic* SetCreatureAttributesLogic::getTemplate()
{
    if(s_login_logic == nullptr)
        s_login_logic = new SetCreatureAttributesLogic();

    return s_login_logic;
}

QString SetCreatureAttributesLogic::getLogicName()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::SetCreatureAttributes);
    return s_logic_name;
}

SetCreatureAttributesLogic::~SetCreatureAttributesLogic()
{
    if(s_login_logic != nullptr)
        delete s_login_logic;
}
