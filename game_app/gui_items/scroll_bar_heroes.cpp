#include "scroll_bar_heroes.h"

#include "plate_mesh.h"

ScrollBarHeroes::ScrollBarHeroes(QObject *parent)
{
    Q_UNUSED(parent);

    init();
}

ScrollBarHeroes::ScrollBarHeroes(const QVector2D& pos, const QVector2D& size, const QList<Hero::HeroInfo>& list_of_heroes, QObject *parent)
{
    Q_UNUSED(parent);

    init();

    setHeroesList(list_of_heroes);

    setPosition(pos);
    setSize(size);
}

ScrollBarHeroes::~ScrollBarHeroes()
{
    if(m_button_back)
        delete m_button_back;

    if(m_body)
        delete m_body;

    if(m_button_next)
        delete m_button_next;
}

void ScrollBarHeroes::init()
{
    m_button_back = new OpenGLObject2D();
    m_body = new OpenGLObject2D();
    m_button_next = new OpenGLObject2D();

    m_body->setMesh(new PlateMesh());
    m_button_back->setMesh(new PlateMesh());
    m_button_next->setMesh(new PlateMesh());

    m_body->setBaseColor(QColor(255,0,0));
    m_button_back->setBaseColor(QColor(0,255,0));
    m_button_next->setBaseColor(QColor(0,0,255));

    m_back = new Hero();
    m_next = new Hero();
    m_selected = new Hero();

    m_back->setMesh(new PlateMesh());
    m_next->setMesh(new PlateMesh());
    m_selected->setMesh(new PlateMesh());

    m_back->setBaseColor(QColor(255,255,0));
    m_next->setBaseColor(QColor(0,255,255));
    m_selected->setBaseColor(QColor(255,0,255));
}

void ScrollBarHeroes::select_next()
{
    int size_list = m_heroes_info_list.size();

    if(size_list == 0)
        return;

    if(m_selected_index + 1 >= size_list)
        return;

    m_selected_index++;

    if(m_selected_index == size_list - 1)
    {
        m_draw_next = false;
        m_draw_back = true;
    }
    else
    {
        m_draw_next = true;
        m_draw_back = true;
    }

    set_texture();

    emit selectedHeroId(m_selected_index);
}

void ScrollBarHeroes::select_back()
{
    int size_list = m_heroes_info_list.size();

    if(size_list == 0)
        return;

    if(m_selected_index == 0)
        return;

    m_selected_index--;

    if(m_selected_index == 0)
    {
        m_draw_next = true;
        m_draw_back = false;
    }
    else
    {
        m_draw_next = true;
        m_draw_back = true;
    }

    set_texture();

    emit selectedHeroId(m_selected_index);
}

void ScrollBarHeroes::set_texture()
{
    int size_list = m_heroes_info_list.size();

    if(size_list == 0)
        return;

    m_selected->setTexture(m_heroes_info_list.at(m_selected_index).m_texture);

    if(m_draw_next)
        m_selected->setTexture(m_heroes_info_list.at(m_selected_index + 1).m_texture);
    if(m_draw_back)
        m_selected->setTexture(m_heroes_info_list.at(m_selected_index - 1).m_texture);
}

void ScrollBarHeroes::setHeroesList(const QList<Hero::HeroInfo>& list_of_heroes)
{
    m_heroes_info_list = list_of_heroes;

    set_texture();

    emit selectedHeroId(m_selected_index);
}

void ScrollBarHeroes::setPosition(const QVector2D& pos)
{
    m_body->setPosition(pos);
    m_button_back->setPosition(pos);

    m_button_next->setPosition(pos.x(),m_body->getPosition().y() + m_body->getScale().y() - m_size_button_y);
}

void ScrollBarHeroes::setSize(const QVector2D& size)
{
    m_body->setScale(size);
    m_button_back->setScale(size.x(), m_size_button_y);
    m_button_next->setScale(size.x(), m_size_button_y);

    m_button_next->setPosition(m_body->getPosition().x(), m_body->getPosition().y() + size.y() - m_size_button_y);
}

bool ScrollBarHeroes::setSizeItem(const QVector2D& size_selected, const QVector2D& size_unselected)
{
    float pos_x = m_body->getPosition().x();
    float pos_y = m_body->getPosition().y() + m_size_button_y;
    float size_x = m_body->getScale().x();
    float size_y = m_body->getScale().y() - m_size_button_y - m_size_button_y;

    if(m_body->getScale().y() - m_size_button_y - m_size_button_y < (size_unselected.y() * 2) + size_selected.y() + 4)
        return false; // wymiary itemów nie zmieszcza się w m_body i przesłonią oba buttony. Jest to niedupuszczalne zachowanie

    m_selected->setScale(size_selected);

    m_back->setScale(size_unselected);
    m_next->setScale(size_unselected);

    //przeliczanie i ustawianie pozycji zaznaczonego herołsa
    float x_selected = pos_x + (size_x / 2.0f) - (size_selected.x() / 2.0f);
    float y_selected = pos_y + (size_y / 2.0f) - (size_selected.y() / 2.0f);
    m_selected->setPosition(x_selected, y_selected);

    //przeliczanie i ustawianie pozycji poprzedniego herołsa
    float x_back = pos_x + (size_x / 2.0f) - (size_unselected.x() / 2.0f);
    float y_back = pos_y + ((y_selected - pos_y) / 2.0f) - (size_unselected.x() / 2.0f);
    m_back->setPosition(x_back, y_back);

    //przeliczanie i ustawianie pozycji nstępnego herołsa
    float x_next = pos_x + (size_x / 2.0f) - (size_unselected.x() / 2.0f);
    float y_next = (y_selected + size_selected.y()) + (((pos_y + size_y) - (y_selected + size_selected.y())) / 2.0f) - (size_unselected.y() / 2.0f);

    m_next->setPosition(x_next, y_next);

    return true;
}

bool ScrollBarHeroes::draw(Shader* shader)
{
    m_selected->draw(shader);

    if(m_draw_back)
        m_back->draw(shader);
    if(m_draw_next)
        m_next->draw(shader);

    m_button_back->draw(shader);
    m_button_next->draw(shader);

    m_body->draw(shader);

    return true;
}

void ScrollBarHeroes::mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button)
{
    if(type == QEvent::MouseButtonPress && button == Qt::LeftButton)
    {
        if(m_button_back->pointOnObject(pos) || m_back->pointOnObject(pos))
        {
            select_back();
        }

        if(m_button_next->pointOnObject(pos) || m_next->pointOnObject(pos))
        {
            select_next();


        }
    }
}

void ScrollBarHeroes::receiveFromServer(const QString& response)
{

}
