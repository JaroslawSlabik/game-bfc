#ifndef DELETE_PLAYER_H
#define DELETE_PLAYER_H
#include "i_tool.h"
#include <QSqlDatabase>

class DeletePlayer : public ITool
{
public:
    DeletePlayer(const QSqlDatabase& database = QSqlDatabase::database());

    virtual bool setOptionFromComandLine(const QMap<QString, QString>& comand_line_option, QString& error) override;
    virtual bool work(QString& error) override;

private:
    qlonglong m_id_player;

    QSqlDatabase m_database;
};

#endif // DELETE_PLAYER_H
