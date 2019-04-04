#include "get_battle_map_for_init_logic_args.h"
#include "logic_list.h"

GetBattleMapForInitLogicArgs::GetBattleMapForInitLogicArgs()
{
    this->reserve(m_arg_list_query, static_cast<int>(GetBattleMapForInitLogicArgs::ArgumentsQuery::COUNT_Q));
    this->reserve(m_arg_list_response, static_cast<int>(GetBattleMapForInitLogicArgs::ArgumentsResponse::COUNT_R - GetBattleMapForInitLogicArgs::ArgumentsQuery::COUNT_Q));

    m_arg_list_query[0] = LogicList::getLogicName(LogicList::LogicMember::GetBattleMapForInitLogic);
    m_arg_list_response[0] = LogicList::getLogicName(LogicList::LogicMember::GetBattleMapForInitLogic);

    this->m_count_arg_query = GetBattleMapForInitLogicArgs::ArgumentsQuery::COUNT_Q;
    this->m_count_arg_response = GetBattleMapForInitLogicArgs::ArgumentsResponse::COUNT_R;
}
