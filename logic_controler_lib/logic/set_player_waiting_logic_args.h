#ifndef SET_PLAYER_WAITING_LOGIC_ARGS_H
#define SET_PLAYER_WAITING_LOGIC_ARGS_H
#include "i_logic_args_template.h"

class SetPlayerWaitingLogicArgs : public I_LogicArgsTemplate
{
public:
    SetPlayerWaitingLogicArgs();

    enum ArgumentsQuery
    {
        ID_PLAYER = 1,
        ID_GAME_MODE,
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

#endif // SET_PLAYER_WAITING_LOGIC_ARGS_H
