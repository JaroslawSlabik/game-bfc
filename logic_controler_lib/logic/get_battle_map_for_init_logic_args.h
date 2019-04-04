#ifndef GET_BATTLE_MAP_LOGIC_ARGS_H
#define GET_BATTLE_MAP_LOGIC_ARGS_H
#include "i_logic_args_template.h"

class GetBattleMapForInitLogicArgs : public I_LogicArgsTemplate
{
public:
    GetBattleMapForInitLogicArgs();

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
        MAP_FILE,
        MAP_ELEMENT,
        COUNT_R
    };
};

#endif // GET_BATTLE_MAP_LOGIC_ARGS_H
