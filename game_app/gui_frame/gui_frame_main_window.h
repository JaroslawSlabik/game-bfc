#ifndef GUI_FRAME_MAIN_WINDOW_H
#define GUI_FRAME_MAIN_WINDOW_H

#include <QString>

#include "i_gui_frame.h"
#include "gui_items/player_attributes.h"
#include "gui_items/scroll_bar_creatures.h"
#include "gui_items/creature_attributes_view.h"

class GUIFrameMainWindow : public I_GUIFrame
{
    Q_OBJECT

public:
    GUIFrameMainWindow(QWidget *parent = 0);
    ~GUIFrameMainWindow();

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
    void buttonPlayClicked();
    void buttonLogoutClicked();

private:
    PlayerAttributes* m_player_attributes = nullptr;
    ScrollBarCreatures* m_scroll_bar_creatures = nullptr;
    CreatureAttributesView* m_creature_attributes_view = nullptr;
    Button* m_play = nullptr;
    Button* m_logout = nullptr;
};

#endif //GUI_FRAME_MAIN_WINDOW_H
