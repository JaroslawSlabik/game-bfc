#ifndef GAME_MAP_H
#define GAME_MAP_H
#include <QString>
#include <QByteArray>
#include <QObject>
#include <QEvent>

#include "texture.h"
#include "opengl_object_2d.h"
#include "shader.h"

class GameMap : public QObject
{
public:

    enum TypeArea
    {
        obstacle_permanent = 0,
        obstacle_on_earth,
        obstacle_in_air,
        soil,
        water,
        ice,
        other_hero
    };

    struct Map
    {
        int x_size = 0;
        int y_size = 0;
        int item_size = 0;

        TypeArea** map;
    };

    explicit GameMap(QObject *parent = 0) ;
    bool loadFromFile(const QString& file_path);
    bool loadFromBytes(const QByteArray& bytes);
    Map getMap();

    bool draw(Shader *shader);

public slots:
    void mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button);

signals:
    void elementClicked(const int& x, const int& y);

private:
    Texture* m_item_texture;
    OpenGLObject2D** m_element_map;
    OpenGLObject2D* m_background;
    bool m_load_map = false;
    Map m_map;

    bool convertValueToMapElementOption(const unsigned int& value, unsigned int& textureRectX, unsigned int& textureRectY, GameMap::TypeArea& type);
    void markClickedElement(const int& x, const int& y);
    void markMoveElement(const int& x, const int& y);

    QVector2D element_mark;

    Q_OBJECT
};

#endif // GAME_MAP_H
