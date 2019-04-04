#ifndef I_TOOL_H
#define I_TOOL_H
#include <QObject>
#include <QMap>

class ITool
{
public:
    virtual bool setOptionFromComandLine(const QMap<QString, QString>& comand_line_option, QString& error) = 0;

    virtual bool work(QString& error) = 0;

    virtual ~ITool(){}
};

#endif // I_TOOL_H
