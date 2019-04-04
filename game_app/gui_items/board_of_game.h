#ifndef BOARD_OF_GAME_H
#define BOARD_OF_GAME_H
#include <QObject>

#include "gui_items/i_gui_item.h"
#include "gui_items/board_cell.h"
#include "opengl_object_2d.h"
#include "shader.h"
#include "../logic_controler_lib/global_struct/player_info.h"
#include "../logic_controler_lib/logic/get_battle_map_for_init_logic.h"

class BoardOfGame : public I_GUIItem, public OpenGLObject2D
{
public:
    explicit BoardOfGame(QObject *parent = 0) ;
    ~BoardOfGame();

    void setPositionWindow(float x, float y);
    void setSizeWindow(float x, float y);

    void setPositionFrame(float x, float y);
    void setSizeFrame(float x, float y);

    QVector2D getPositionBoard();
    QVector2D getSizeBoard();
    QVector2D getSizeCell();

    QVector2D getPositionWindow();
    QVector2D getSizeWindow();

    QVector2D getPositionFrame();
    QVector2D getSizeFrame();

    virtual bool draw(Shader* shader) override;

    virtual bool pointOnObject(QVector2D point) override;

    void loadMapFromServer();

    //AFTER TEST make TO PRIVATE
    bool generateBoard();

public slots:
    virtual void kayboardEventRec(QEvent::Type type, Qt::Key key, QString text) override;
    virtual void mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button) override;
    virtual void receiveFromServer(const QString& response) override;
    void releaseAllBoard();

signals:
    void selectedCell(int x, int y, bool mark);
    void selectedNotCell();
    void clearSelect();
    void DoneInit(QVector2D position, QVector2D size);
    void initializationBoard(QMap<std::pair<int, int>, BoardCellType_e> map_of_board_cell_type, int size_x, int size_y);
    void Update(QVector2D position, QVector2D size);

private:
    void moveOnBoard(QVector2D pos);
    void clickedBoard(QVector2D pos);
    void releaseBoard(QVector2D pos, bool all = false);
    void decompositionDefinitionMap(const QString& def_map, QString& size_map, QString& size_cell, QString& def_board, QString& def_image);
    bool stringToXandY(const QString& size, int& x, int& y);
    void setPositionBoard(float x, float y);
    void setSizeBoard();

    QVector2D m_last_position_mouse;
    bool m_mouse_right_button_pressing;
    int m_size_x_board;
    int m_size_y_board;
    int m_size_x_cell;
    int m_size_y_cell;
    QVector2D m_size_window;
    QVector2D m_position_window;
    BoardCell** m_board_cells;
    OpenGLObject2D* m_board;
    OpenGLObject2D* m_top_cover;
    OpenGLObject2D* m_bottom_cover;
    OpenGLObject2D* m_left_cover;
    OpenGLObject2D* m_right_cover;
    bool m_your_turn = false;
    QString m_definition_map;

    GetBattleMapForInitLogicArgs args;

    Q_OBJECT
};

#endif // BOARD_OF_GAME_H
