#ifndef SET_CREATURE_ATTRIBUTES_LOGIC_H
#define SET_CREATURE_ATTRIBUTES_LOGIC_H

#include "i_logic_template.h"
#include "set_creature_attributes_logic_args.h"

#include "../database/database_query_set_creature_attributes.h"

class SetCreatureAttributesLogic : public I_LogicTemplate
{
private:
    SetCreatureAttributesLogic();
    static SetCreatureAttributesLogic* s_login_logic;
    static QString s_logic_name;

    DatabaseQuerySetCreatureAttributes m_set_creature_attributes;

    SetCreatureAttributesLogicArgs m_logic_args;
public:
    virtual bool setArguments(QStringList arguments, QString& error) override;
    virtual bool work(QString dbConnectionNmae, QString& error) override;
    virtual QString getResult() override;

    static QString getLogicName();
    static SetCreatureAttributesLogic* getTemplate();

    virtual ~SetCreatureAttributesLogic();
};

#endif // SET_CREATURE_ATTRIBUTES_LOGIC_H
