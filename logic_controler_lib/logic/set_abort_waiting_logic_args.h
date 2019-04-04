#ifndef SET_ABORT_WAITING_LOGIC_ARGS_H
#define SET_ABORT_WAITING_LOGIC_ARGS_H
#include "i_logic_args_template.h"

class SetAbortWaitingLogicArgs : public I_LogicArgsTemplate
{
public:
    SetAbortWaitingLogicArgs();

    enum ArgumentsQuery
    {
        ID_PLAYER = 1,
        COUNT_Q
    };

    enum ArgumentsResponse
    {
        WAS_OK = ArgumentsQuery::COUNT_Q + 1,
        STATUS,
        MESSAGE,
        COUNT_R
    };
};


#endif // SET_ABORT_WAITING_LOGIC_ARGS_H
