#include "set_abort_waiting_logic_args.h"
#include "logic_list.h"

SetAbortWaitingLogicArgs::SetAbortWaitingLogicArgs()
{
    this->reserve(m_arg_list_query, static_cast<int>(SetAbortWaitingLogicArgs::ArgumentsQuery::COUNT_Q));
    this->reserve(m_arg_list_response, static_cast<int>(SetAbortWaitingLogicArgs::ArgumentsResponse::COUNT_R - SetAbortWaitingLogicArgs::ArgumentsQuery::COUNT_Q));

    m_arg_list_query[0] = LogicList::getLogicName(LogicList::LogicMember::SetAbortWaitingLogic);
    m_arg_list_response[0] = LogicList::getLogicName(LogicList::LogicMember::SetAbortWaitingLogic);

    this->m_count_arg_query = SetAbortWaitingLogicArgs::ArgumentsQuery::COUNT_Q;
    this->m_count_arg_response = SetAbortWaitingLogicArgs::ArgumentsResponse::COUNT_R;
}
