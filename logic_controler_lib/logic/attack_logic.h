#ifndef ATTACK_LOGIC_H
#define ATTACK_LOGIC_H

#include "i_logic_template.h"
#include "attack_logic_args.h"

#include "../database/database_query_attack.h"

class AttackLogic : public I_LogicTemplate
{
private:
    AttackLogic();
    static AttackLogic* s_login_logic;
    static QString s_logic_name;

    DatabaseQueryAttack m_attack;

    AttackLogicArgs m_logic_args;

public:
    virtual bool setArguments(QStringList arguments, QString& error) override;
    virtual bool work(QString dbConnectionNmae, QString& error) override;
    virtual QString getResult() override;

    static QString getLogicName();
    static AttackLogic* getTemplate();

    virtual ~AttackLogic();

};

#endif // ATTACK_LOGIC_H
