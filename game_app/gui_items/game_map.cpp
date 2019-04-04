#include "game_map.h"

#include <QFile>

#include "plate_mesh.h"

GameMap::GameMap(QObject *parent) :
    m_load_map(false),
    element_mark(QVector2D(-1, -1))
{
    Q_UNUSED(parent);
}

bool GameMap::loadFromFile(const QString& file_path)
{
    if(!QFile::exists(file_path))
        return false;

    QFile file(file_path);
    if(!file.open(QFile::ReadOnly))
        return false;

    QByteArray bytes = file.readAll();

    file.close();

    return loadFromBytes(bytes);
}

bool GameMap::loadFromBytes(const QByteArray& bytes)
{
    bool was_ok = false;

    if(bytes.size() < 10)
        return false;

    QList<QByteArray> lines = bytes.split('#');

    if(lines.size() < 5)
        return false;

    for(auto it = lines.begin(); it != lines.end() - 1; ++it)
    {
        it->replace(' ', QByteArray());
        it->replace('\t', QByteArray());
    }

    //Ładowanie danych o mapie
    m_map.x_size = QString(lines.at(0)).toInt(&was_ok, 10);
    if(!was_ok)
        return false;

    m_map.y_size = QString(lines.at(1)).toInt(&was_ok, 10);
    if(!was_ok)
        return false;

    m_map.item_size = QString(lines.at(2)).toInt(&was_ok, 10); // wielkosc elementu
    if(!was_ok)
        return false;

    //Wczytanie tekstury. Tektura to ostatni element pliku z mapą
    QByteArray textura_mapy = lines.at(lines.size() - 1);
    textura_mapy = textura_mapy.right(textura_mapy.size() - 2);
    m_item_texture = new Texture(textura_mapy, &was_ok);
    if(!was_ok)
    {
        qDebug() << "Nie udało sie wczytać tekstury";
        return false;
    }
    m_item_texture->setMinificationFilter(TextureFilter::Nearest); // Set nearest filtering mode for texture minification
    m_item_texture->setMinificationFilter(TextureFilter::Linear); // Set bilinear filtering mode for texture magnification
    m_item_texture->setWrapMode(TextureWrapMode::Repeat); // W

    //utworzenie tła mapy
    m_background = new OpenGLObject2D();
    m_background->setPosition(QVector2D(0,0));
    m_background->setScale(QVector2D(800,800));
    m_background->setMesh(new PlateMesh());
    m_background->setTexture(m_item_texture->getTexture());


    int vertical_size_map = lines.size() - 5;
    if(m_map.y_size != vertical_size_map)
        return false;

    //tworzenie mapy
    m_map.map = new TypeArea*[vertical_size_map];
    m_element_map = new OpenGLObject2D*[vertical_size_map];
    for(int i = 0; i < vertical_size_map; ++i)
    {
        QList<QByteArray> items_per_line = lines.at(i + 4).split(';');

        int horizontal_size_map = items_per_line.size();
        if(m_map.x_size != horizontal_size_map)
            return false;

        m_map.map[i] = new TypeArea[horizontal_size_map];
        m_element_map[i] = new OpenGLObject2D[horizontal_size_map];
        for(int j = 0; j < horizontal_size_map; ++j)
        {
            //Tworzenie elementu mapy
            unsigned int texture_rect_x = 0;
            unsigned int texture_rect_y = 0;
            TypeArea type = TypeArea::obstacle_permanent;

            convertValueToMapElementOption(QString(items_per_line.at(j)).toUInt(), texture_rect_x, texture_rect_y, type);

            m_map.map[i][j] = type;

            m_element_map[i][j].setMesh(new PlateMesh());
            m_element_map[i][j].setPosition(i * m_map.item_size, j * m_map.item_size);
            m_element_map[i][j].setScale(m_map.item_size, m_map.item_size);
            m_element_map[i][j].setTexture(m_item_texture->getTexture());
            m_element_map[i][j].setTextureRect(texture_rect_x, texture_rect_y, m_map.item_size, m_map.item_size);
        }
    }

    m_load_map = true;

    return true;
}

GameMap::Map GameMap::getMap()
{
    return m_map;
}

bool GameMap::draw(Shader *shader)
{
    if(!m_load_map)
        return false;

    for(int i = 0; i < m_map.y_size; ++i)
    {
        for(int j = 0; j < m_map.x_size; ++j)
        {
            m_element_map[i][j].draw(shader);
        }
    }

    m_background->draw(shader);

    return true;
}

void GameMap::mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button)
{
    if(type == QEvent::MouseButtonPress && button == Qt::LeftButton)
    {
        for(int i = 0; i < m_map.y_size; ++i)
        {
            for(int j = 0; j < m_map.x_size; ++j)
            {
                if(m_element_map[i][j].pointOnObject(pos))
                {
                    emit elementClicked(j, i);
                    markClickedElement(j, i);
                    return;
                }
            }
        }
    }

    if(type == QEvent::MouseMove && button == Qt::NoButton)
    {
        for(int i = 0; i < m_map.y_size; ++i)
        {
            for(int j = 0; j < m_map.x_size; ++j)
            {
                if(m_element_map[i][j].pointOnObject(pos))
                {
                    markMoveElement(j, i);
                    return;
                }
            }
        }
    }
}

bool GameMap::convertValueToMapElementOption(const unsigned int& value, unsigned int& textureRectX, unsigned int& textureRectY, GameMap::TypeArea& type)
{
    //value = 00000000 yyyyyyyy xxxxxxxx 0000pppp
    //        31								0

    type = static_cast<TypeArea>((unsigned int)((unsigned char)(value)));
    textureRectX = (unsigned int)((unsigned char)(value >> 8));
    textureRectY = (unsigned int)((unsigned char)(value >> 16));

    return true;
}

void GameMap::markClickedElement(const int& x, const int& y)
{
    for(int i = 0; i < m_map.y_size; ++i)
    {
        for(int j = 0; j < m_map.x_size; ++j)
        {
            m_element_map[i][j].setBaseColor(QColor(255,255,255));
        }
    }

    m_element_map[y][x].setBaseColor(QColor(255,0,0));
    element_mark.setX(x);
    element_mark.setY(y);
}

void GameMap::markMoveElement(const int& x, const int& y)
{
    for(int i = 0; i < m_map.y_size; ++i)
    {
        for(int j = 0; j < m_map.x_size; ++j)
        {
            if(!(element_mark.x() == j && element_mark.y() == i))
            {
                m_element_map[i][j].setBaseColor(QColor(255,255,255));
            }
        }
    }

    if(!(element_mark.x() == x && element_mark.y() == y))
    {
        m_element_map[y][x].setBaseColor(QColor(0,0,255));
    }
}
