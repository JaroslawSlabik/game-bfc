#include "attack_logic_args.h"
#include "logic_list.h"

AttackLogicArgs::AttackLogicArgs()
{
    this->reserve(m_arg_list_query, static_cast<int>(AttackLogicArgs::ArgumentsQuery::COUNT_Q));
    this->reserve(m_arg_list_response, static_cast<int>(AttackLogicArgs::ArgumentsResponse::COUNT_R - AttackLogicArgs::ArgumentsQuery::COUNT_Q));

    m_arg_list_query[0] = LogicList::getLogicName(LogicList::LogicMember::AttackLogic);
    m_arg_list_response[0] = LogicList::getLogicName(LogicList::LogicMember::AttackLogic);

    this->m_count_arg_query = AttackLogicArgs::ArgumentsQuery::COUNT_Q;
    this->m_count_arg_response = AttackLogicArgs::ArgumentsResponse::COUNT_R;
}
