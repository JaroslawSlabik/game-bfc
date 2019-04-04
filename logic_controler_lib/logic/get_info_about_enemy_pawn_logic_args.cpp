#include "get_info_about_enemy_pawn_logic_args.h"
#include "logic_list.h"

GetInfoAboutEnemyPawnLogicArgs::GetInfoAboutEnemyPawnLogicArgs()
{
    this->reserve(m_arg_list_query, static_cast<int>(GetInfoAboutEnemyPawnLogicArgs::ArgumentsQuery::COUNT_Q));
    this->reserve(m_arg_list_response, static_cast<int>(GetInfoAboutEnemyPawnLogicArgs::ArgumentsResponse::COUNT_R - GetInfoAboutEnemyPawnLogicArgs::ArgumentsQuery::COUNT_Q));

    m_arg_list_query[0] = LogicList::getLogicName(LogicList::LogicMember::GetInfoAboutEnemyPawnLogic);
    m_arg_list_response[0] = LogicList::getLogicName(LogicList::LogicMember::GetInfoAboutEnemyPawnLogic);

    this->m_count_arg_query = GetInfoAboutEnemyPawnLogicArgs::ArgumentsQuery::COUNT_Q;
    this->m_count_arg_response = GetInfoAboutEnemyPawnLogicArgs::ArgumentsResponse::COUNT_R;
}
