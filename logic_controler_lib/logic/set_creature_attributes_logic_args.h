#ifndef SET_CREATURE_ATTRIBUTES_LOGIC_ARGS_H
#define SET_CREATURE_ATTRIBUTES_LOGIC_ARGS_H
#include "i_logic_args_template.h"

class SetCreatureAttributesLogicArgs : public I_LogicArgsTemplate
{
public:
    SetCreatureAttributesLogicArgs();

    enum ArgumentsQuery
    {
        ID_CREATURE = 1,
        HEALTHS,
        SHIELDS,
        ATTACKS,
        POINTS_OF_MOVE,
        COUNT_Q
    };

    enum ArgumentsResponse
    {
        WAS_OK = ArgumentsQuery::COUNT_Q + 1,
        MESSAGE,
        COUNT_R
    };
};

#endif // SET_CREATURE_ATTRIBUTES_LOGIC_ARGS_H
