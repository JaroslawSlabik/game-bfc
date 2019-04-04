#ifndef I_GUI_ITEM_H
#define I_GUI_ITEM_H

#include <QObject>
#include <QMouseEvent>

class I_GUIItem : public QObject
{
    Q_OBJECT

public:
    virtual void kayboardEventRec(QEvent::Type type, Qt::Key key, QString text) = 0;
    virtual void mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button) = 0;
    virtual void receiveFromServer(const QString& response) = 0;

    virtual ~I_GUIItem(){ }

signals:
    void sendToServer(const QString& query);
};

#endif // I_GUI_ITEM_H
