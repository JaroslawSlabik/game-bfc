#ifndef REGISTRATION_PLAYER_LOGIC_H
#define REGISTRATION_PLAYER_LOGIC_H
#include "i_logic_template.h"
#include "registration_player_logic_args.h"

#include "../database/database_query_registration_player.h"

class RegistrationPlayerLogic : public I_LogicTemplate
{
private:
    RegistrationPlayerLogic();
    static RegistrationPlayerLogic* s_login_logic;
    static QString s_logic_name;

    DatabaseQueryRegistrationPlayer m_registration_player;

    RegistrationPlayerLogicArgs m_logic_args;
public:
    virtual bool setArguments(QStringList arguments, QString& error) override;
    virtual bool work(QString dbConnectionNmae, QString& error) override;
    virtual QString getResult() override;

    static QString getLogicName();
    static RegistrationPlayerLogic* getTemplate();

    virtual ~RegistrationPlayerLogic();
};

#endif // REGISTRATION_PLAYER_LOGIC_H
