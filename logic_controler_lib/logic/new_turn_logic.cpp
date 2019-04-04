#include "new_turn_logic.h"

#include "logic_list.h"
#include "database.h"
#include "global_struct/player_info.h"

NewTurnLogic* NewTurnLogic::s_login_logic;
QString NewTurnLogic::s_logic_name;


NewTurnLogic::NewTurnLogic()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::NewTurnLogic);
}

bool NewTurnLogic::setArguments(QStringList arguments, QString& error)
{
    if(!m_logic_args.setArgsQuery(arguments))
    {
        error = "Nie odpowiednia liczba argumentow";
        m_logic_args.setArg(NewTurnLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(NewTurnLogicArgs::ArgumentsResponse::STATUS, -1);
        m_logic_args.setArg(NewTurnLogicArgs::ArgumentsResponse::MESSAGE, error);
        return false;
    }

    bool was_ok = false;
    m_new_turn.m_id_player = m_logic_args.getArg(NewTurnLogicArgs::ArgumentsQuery::ID_PLAYER, &was_ok).toLongLong();
    if(!was_ok || m_new_turn.m_id_player < 1)
    {
        error = "argument 'id_gracz_potwor' jest pusty";
        m_logic_args.setArg(NewTurnLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(NewTurnLogicArgs::ArgumentsResponse::STATUS, -1);
        m_logic_args.setArg(NewTurnLogicArgs::ArgumentsResponse::MESSAGE, error);
        return false;
    }

    return true;
}

bool NewTurnLogic::work(QString dbConnectionNmae, QString& error)
{
    Database* db = Database::getInstance(dbConnectionNmae);

    if(!db->execQuery(&m_new_turn))
    {
        error = db->getLastError();
        m_logic_args.setArg(NewTurnLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(NewTurnLogicArgs::ArgumentsResponse::STATUS, -1);
        m_logic_args.setArg(NewTurnLogicArgs::ArgumentsResponse::MESSAGE, error);
        return false;
    }

    m_logic_args.setArg(NewTurnLogicArgs::ArgumentsResponse::WAS_OK, m_new_turn.getResult().was_ok);
    m_logic_args.setArg(NewTurnLogicArgs::ArgumentsResponse::STATUS, m_new_turn.getResult().status);
    m_logic_args.setArg(NewTurnLogicArgs::ArgumentsResponse::MESSAGE, m_new_turn.getResult().db_message);

    return true;
}

QString NewTurnLogic::getResult()
{
    return m_logic_args.getResponse();
}

NewTurnLogic* NewTurnLogic::getTemplate()
{
    if(s_login_logic == nullptr)
        s_login_logic = new NewTurnLogic();

    return s_login_logic;
}

QString NewTurnLogic::getLogicName()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::NewTurnLogic);
    return s_logic_name;
}

NewTurnLogic::~NewTurnLogic()
{
    if(s_login_logic != nullptr)
        delete s_login_logic;
}
