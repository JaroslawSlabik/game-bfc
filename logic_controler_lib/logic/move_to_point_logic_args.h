#ifndef MOVE_TO_POINT_LOGIC_ARGS_H
#define MOVE_TO_POINT_LOGIC_ARGS_H
#include "i_logic_args_template.h"

class MoveToPointLogicArgs : public I_LogicArgsTemplate
{
public:
    MoveToPointLogicArgs();

    enum ArgumentsQuery
    {
        ID_CREATURE_PLAYER = 1,
        POSITION_X,
        POSITION_Y,
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

#endif // MOVE_TO_POINT_LOGIC_ARGS_H
