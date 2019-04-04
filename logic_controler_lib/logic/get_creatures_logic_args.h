#ifndef GET_CREATURES_LOGIC_ARGS_H
#define GET_CREATURES_LOGIC_ARGS_H
#include "i_logic_args_template.h"

class GetCreaturesLogicArgs : public I_LogicArgsTemplate
{
public:
    GetCreaturesLogicArgs();

    enum ArgumentsQuery
    {
        ID_GAMER = 1,
        LP_CREATURE,
        COUNT_Q
    };

    enum ArgumentsResponse
    {
        IDS_CREATURE = ArgumentsQuery::COUNT_Q + 1,
        NAMES,
        DESCRIPTIONS,
        HEALTHS,
        SHIELDS,
        ATTACKS,
        POINTS_OF_MOVE,
        TEXTURES,
        COUNT_R
    };
};


#endif // GET_CREATURES_LOGIC_ARGS_H
