#ifndef LOGIC_H
#define LOGIC_H

#include <QString>
#include <QMap>

#include "i_logic_template.h"

class Logic
{
private:
    const int m_pos_logic_name = 0;
    I_LogicTemplate* m_logic = nullptr;
    QString m_last_error = "";
    QMap<QString, I_LogicTemplate*> m_map_of_logic;
    void setLogicTemplate(I_LogicTemplate* template_logic);

public:
    Logic();
    bool setArguments(QString arguments);
    bool work(QString dbConnectionNmae);
    QString getResult();
    QString getLastError();
};

#endif
