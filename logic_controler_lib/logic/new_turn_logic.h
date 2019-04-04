#ifndef NEW_TURN_LOGIC_H
#define NEW_TURN_LOGIC_H

#include "i_logic_template.h"
#include "new_turn_logic_args.h"

#include "../database/database_query_new_turn.h"

class NewTurnLogic : public I_LogicTemplate
{
private:
    NewTurnLogic();
    static NewTurnLogic* s_login_logic;
    static QString s_logic_name;

    DatabaseQueryNewTurn m_new_turn;

    NewTurnLogicArgs m_logic_args;

public:
    virtual bool setArguments(QStringList arguments, QString& error) override;
    virtual bool work(QString dbConnectionNmae, QString& error) override;
    virtual QString getResult() override;

    static QString getLogicName();
    static NewTurnLogic* getTemplate();

    virtual ~NewTurnLogic();

};

#endif // NEW_TURN_LOGIC_H
