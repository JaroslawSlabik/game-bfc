#ifndef GET_CREATURES_LOGIC_H
#define GET_CREATURES_LOGIC_H

#include "i_logic_template.h"
#include "get_creatures_logic_args.h"

#include "../database/database_query_get_player_creatures.h"

class GetCreaturesLogic : public I_LogicTemplate
{
private:
    GetCreaturesLogic();
    static GetCreaturesLogic* s_login_logic;
    static QString s_logic_name;

    DatabaseQueryGetPlayerCreatures m_get_player_creatures;

    GetCreaturesLogicArgs m_logic_args;

public:
    virtual bool setArguments(QStringList arguments, QString& error) override;
    virtual bool work(QString dbConnectionNmae, QString& error) override;
    virtual QString getResult() override;

    static QString getLogicName();
    static GetCreaturesLogic* getTemplate();

    virtual ~GetCreaturesLogic();

};

#endif // GET_CREATURES_LOGIC_H
