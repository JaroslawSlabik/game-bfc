#include "login_logic_args.h"
#include "logic_list.h"

LogInLogicArgs::LogInLogicArgs()
{
    this->reserve(m_arg_list_query, static_cast<int>(LogInLogicArgs::ArgumentsQuery::COUNT_Q));
    this->reserve(m_arg_list_response, static_cast<int>(LogInLogicArgs::ArgumentsResponse::COUNT_R - LogInLogicArgs::ArgumentsQuery::COUNT_Q));

    m_arg_list_query[0] = LogicList::getLogicName(LogicList::LogicMember::LogIn);
    m_arg_list_response[0] = LogicList::getLogicName(LogicList::LogicMember::LogIn);

    this->m_count_arg_query = LogInLogicArgs::ArgumentsQuery::COUNT_Q;
    this->m_count_arg_response = LogInLogicArgs::ArgumentsResponse::COUNT_R;
}
