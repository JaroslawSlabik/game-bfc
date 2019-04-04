#include "get_battle_pawn_for_init_logic_args.h"
#include "logic_list.h"

GetBattlePawnForInitLogicArgs::GetBattlePawnForInitLogicArgs()
{
    this->reserve(m_arg_list_query, static_cast<int>(GetBattlePawnForInitLogicArgs::ArgumentsQuery::COUNT_Q));
    this->reserve(m_arg_list_response, static_cast<int>(GetBattlePawnForInitLogicArgs::ArgumentsResponse::COUNT_R - GetBattlePawnForInitLogicArgs::ArgumentsQuery::COUNT_Q));

    m_arg_list_query[0] = LogicList::getLogicName(LogicList::LogicMember::GetBattlePawnForInitLogic);
    m_arg_list_response[0] = LogicList::getLogicName(LogicList::LogicMember::GetBattlePawnForInitLogic);

    this->m_count_arg_query = GetBattlePawnForInitLogicArgs::ArgumentsQuery::COUNT_Q;
    this->m_count_arg_response = GetBattlePawnForInitLogicArgs::ArgumentsResponse::COUNT_R;
}
