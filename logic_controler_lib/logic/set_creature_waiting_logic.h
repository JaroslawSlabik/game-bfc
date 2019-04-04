#ifndef SET_CREATORE_WAITING_LOGIC_H
#define SET_CREATORE_WAITING_LOGIC_H
#include "i_logic_template.h"
#include "set_creature_waiting_logic_args.h"

#include "../database/database_query_set_insert_creature_waiting.h"
#include "../database/database_query_set_delete_creature_waiting.h"

class SetCreatureWaitingLogic : public I_LogicTemplate
{
private:
    SetCreatureWaitingLogic();
    static SetCreatureWaitingLogic* s_login_logic;
    static QString s_logic_name;

    DatabaseQuerySetInsertCreatureWaiting m_set_insert_creature_waiting;
    DatabaseQuerySetDeleteCreatureWaiting m_set_delete_creature_waiting;
    bool m_inserting;

    SetCreatureWaitingLogicArgs m_logic_args;
public:
    virtual bool setArguments(QStringList arguments, QString& error) override;
    virtual bool work(QString dbConnectionNmae, QString& error) override;
    virtual QString getResult() override;

    static QString getLogicName();
    static SetCreatureWaitingLogic* getTemplate();

    virtual ~SetCreatureWaitingLogic();
};

#endif // SET_CREATORE_WAITING_LOGIC_H
