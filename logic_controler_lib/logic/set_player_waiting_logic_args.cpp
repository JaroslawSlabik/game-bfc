#include "set_player_waiting_logic_args.h"
#include "logic_list.h"

SetPlayerWaitingLogicArgs::SetPlayerWaitingLogicArgs()
{
    this->reserve(m_arg_list_query, static_cast<int>(SetPlayerWaitingLogicArgs::ArgumentsQuery::COUNT_Q));
    this->reserve(m_arg_list_response, static_cast<int>(SetPlayerWaitingLogicArgs::ArgumentsResponse::COUNT_R - SetPlayerWaitingLogicArgs::ArgumentsQuery::COUNT_Q));

    m_arg_list_query[0] = LogicList::getLogicName(LogicList::LogicMember::SetPlayerWaiting);
    m_arg_list_response[0] = LogicList::getLogicName(LogicList::LogicMember::SetPlayerWaiting);

    this->m_count_arg_query = SetPlayerWaitingLogicArgs::ArgumentsQuery::COUNT_Q;
    this->m_count_arg_response = SetPlayerWaitingLogicArgs::ArgumentsResponse::COUNT_R;
}
