#ifndef ATTACK_LOGIC_ARGS_H
#define ATTACK_LOGIC_ARGS_H
#include "i_logic_args_template.h"

class AttackLogicArgs : public I_LogicArgsTemplate
{
public:
    AttackLogicArgs();

    enum ArgumentsQuery
    {
        ID_CREATURE_PLAYER = 1,
        ID_CREATURE_ENEMY,
        DAMAGE,
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

#endif // ATTACK_LOGIC_ARGS_H
