#ifndef WAITING_BOX_H
#define WAITING_BOX_H
#include <QObject>
#include <QEvent>
#include <QTimer>
#include "opengl_object_2d.h"
#include "opengl_text_render_2d.h"
#include "i_gui_item.h"
#include "button.h"
#include "../logic_controler_lib/logic/get_waiting_info_logic_args.h"
#include "../logic_controler_lib/logic/set_abort_waiting_logic_args.h"

class WaitingBox : public I_GUIItem, public OpenGLObject2D
{
    Q_OBJECT

public:
    explicit WaitingBox(QObject *parent = 0) ;
    ~WaitingBox();

    virtual bool draw(Shader* shader) override;

public slots:
    virtual void mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button) override;
    virtual void kayboardEventRec(QEvent::Type type, Qt::Key key, QString text) override;
    virtual void receiveFromServer(const QString& response) override;

    void show();

private slots:
    void buttonAbortClicked();
    void sendRequestWaitingInfo();

signals:
    void abortWaiting();
    void startGame();

private:
    OpenGLTextRender2D* m_info_text_label = nullptr;
    Button* m_button_abort = nullptr;

    GetWaitingInfoLogicArgs m_waiting_info_args;
    SetAbortWaitingLogicArgs m_abort_waiting_args;
    QTimer m_timer_waiting_info;

};

#endif // WAITING_BOX_H
