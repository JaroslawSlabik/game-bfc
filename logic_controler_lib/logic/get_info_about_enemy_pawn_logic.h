#ifndef GET_INFO_ABOUT_ENEMY_PAWN_H
#define GET_INFO_ABOUT_ENEMY_PAWN_H

#include "i_logic_template.h"
#include "get_info_about_enemy_pawn_logic_args.h"

#include "../database/database_query_get_info_about_enemy_pawn.h"

class GetInfoAboutEnemyPawnLogic : public I_LogicTemplate
{
private:
    GetInfoAboutEnemyPawnLogic();
    static GetInfoAboutEnemyPawnLogic* s_login_logic;
    static QString s_logic_name;

    DatabaseQueryGetInfoAboutEnemyPawn m_get_info_about_enemy_pawn;

    GetInfoAboutEnemyPawnLogicArgs m_logic_args;

public:
    virtual bool setArguments(QStringList arguments, QString& error) override;
    virtual bool work(QString dbConnectionNmae, QString& error) override;
    virtual QString getResult() override;

    static QString getLogicName();
    static GetInfoAboutEnemyPawnLogic* getTemplate();

    virtual ~GetInfoAboutEnemyPawnLogic();

};

#endif // GET_INFO_ABOUT_ENEMY_PAWN_H
