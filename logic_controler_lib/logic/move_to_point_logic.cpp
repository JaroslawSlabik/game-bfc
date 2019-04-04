#include "move_to_point_logic.h"

#include "logic_list.h"
#include "database.h"
#include "global_struct/player_info.h"

MoveToPointLogic* MoveToPointLogic::s_login_logic;
QString MoveToPointLogic::s_logic_name;


MoveToPointLogic::MoveToPointLogic()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::MoveToPointLogic);
}

bool MoveToPointLogic::setArguments(QStringList arguments, QString& error)
{
    if(!m_logic_args.setArgsQuery(arguments))
    {
        error = "Nie odpowiednia liczba argumentow";
        m_logic_args.setArg(MoveToPointLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(MoveToPointLogicArgs::ArgumentsResponse::STATUS, -1);
        m_logic_args.setArg(MoveToPointLogicArgs::ArgumentsResponse::MESSAGE, error);
        return false;
    }

    bool was_ok = false;
    m_move_to_point.m_id_creature_player = m_logic_args.getArg(MoveToPointLogicArgs::ArgumentsQuery::ID_CREATURE_PLAYER, &was_ok).toLongLong();
    if(false == was_ok || m_move_to_point.m_id_creature_player < 1)
    {
        error = "argument 'id_creature_player' jest pusty lub nieprawidlowy";
        m_logic_args.setArg(MoveToPointLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(MoveToPointLogicArgs::ArgumentsResponse::STATUS, -1);
        m_logic_args.setArg(MoveToPointLogicArgs::ArgumentsResponse::MESSAGE, error);
        return false;
    }

    m_move_to_point.m_pozycja_x = m_logic_args.getArg(MoveToPointLogicArgs::ArgumentsQuery::POSITION_X, &was_ok).toInt();
    if(false == was_ok || m_move_to_point.m_pozycja_x > 1 || m_move_to_point.m_pozycja_x < -1)
    {
        error = "argument 'pozycja_x' jest pusty lub nieprawidlowy";
        m_logic_args.setArg(MoveToPointLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(MoveToPointLogicArgs::ArgumentsResponse::STATUS, -1);
        m_logic_args.setArg(MoveToPointLogicArgs::ArgumentsResponse::MESSAGE, error);
        return false;
    }

    m_move_to_point.m_pozycja_y = m_logic_args.getArg(MoveToPointLogicArgs::ArgumentsQuery::POSITION_Y, &was_ok).toInt();
    if(false == was_ok || m_move_to_point.m_pozycja_y > 1 || m_move_to_point.m_pozycja_y < -1)
    {
        error = "argument 'pozycja_y' jest pusty lub nieprawidlowy";
        m_logic_args.setArg(MoveToPointLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(MoveToPointLogicArgs::ArgumentsResponse::STATUS, -1);
        m_logic_args.setArg(MoveToPointLogicArgs::ArgumentsResponse::MESSAGE, error);
        return false;
    }

    return true;
}

bool MoveToPointLogic::work(QString dbConnectionNmae, QString& error)
{
    Database* db = Database::getInstance(dbConnectionNmae);

    if(!db->execQuery(&m_move_to_point))
    {
        error = db->getLastError();
        m_logic_args.setArg(MoveToPointLogicArgs::ArgumentsResponse::WAS_OK, false);
        m_logic_args.setArg(MoveToPointLogicArgs::ArgumentsResponse::STATUS, -1);
        m_logic_args.setArg(MoveToPointLogicArgs::ArgumentsResponse::MESSAGE, error);
        return false;
    }

    m_logic_args.setArg(MoveToPointLogicArgs::ArgumentsResponse::WAS_OK, m_move_to_point.getResult().was_ok);
    m_logic_args.setArg(MoveToPointLogicArgs::ArgumentsResponse::STATUS, m_move_to_point.getResult().status);
    m_logic_args.setArg(MoveToPointLogicArgs::ArgumentsResponse::MESSAGE, m_move_to_point.getResult().db_message);

    return true;
}

QString MoveToPointLogic::getResult()
{
    return m_logic_args.getResponse();
}

MoveToPointLogic* MoveToPointLogic::getTemplate()
{
    if(s_login_logic == nullptr)
        s_login_logic = new MoveToPointLogic();

    return s_login_logic;
}

QString MoveToPointLogic::getLogicName()
{
    s_logic_name = LogicList::getLogicName(LogicList::LogicMember::MoveToPointLogic);
    return s_logic_name;
}

MoveToPointLogic::~MoveToPointLogic()
{
    if(s_login_logic != nullptr)
        delete s_login_logic;
}
