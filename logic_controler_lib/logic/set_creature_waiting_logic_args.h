#ifndef SET_CREATORE_WAITING_LOGIC_ARGS_H
#define SET_CREATORE_WAITING_LOGIC_ARGS_H
#include "i_logic_args_template.h"

class SetCreatureWaitingLogicArgs : public I_LogicArgsTemplate
{
public:
    SetCreatureWaitingLogicArgs();

    enum ArgumentsQuery
    {
        ID_CREATURE = 1,
        ID_ELEMENT,
        POSITION_X,
        POSITION_Y,
        INSERTING, // if true then make insert else make delete waiting creature
        COUNT_Q
    };

    enum ArgumentsResponse
    {
        WAS_OK = ArgumentsQuery::COUNT_Q + 1,
        MESSAGE,
        COUNT_R
    };
};

#endif // SET_CREATORE_WAITING_LOGIC_ARGS_H
