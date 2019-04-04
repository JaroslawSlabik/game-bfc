#include "set_creature_attributes_logic_args.h"
#include "logic_list.h"

SetCreatureAttributesLogicArgs::SetCreatureAttributesLogicArgs()
{
    this->reserve(m_arg_list_query, static_cast<int>(SetCreatureAttributesLogicArgs::ArgumentsQuery::COUNT_Q));
    this->reserve(m_arg_list_response, static_cast<int>(SetCreatureAttributesLogicArgs::ArgumentsResponse::COUNT_R - SetCreatureAttributesLogicArgs::ArgumentsQuery::COUNT_Q));

    m_arg_list_query[0] = LogicList::getLogicName(LogicList::LogicMember::SetCreatureAttributes);
    m_arg_list_response[0] = LogicList::getLogicName(LogicList::LogicMember::SetCreatureAttributes);

    this->m_count_arg_query = SetCreatureAttributesLogicArgs::ArgumentsQuery::COUNT_Q;
    this->m_count_arg_response = SetCreatureAttributesLogicArgs::ArgumentsResponse::COUNT_R;
}
