#include "move_to_point_logic_args.h"
#include "logic_list.h"

MoveToPointLogicArgs::MoveToPointLogicArgs()
{
    this->reserve(m_arg_list_query, static_cast<int>(MoveToPointLogicArgs::ArgumentsQuery::COUNT_Q));
    this->reserve(m_arg_list_response, static_cast<int>(MoveToPointLogicArgs::ArgumentsResponse::COUNT_R - MoveToPointLogicArgs::ArgumentsQuery::COUNT_Q));

    m_arg_list_query[0] = LogicList::getLogicName(LogicList::LogicMember::MoveToPointLogic);
    m_arg_list_response[0] = LogicList::getLogicName(LogicList::LogicMember::MoveToPointLogic);

    this->m_count_arg_query = MoveToPointLogicArgs::ArgumentsQuery::COUNT_Q;
    this->m_count_arg_response = MoveToPointLogicArgs::ArgumentsResponse::COUNT_R;
}
