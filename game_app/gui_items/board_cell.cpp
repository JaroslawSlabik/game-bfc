#include "board_cell.h"

#include "plate_mesh.h"
#include "texture.h"

BoardCell::BoardCell(QObject* parent)
{
    m_background = new OpenGLObject2D;
    m_background->setMesh(new PlateMesh);
    m_background->setBaseColor(QColor(255, 255, 255));

    m_indicate_light = new OpenGLObject2D;
    m_indicate_light->setMesh(new PlateMesh);
    m_indicate_light->setBaseColor(QColor(0, 130, 130));

    setRelease(true);
}

BoardCell::~BoardCell()
{

}

void BoardCell::setPosition(float x, float y)
{
    m_background_position = QVector2D(x, y);

    m_background->setPosition(m_background_position);
    m_background->setScale(m_background_size);

    m_indicate_light->setPosition(m_background_position.x() - m_size_light, m_background_position.y() - m_size_light);
    m_indicate_light->setScale(m_background_size.x() + (2 * m_size_light), m_background_size.y() + (2 * m_size_light));
}

void BoardCell::setSize(float x, float y)
{
    m_background_size = QVector2D(x, y);

    m_background->setPosition(m_background_position);
    m_background->setScale(m_background_size);

    m_indicate_light->setPosition(m_background_position.x() - m_size_light, m_background_position.y() - m_size_light);
    m_indicate_light->setScale(m_background_size.x() + (2 * m_size_light), m_background_size.y() + (2 * m_size_light));
}

bool BoardCell::setCell(int x, int y, const std::pair<BoardCellModel_e, BoardCellType_e> type, const QByteArray& bytes)
{
    m_type = type.second;
    m_model = type.first;

    m_x_pos = x;
    m_y_pos = y;

    Texture* texture = new Texture();
    texture->loadFromBytes(bytes, false, false);

    m_background->setTexture(texture);
    m_background->setTextureRect((static_cast<int>(m_model) - 1) * static_cast<int>(m_background_size.x()), 0, static_cast<int>(m_background_size.x()), static_cast<int>(m_background_size.y()));

    return true;
}

void BoardCell::setClicked()
{
    m_selected = true;
    m_indicate_light->setBaseColor(QColor(0, 0, 255));
    m_indicate_light->setVisible(true);
}

void BoardCell::setMovedOn()
{
    if(m_selected)
        return;

    m_indicate_light->setBaseColor(QColor(255, 0, 0));
    m_indicate_light->setVisible(true);
}

void BoardCell::setRelease(bool all)
{
    if(all)
    {
        m_selected = false;
        m_indicate_light->setVisible(false);
    }
    else
    {
        if(m_selected)
        {
            return;
        }

        m_indicate_light->setVisible(false);
    }
}

BoardCellType_e BoardCell::getBoardCellType()
{
    return m_type;
}

int BoardCell::getX()
{
    return m_x_pos;
}

int BoardCell::getY()
{
    return m_y_pos;
}

QVector2D BoardCell::getPosition()
{
    return m_background_position;
}

QVector2D BoardCell::getSize()
{
    return m_background_size;
}

bool BoardCell::getSelected()
{
    return m_selected;
}

bool BoardCell::draw(Shader* shader)
{
    m_indicate_light->draw(shader);
    m_background->draw(shader);

    return true;
}

bool BoardCell::pointOnObject(QVector2D point)
{
    if(!m_visible)
        return false;

    if(getPosition().x()                    <= point.x() &&
       getPosition().x() + getSize().x()   >= point.x() &&
       getPosition().y()                    <= point.y() &&
       getPosition().y() + getSize().y()   >= point.y())
        return true;

    return false;
}

BoardCellType_e BoardCell::getTypeCell()
{
    return m_type;
}
