#ifndef REGISTRATION_PLAYER_LOGIC_ARGS_H
#define REGISTRATION_PLAYER_LOGIC_ARGS_H
#include "i_logic_args_template.h"

class RegistrationPlayerLogicArgs : public I_LogicArgsTemplate
{
public:
    RegistrationPlayerLogicArgs();

    enum ArgumentsQuery
    {
        NAME = 1,
        SURNAME,
        EMAIL,
        PASSWORD,
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

#endif // REGISTRATION_PLAYER_LOGIC_ARGS_H
