#include "get_waiting_info_logic_args.h"
#include "logic_list.h"

GetWaitingInfoLogicArgs::GetWaitingInfoLogicArgs()
{
    this->reserve(m_arg_list_query, static_cast<int>(GetWaitingInfoLogicArgs::ArgumentsQuery::COUNT_Q));
    this->reserve(m_arg_list_response, static_cast<int>(GetWaitingInfoLogicArgs::ArgumentsResponse::COUNT_R - GetWaitingInfoLogicArgs::ArgumentsQuery::COUNT_Q));

    m_arg_list_query[0] = LogicList::getLogicName(LogicList::LogicMember::GetWaitingInfoLogic);
    m_arg_list_response[0] = LogicList::getLogicName(LogicList::LogicMember::GetWaitingInfoLogic);

    this->m_count_arg_query = GetWaitingInfoLogicArgs::ArgumentsQuery::COUNT_Q;
    this->m_count_arg_response = GetWaitingInfoLogicArgs::ArgumentsResponse::COUNT_R;
}
