#include "get_player_info_logic_args.h"
#include "logic_list.h"

GetPlayerInfoLogicArgs::GetPlayerInfoLogicArgs()
{
    this->reserve(m_arg_list_query, static_cast<int>(GetPlayerInfoLogicArgs::ArgumentsQuery::COUNT_Q));
    this->reserve(m_arg_list_response, static_cast<int>(GetPlayerInfoLogicArgs::ArgumentsResponse::COUNT_R - GetPlayerInfoLogicArgs::ArgumentsQuery::COUNT_Q));

    m_arg_list_query[0] = LogicList::getLogicName(LogicList::LogicMember::GetPlayerInfo);
    m_arg_list_response[0] = LogicList::getLogicName(LogicList::LogicMember::GetPlayerInfo);

    this->m_count_arg_query = GetPlayerInfoLogicArgs::ArgumentsQuery::COUNT_Q;
    this->m_count_arg_response = GetPlayerInfoLogicArgs::ArgumentsResponse::COUNT_R;
}
