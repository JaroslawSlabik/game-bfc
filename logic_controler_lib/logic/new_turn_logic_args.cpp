#include "new_turn_logic_args.h"
#include "logic_list.h"

NewTurnLogicArgs::NewTurnLogicArgs()
{
    this->reserve(m_arg_list_query, static_cast<int>(NewTurnLogicArgs::ArgumentsQuery::COUNT_Q));
    this->reserve(m_arg_list_response, static_cast<int>(NewTurnLogicArgs::ArgumentsResponse::COUNT_R - NewTurnLogicArgs::ArgumentsQuery::COUNT_Q));

    m_arg_list_query[0] = LogicList::getLogicName(LogicList::LogicMember::NewTurnLogic);
    m_arg_list_response[0] = LogicList::getLogicName(LogicList::LogicMember::NewTurnLogic);

    this->m_count_arg_query = NewTurnLogicArgs::ArgumentsQuery::COUNT_Q;
    this->m_count_arg_response = NewTurnLogicArgs::ArgumentsResponse::COUNT_R;
}
