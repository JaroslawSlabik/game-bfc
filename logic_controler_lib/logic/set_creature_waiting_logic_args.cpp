#include "set_creature_waiting_logic_args.h"
#include "logic_list.h"

SetCreatureWaitingLogicArgs::SetCreatureWaitingLogicArgs()
{
    this->reserve(m_arg_list_query, static_cast<int>(SetCreatureWaitingLogicArgs::ArgumentsQuery::COUNT_Q));
    this->reserve(m_arg_list_response, static_cast<int>(SetCreatureWaitingLogicArgs::ArgumentsResponse::COUNT_R - SetCreatureWaitingLogicArgs::ArgumentsQuery::COUNT_Q));

    m_arg_list_query[0] = LogicList::getLogicName(LogicList::LogicMember::SetCreatureWaiting);
    m_arg_list_response[0] = LogicList::getLogicName(LogicList::LogicMember::SetCreatureWaiting);

    this->m_count_arg_query = SetCreatureWaitingLogicArgs::ArgumentsQuery::COUNT_Q;
    this->m_count_arg_response = SetCreatureWaitingLogicArgs::ArgumentsResponse::COUNT_R;
}
