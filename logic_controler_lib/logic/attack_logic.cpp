#include "attack_logic.h"

#include "logic_list.h"
#include "database.h"
#include "global_struct/player_info.h"

AttackLogic* AttackLogic::s_login_logic;
QString AttackLogic::s_logic_name;


AttackLogic::AttackLogic()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::AttackLogic);
}

bool AttackLogic::setArguments(QStringList arguments, QString& error)
{
    if(!m_logic_args.setArgsQuery(arguments))
    {
        error = "Nie odpowiednia liczba argumentow";
        m_logic_args.setArg(AttackLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(AttackLogicArgs::ArgumentsResponse::STATUS, -1);
        m_logic_args.setArg(AttackLogicArgs::ArgumentsResponse::MESSAGE, error);
        return false;
    }

    bool was_ok = false;
    m_attack.m_id_gracz_potwor = m_logic_args.getArg(AttackLogicArgs::ArgumentsQuery::ID_CREATURE_PLAYER, &was_ok).toLongLong();
    if(false == was_ok || m_attack.m_id_gracz_potwor < 1)
    {
        error = "argument 'id_gracz_potwor' jest pusty lub nieprawidlowy";
        m_logic_args.setArg(AttackLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(AttackLogicArgs::ArgumentsResponse::STATUS, -1);
        m_logic_args.setArg(AttackLogicArgs::ArgumentsResponse::MESSAGE, error);
        return false;
    }

    m_attack.m_id_wrog_potwor = m_logic_args.getArg(AttackLogicArgs::ArgumentsQuery::ID_CREATURE_ENEMY, &was_ok).toLongLong();
    if(false == was_ok || m_attack.m_id_wrog_potwor < 1)
    {
        error = "argument 'id_wrog_potwor' jest pusty lub nieprawidlowy";
        m_logic_args.setArg(AttackLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(AttackLogicArgs::ArgumentsResponse::STATUS, -1);
        m_logic_args.setArg(AttackLogicArgs::ArgumentsResponse::MESSAGE, error);
        return false;
    }

    m_attack.m_damage = m_logic_args.getArg(AttackLogicArgs::ArgumentsQuery::DAMAGE, &was_ok).toInt();
    if(false == was_ok || m_attack.m_damage < 1)
    {
        error = "argument 'damage' jest pusty lub nieprawidlowy";
        m_logic_args.setArg(AttackLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(AttackLogicArgs::ArgumentsResponse::STATUS, -1);
        m_logic_args.setArg(AttackLogicArgs::ArgumentsResponse::MESSAGE, error);
        return false;
    }

    return true;
}

bool AttackLogic::work(QString dbConnectionNmae, QString& error)
{
    Database* db = Database::getInstance(dbConnectionNmae);

    if(!db->execQuery(&m_attack))
    {
        error = db->getLastError();
        m_logic_args.setArg(AttackLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(AttackLogicArgs::ArgumentsResponse::STATUS, -1);
        m_logic_args.setArg(AttackLogicArgs::ArgumentsResponse::MESSAGE, error);
        return false;
    }

    m_logic_args.setArg(AttackLogicArgs::ArgumentsResponse::WAS_OK, m_attack.getResult().was_ok);
    m_logic_args.setArg(AttackLogicArgs::ArgumentsResponse::STATUS, m_attack.getResult().status);
    m_logic_args.setArg(AttackLogicArgs::ArgumentsResponse::MESSAGE, m_attack.getResult().db_message);

    return true;
}

QString AttackLogic::getResult()
{
    return m_logic_args.getResponse();
}

AttackLogic* AttackLogic::getTemplate()
{
    if(s_login_logic == nullptr)
        s_login_logic = new AttackLogic();

    return s_login_logic;
}

QString AttackLogic::getLogicName()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::AttackLogic);
    return s_logic_name;
}

AttackLogic::~AttackLogic()
{
    if(s_login_logic != nullptr)
        delete s_login_logic;
}
