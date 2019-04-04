#ifndef GET_BATTLE_PAWN_FOR_INIT_LOGIC_ARGS_H
#define GET_BATTLE_PAWN_FOR_INIT_LOGIC_ARGS_H
#include "i_logic_args_template.h"

class GetBattlePawnForInitLogicArgs : public I_LogicArgsTemplate
{
public:
    GetBattlePawnForInitLogicArgs();

    enum ArgumentsQuery
    {
        ID_PLAYER = 1,
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
        POSITION_X,
        POSITION_Y,
        ELEMENT,
        ENEMY,
        COUNT_R
    };
};

#endif // GET_BATTLE_PAWN_FOR_INIT_LOGIC_ARGS_H
