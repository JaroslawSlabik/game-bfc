#ifndef GUI_FRAME_LOGIN_H
#define GUI_FRAME_LOGIN_H

#include "i_gui_frame.h"
#include "opengl_text_render_2d.h"
#include "gui_items/text_box.h"
#include "gui_items/button.h"
#include "../logic_controler_lib/logic/login_logic_args.h"

#include <QThread>

class GUIFrameLogin : public I_GUIFrame
{
    Q_OBJECT

public:
    GUIFrameLogin(QWidget *parent = 0);
    ~GUIFrameLogin();

    virtual void initialize() override;
    virtual void deinitialize() override;
    virtual void draw(Shader* shader) override;
    virtual void timerEvent(QTimerEvent * timer_event) override;
    virtual void show() override;
    virtual void hide() override;

public slots:
    virtual void receiveFromServer(const QString& response) override;
    virtual void kayboardEventRec(QEvent::Type type, Qt::Key key, QString text) override;
    virtual void mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button) override;

private slots:
    void loginClicked();
    void registrationClicked();

private:
    OpenGLTextRender2D* text_render_part1;
    OpenGLTextRender2D* text_render_part2;
    TextBox* m_login_textbox;
    TextBox* m_password_textbox;
    Button* m_login_button;
    Button* m_registration_button;
    OpenGLTextRender2D* m_message;
    LogInLogicArgs args;

    void clear();
};

#endif //GUI_FRAME_LOGIN_H
