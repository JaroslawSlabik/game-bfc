#ifndef BOARD_CELL_H
#define BOARD_CELL_H
#include <QObject>
#include <QEvent>

#include "opengl_object.h"
#include "opengl_object_2d.h"
#include "../logic_controler_lib/global_struct/board_cell_types.h"

class BoardCell : public QObject, public OpenGLObject
{
    Q_OBJECT

public:
    explicit BoardCell(QObject* parent = 0);
    ~BoardCell();

    void setPosition(float x, float y);
    void setSize(float x, float y);
    bool setCell(int x, int y, const std::pair<BoardCellModel_e, BoardCellType_e> type, const QByteArray& bytes);
    void setClicked();
    void setMovedOn();
    void setRelease(bool all = false);

    BoardCellType_e getBoardCellType();
    int getX();
    int getY();
    QVector2D getPosition();
    QVector2D getSize();
    bool getSelected();

    virtual bool draw(Shader* shader) override;
    virtual bool pointOnObject(QVector2D point) override;

    BoardCellType_e getTypeCell();

private:
    BoardCellType_e m_type;
    BoardCellModel_e m_model;
    OpenGLObject2D* m_background;
    QVector2D m_background_position;
    QVector2D m_background_size;
    OpenGLObject2D* m_indicate_light;

    int m_x_pos;
    int m_y_pos;

    bool m_selected;

    float m_size_light = 3.0f;
};


#endif // BOARD_CELL_H
