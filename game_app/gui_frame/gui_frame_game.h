#ifndef GUI_FRAME_GAME_H
#define GUI_FRAME_GAME_H
#include <QThread>

#include "i_gui_frame.h"
#include "opengl_text_render_2d.h"
#include "gui_items/text_box.h"
#include "gui_items/button.h"
#include "gui_items/board_of_game.h"
#include "gui_items/map_of_pawn.h"
#include "gui_items/pawn_manager.h"
#include "gui_items/pawn_review.h"
#include "gui_items/power_icon.h"

class GUIFrameGame : public I_GUIFrame
{
    Q_OBJECT

public:
    GUIFrameGame(QWidget *parent = 0);
    ~GUIFrameGame();

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
    void selectPawn(CreatureInfo info, bool mark);
    void selectNotPawn(bool mark);
    void clearSelect();

private:
    BoardOfGame* m_board_of_game = nullptr;
    MapOfPawn* m_map_of_pawn = nullptr;
    PawnManager* m_pawn_manager = nullptr;
    QThread* m_thread_for_pawn_manager = nullptr;

    PawnReview* m_pawn_review_player = nullptr;
    PawnReview* m_pawn_review_enemy = nullptr;
    Button* m_new_turn = nullptr;
    Button* m_unsubscribe = nullptr;
    OpenGLTextRender2D* m_map_element_label = nullptr;
    ElementIcon* m_map_element_icon = nullptr;
};

#endif //GUI_FRAME_GAME_H
