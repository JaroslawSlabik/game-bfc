#ifndef GUI_FRAME_END_GAME_H
#define GUI_FRAME_END_GAME_H
#include "i_gui_frame.h"
#include "opengl_text_render_2d.h"
#include "gui_items/player_attributes.h"
#include "gui_items/button.h"

class GUIFrameEndGame : public I_GUIFrame
{
    Q_OBJECT

public:
    GUIFrameEndGame(QWidget *parent = 0);
    ~GUIFrameEndGame();

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
    void buttonMainWindowsClicked();
    void buttonReplayGameClicked();

private:
    PlayerAttributes* m_player_attributes = nullptr;
    Button* m_button_main_windows = nullptr;
    Button* m_button_replay_game = nullptr;
    OpenGLTextRender2D* m_label_result = nullptr;
    OpenGLTextRender2D* m_label_score_points = nullptr;
};

#endif // GUI_FRAME_END_GAME_H
