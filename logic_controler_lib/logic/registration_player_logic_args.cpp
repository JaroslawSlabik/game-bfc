#include "registration_player_logic_args.h"
#include "logic_list.h"

RegistrationPlayerLogicArgs::RegistrationPlayerLogicArgs()
{
    this->reserve(m_arg_list_query, static_cast<int>(RegistrationPlayerLogicArgs::ArgumentsQuery::COUNT_Q));
    this->reserve(m_arg_list_response, static_cast<int>(RegistrationPlayerLogicArgs::ArgumentsResponse::COUNT_R - RegistrationPlayerLogicArgs::ArgumentsQuery::COUNT_Q));

    m_arg_list_query[0] = LogicList::getLogicName(LogicList::LogicMember::RegistrationPlayerLogic);
    m_arg_list_response[0] = LogicList::getLogicName(LogicList::LogicMember::RegistrationPlayerLogic);

    this->m_count_arg_query = RegistrationPlayerLogicArgs::ArgumentsQuery::COUNT_Q;
    this->m_count_arg_response = RegistrationPlayerLogicArgs::ArgumentsResponse::COUNT_R;
}
