#include "set_creature_waiting_logic.h"

#include "logic_list.h"
#include "database.h"
#include "global_struct/player_info.h"

SetCreatureWaitingLogic* SetCreatureWaitingLogic::s_login_logic;
QString SetCreatureWaitingLogic::s_logic_name;


SetCreatureWaitingLogic::SetCreatureWaitingLogic()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::SetCreatureWaiting);
}

bool SetCreatureWaitingLogic::setArguments(QStringList arguments, QString& error)
{
    if(!m_logic_args.setArgsQuery(arguments))
    {
        error = "Nie odpowiednia liczba argumentow";
        m_logic_args.setArg(SetCreatureWaitingLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(SetCreatureWaitingLogicArgs::ArgumentsResponse::MESSAGE, error);
        return false;
    }

    bool was_ok = false;

    m_inserting = m_logic_args.getArg(SetCreatureWaitingLogicArgs::ArgumentsQuery::INSERTING, &was_ok).toBool();
    if(!was_ok)
        return false;

    qlonglong id_creature = m_logic_args.getArg(SetCreatureWaitingLogicArgs::ArgumentsQuery::ID_CREATURE, &was_ok).toLongLong();
    if(!was_ok || id_creature < 1)
    {
        error = "argument 'id_creature' jest pusty";
        m_logic_args.setArg(SetCreatureWaitingLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(SetCreatureWaitingLogicArgs::ArgumentsResponse::MESSAGE, error);
        return false;
    }
    m_set_insert_creature_waiting.m_id_creature = m_set_delete_creature_waiting.m_id_creature = id_creature;


    if(m_inserting) //valid this field only when this is inserting
    {
        int id_element = m_logic_args.getArg(SetCreatureWaitingLogicArgs::ArgumentsQuery::ID_ELEMENT, &was_ok).toInt();
        if(!was_ok || id_element < 1)
        {
            error = "argument 'id_element' jest pusty";
            m_logic_args.setArg(SetCreatureWaitingLogicArgs::ArgumentsResponse::WAS_OK, false);
            m_logic_args.setArg(SetCreatureWaitingLogicArgs::ArgumentsResponse::MESSAGE, error);
            return false;
        }
        m_set_insert_creature_waiting.m_id_element = id_element;

        int pos_x = m_logic_args.getArg(SetCreatureWaitingLogicArgs::ArgumentsQuery::POSITION_X, &was_ok).toInt();
        if(!was_ok || pos_x < 0)
        {
            error = "argument 'pos_x' jest pusty";
            m_logic_args.setArg(SetCreatureWaitingLogicArgs::ArgumentsResponse::WAS_OK, false);
            m_logic_args.setArg(SetCreatureWaitingLogicArgs::ArgumentsResponse::MESSAGE, error);
            return false;
        }
        m_set_insert_creature_waiting.m_pos_x = pos_x;

        int pos_y = m_logic_args.getArg(SetCreatureWaitingLogicArgs::ArgumentsQuery::POSITION_Y, &was_ok).toInt();
        if(!was_ok || pos_y < 0)
        {
            error = "argument 'pos_y' jest pusty";
            m_logic_args.setArg(SetCreatureWaitingLogicArgs::ArgumentsResponse::WAS_OK, false);
            m_logic_args.setArg(SetCreatureWaitingLogicArgs::ArgumentsResponse::MESSAGE, error);
            return false;
        }
        m_set_insert_creature_waiting.m_pos_y = pos_y;
    }

    return true;
}

bool SetCreatureWaitingLogic::work(QString dbConnectionNmae, QString& error)
{
    Database* db = Database::getInstance(dbConnectionNmae);

    bool res_query = (m_inserting) ? db->execQuery(&m_set_insert_creature_waiting) : db->execQuery(&m_set_delete_creature_waiting);

    if(false == res_query)
    {
        error = db->getLastError();
        m_logic_args.setArg(SetCreatureWaitingLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(SetCreatureWaitingLogicArgs::ArgumentsResponse::MESSAGE, "Błąd bazy danych");
        return false;
    }

    m_logic_args.setArg(SetCreatureWaitingLogicArgs::ArgumentsResponse::WAS_OK, true);
    m_logic_args.setArg(SetCreatureWaitingLogicArgs::ArgumentsResponse::MESSAGE, (m_inserting) ? "Inserting - OK" : "Deleting - OK");

    return true;
}

QString SetCreatureWaitingLogic::getResult()
{
    return m_logic_args.getResponse();
}

SetCreatureWaitingLogic* SetCreatureWaitingLogic::getTemplate()
{
    if(s_login_logic == nullptr)
        s_login_logic = new SetCreatureWaitingLogic();

    return s_login_logic;
}

QString SetCreatureWaitingLogic::getLogicName()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::SetCreatureWaiting);
    return s_logic_name;
}

SetCreatureWaitingLogic::~SetCreatureWaitingLogic()
{
    if(s_login_logic != nullptr)
        delete s_login_logic;
}
