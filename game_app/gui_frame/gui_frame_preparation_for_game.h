#ifndef GUI_FRAME_PREPARATION_FOR_GAME_H
#define GUI_FRAME_PREPARATION_FOR_GAME_H
#include <QString>

#include "i_gui_frame.h"
#include "gui_items/button.h"
#include "gui_items/player_attributes.h"
#include "gui_items/scroll_bar_creatures.h"
#include "gui_items/creature_element_choice.h"
#include "gui_items/map_position_pawn_choice.h"
#include "gui_items/waiting_box.h"

#include "../logic_controler_lib/logic/set_player_waiting_logic_args.h"

class GUIFramePreparationForGame : public I_GUIFrame
{
    Q_OBJECT

public:
    GUIFramePreparationForGame(QWidget *parent = 0);
    ~GUIFramePreparationForGame();

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
    void selectedPawn();
    void selectedEmptyCell();
    void selectedOutsideMap();

    void putOnCliecked();

    void GoStartGame();
    void GoAbort();
    void buttonStartGameClicked();
    void buttonBackClicked();

private:
    PlayerAttributes* m_player_attributes = nullptr;
    ScrollBarCreatures* m_scroll_bar_creatures = nullptr;
    CreatureElementChoice* m_creature_element_choice = nullptr;
    MapPositionPawnChoice* m_map_position_pawn_choice = nullptr;
    Button* m_button_put_on_map = nullptr;
    Button* m_button_put_off_map = nullptr;
    Button* m_button_start_game = nullptr;
    Button* m_button_back = nullptr;

    Button* m_button_1_vs_1 = nullptr;
    Button* m_button_2_vs_2 = nullptr;
    Button* m_button_1_vs_PC = nullptr;
    WaitingBox* m_waiting_box = nullptr;

    SetPlayerWaitingLogicArgs args;

};

#endif // GUI_FRAME_PREPARATION_FOR_GAME_H
