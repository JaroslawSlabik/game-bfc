#ifndef GET_INFO_ABOUT_ENEMY_PAWN_LOGIC_ARGS_H
#define GET_INFO_ABOUT_ENEMY_PAWN_LOGIC_ARGS_H
#include "i_logic_args_template.h"

class GetInfoAboutEnemyPawnLogicArgs : public I_LogicArgsTemplate
{
public:
    GetInfoAboutEnemyPawnLogicArgs();

    enum ArgumentsQuery
    {
        ID_PLAYER = 1,
        COUNT_Q
    };

    enum ArgumentsResponse
    {
        IDS_CREATURE  = ArgumentsQuery::COUNT_Q + 1,
        HEALTH,
        SHIELD,
        POINTS_OF_MOVE,
        POSITION_X,
        POSITION_Y,
        COUNT_R
    };
};

#endif // GET_INFO_ABOUT_ENEMY_PAWN_ARGS_H
