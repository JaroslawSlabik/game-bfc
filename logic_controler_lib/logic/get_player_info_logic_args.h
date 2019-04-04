#ifndef GET_PLAYER_INFO_LOGIC_ARGS_H
#define GET_PLAYER_INFO_LOGIC_ARGS_H
#include "i_logic_args_template.h"

class GetPlayerInfoLogicArgs : public I_LogicArgsTemplate
{
public:
    GetPlayerInfoLogicArgs();

    enum ArgumentsQuery
    {
        ID_GAMER = 1,
        COUNT_Q
    };

    enum ArgumentsResponse
    {
        NAME = ArgumentsQuery::COUNT_Q + 1,
        LEVEL,
        EXPERIENCE,
        EXPERIENCE_TO_NEXT_LEVEL,
        POINTS_TO_DISTRIBUTION,
        COUNT_R
    };
};


#endif // GET_PLAYER_INFO_LOGIC_ARGS_H
