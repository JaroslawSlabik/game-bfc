#ifndef MOVE_TO_POINT_LOGIC_H
#define MOVE_TO_POINT_LOGIC_H

#include "i_logic_template.h"
#include "move_to_point_logic_args.h"

#include "../database/database_query_move_to_point.h"

class MoveToPointLogic : public I_LogicTemplate
{
private:
    MoveToPointLogic();
    static MoveToPointLogic* s_login_logic;
    static QString s_logic_name;

    DatabaseQueryMoveToPoint m_move_to_point;

    MoveToPointLogicArgs m_logic_args;

public:
    virtual bool setArguments(QStringList arguments, QString& error) override;
    virtual bool work(QString dbConnectionNmae, QString& error) override;
    virtual QString getResult() override;

    static QString getLogicName();
    static MoveToPointLogic* getTemplate();

    virtual ~MoveToPointLogic();

};

#endif // MOVE_TO_POINT_LOGIC_H
