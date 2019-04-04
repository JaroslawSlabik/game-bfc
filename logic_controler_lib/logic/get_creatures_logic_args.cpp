#include "get_creatures_logic_args.h"
#include "logic_list.h"

GetCreaturesLogicArgs::GetCreaturesLogicArgs()
{
    this->reserve(m_arg_list_query, static_cast<int>(GetCreaturesLogicArgs::ArgumentsQuery::COUNT_Q));
    this->reserve(m_arg_list_response, static_cast<int>(GetCreaturesLogicArgs::ArgumentsResponse::COUNT_R - GetCreaturesLogicArgs::ArgumentsQuery::COUNT_Q));

    m_arg_list_query[0] = LogicList::getLogicName(LogicList::LogicMember::GetCreatures);
    m_arg_list_response[0] = LogicList::getLogicName(LogicList::LogicMember::GetCreatures);

    this->m_count_arg_query = GetCreaturesLogicArgs::ArgumentsQuery::COUNT_Q;
    this->m_count_arg_response = GetCreaturesLogicArgs::ArgumentsResponse::COUNT_R;
}
