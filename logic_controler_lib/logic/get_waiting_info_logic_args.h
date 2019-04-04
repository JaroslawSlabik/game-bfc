#ifndef GET_WAITING_INFO_LOGIC_ARGS_H
#define GET_WAITING_INFO_LOGIC_ARGS_H
#include "i_logic_args_template.h"

class GetWaitingInfoLogicArgs : public I_LogicArgsTemplate
{
public:
    GetWaitingInfoLogicArgs();

    enum ArgumentsQuery
    {
        ID_PLAYER = 1,
        COUNT_Q
    };

    enum ArgumentsResponse
    {
        WAS_OK  = ArgumentsQuery::COUNT_Q + 1,
        STATUS,
        MESSAGE,
        ID_BATTLE,
        COUNT_R
    };
};

#endif // GET_WAITING_INFO_LOGIC_ARGS_H
