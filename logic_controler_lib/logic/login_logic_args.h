#ifndef LOGIN_LOGIC_ARGS_H
#define LOGIN_LOGIC_ARGS_H
#include "i_logic_args_template.h"

class LogInLogicArgs : public I_LogicArgsTemplate
{
public:
    LogInLogicArgs();

    enum ArgumentsQuery
    {
        LOGIN = 1,
        PASSWORD,
        COUNT_Q
    };

    enum ArgumentsResponse
    {
        WAS_OK = ArgumentsQuery::COUNT_Q + 1,
        MESSAGE,
        kERROR,
        ID_GAMER,
        COUNT_R
    };
};

#endif // LOGIN_LOGIC_ARGS_H
