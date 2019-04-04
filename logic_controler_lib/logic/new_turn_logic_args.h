#ifndef NEW_TURN_LOGIC_ARGS_H
#define NEW_TURN_LOGIC_ARGS_H
#include "i_logic_args_template.h"

class NewTurnLogicArgs : public I_LogicArgsTemplate
{
public:
    NewTurnLogicArgs();

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
        COUNT_R
    };
};

#endif // NEW_TURN_LOGIC_ARGS_H
