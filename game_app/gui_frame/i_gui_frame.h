#ifndef I_GUI_FRAME_H
#define I_GUI_FRAME_H

#include <QObject>
#include <QMouseEvent>
#include "shader.h"

class I_GUIFrame : public QObject
{
    Q_OBJECT

public:
    virtual void kayboardEventRec(QEvent::Type type, Qt::Key key, QString text) = 0;
    virtual void mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button) = 0;
    virtual void timerEvent(QTimerEvent * timer_event) = 0;
    virtual void initialize() = 0;
    virtual void deinitialize() = 0;
    virtual void draw(Shader* shader) = 0;
    virtual void show() = 0;
    virtual void hide() = 0;
    virtual void receiveFromServer(const QString& response) = 0;

    virtual ~I_GUIFrame(){ }

signals:
    void nextFrame();
    void backFrame();
    void skipToFrame(const int& id);
    void sendToServer(const QString& query);
};

#endif //I_GUI_FRAME_H
