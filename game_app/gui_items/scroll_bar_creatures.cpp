#include "scroll_bar_creatures.h"

#include "QByteArray"

#include "plate_mesh.h"
#include "../logic_controler_lib/global_struct/player_info.h"

QList<std::pair<bool, CreatureInfo>> ScrollBarCreatures::m_creature_info_list;

ScrollBarCreatures::ScrollBarCreatures(QObject *parent)
{
    Q_UNUSED(parent);

    init();
}

ScrollBarCreatures::~ScrollBarCreatures()
{
    if(m_button_back)
        delete m_button_back;

    if(m_body)
        delete m_body;

    if(m_button_next)
        delete m_button_next;

    if(m_back)
        delete m_back;

    if(m_next)
        delete m_next;

    if(m_selected)
        delete m_selected;

    if(m_used_mask_back)
        delete m_used_mask_back;

    if(m_used_mask_selected)
        delete m_used_mask_selected;

    if(m_used_mask_next)
        delete m_used_mask_next;
}

void ScrollBarCreatures::setPosition(const QVector2D& pos)
{
    m_body->setPosition(pos);
    m_button_back->setPosition(pos);

    m_button_next->setPosition(pos.x(),m_body->getPosition().y() + m_body->getScale().y() - m_size_button_y);
}

void ScrollBarCreatures::setSize(const QVector2D& size)
{
    m_body->setScale(size);
    m_button_back->setScale(size.x(), m_size_button_y);
    m_button_next->setScale(size.x(), m_size_button_y);

    m_button_next->setPosition(m_body->getPosition().x(), m_body->getPosition().y() + size.y() - m_size_button_y);
}

bool ScrollBarCreatures::setSizeItem(const QVector2D& size_selected, const QVector2D& size_unselected)
{
    float pos_x = m_body->getPosition().x();
    float pos_y = m_body->getPosition().y() + m_size_button_y;
    float size_x = m_body->getScale().x();
    float size_y = m_body->getScale().y() - m_size_button_y - m_size_button_y;

    if(m_body->getScale().y() - m_size_button_y - m_size_button_y < (size_unselected.y() * 2) + size_selected.y() + 4)
        return false; // wymiary itemów nie zmieszcza się w m_body i przesłonią oba buttony. Jest to niedupuszczalne zachowanie

    m_selected->setScale(size_selected);
    m_used_mask_selected->setScale(size_selected);

    m_back->setScale(size_unselected);
    m_used_mask_back->setScale(size_unselected);

    m_next->setScale(size_unselected);
    m_used_mask_next->setScale(size_unselected);

    //przeliczanie i ustawianie pozycji zaznaczonego herołsa
    float x_selected = pos_x + (size_x / 2.0f) - (size_selected.x() / 2.0f);
    float y_selected = pos_y + (size_y / 2.0f) - (size_selected.y() / 2.0f);
    m_selected->setPosition(x_selected, y_selected);
    m_used_mask_selected->setPosition(x_selected, y_selected);

    //przeliczanie i ustawianie pozycji poprzedniego herołsa
    float x_back = pos_x + (size_x / 2.0f) - (size_unselected.x() / 2.0f);
    float y_back = pos_y + ((y_selected - pos_y) / 2.0f) - (size_unselected.x() / 2.0f);
    m_back->setPosition(x_back, y_back);
    m_used_mask_back->setPosition(x_back, y_back);

    //przeliczanie i ustawianie pozycji nstępnego herołsa
    float x_next = pos_x + (size_x / 2.0f) - (size_unselected.x() / 2.0f);
    float y_next = (y_selected + size_selected.y()) + (((pos_y + size_y) - (y_selected + size_selected.y())) / 2.0f) - (size_unselected.y() / 2.0f);

    m_next->setPosition(x_next, y_next);
    m_used_mask_next->setPosition(x_next, y_next);

    return true;
}

bool ScrollBarCreatures::draw(Shader* shader)
{
     m_body->draw(shader);

    if(m_draw_selected)
    {
        m_selected->draw(shader);
        if(m_is_used_selected)
            m_used_mask_selected->draw(shader);
    }
    if(m_draw_back)
    {
        m_back->draw(shader);
        if(m_is_used_back)
            m_used_mask_back->draw(shader);
    }
    if(m_draw_next)
    {
        m_next->draw(shader);
        if(m_is_used_next)
            m_used_mask_next->draw(shader);
    }

    m_button_back->draw(shader);
    m_button_next->draw(shader);

    return true;
}

void ScrollBarCreatures::mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button)
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

void ScrollBarCreatures::kayboardEventRec(QEvent::Type type, Qt::Key key, QString text)
{
    Q_UNUSED(type);
    Q_UNUSED(key);
    Q_UNUSED(text);
}

void ScrollBarCreatures::receiveFromServer(const QString& response)
{
    if(args.setResponse(response))
    {
        qDebug() << __PRETTY_FUNCTION__ << " RESPONSE: " << response;
        QList<QString> ids_creature = args.getArg(GetCreaturesLogicArgs::ArgumentsResponse::IDS_CREATURE).toString().split("}{");
        QList<QString> names = args.getArg(GetCreaturesLogicArgs::ArgumentsResponse::NAMES).toString().split("}{");
        QList<QString> descriptions = args.getArg(GetCreaturesLogicArgs::ArgumentsResponse::DESCRIPTIONS).toString().split("}{");
        QList<QString> healths = args.getArg(GetCreaturesLogicArgs::ArgumentsResponse::HEALTHS).toString().split("}{");
        QList<QString> shields = args.getArg(GetCreaturesLogicArgs::ArgumentsResponse::SHIELDS).toString().split("}{");
        QList<QString> attacks = args.getArg(GetCreaturesLogicArgs::ArgumentsResponse::ATTACKS).toString().split("}{");
        QList<QString> points_of_move = args.getArg(GetCreaturesLogicArgs::ArgumentsResponse::POINTS_OF_MOVE).toString().split("}{");
        QList<QString> textures = args.getArg(GetCreaturesLogicArgs::ArgumentsResponse::TEXTURES).toString().split("}{");

        for(int i = 0; i < ids_creature.size(); ++i)
        {
            CreatureInfo info;
            info.m_id = ids_creature.at(i).toLongLong();
            info.m_name = names.at(i);
            info.m_description = descriptions.at(i);
            info.m_health = healths.at(i).toInt();
            info.m_shield = shields.at(i).toInt();
            info.m_attack = attacks.at(i).toInt();
            info.m_point_of_move = points_of_move.at(i).toInt();
            info.m_texture = QByteArray::fromBase64(textures.at(i).toUtf8());
            m_creature_info_list.push_back(std::make_pair(false, info));
        }

        refresh(m_selected_index, m_creature_info_list.size());
    }
}

void ScrollBarCreatures::saveClicked(CreatureInfo creature)
{
    for(int i = 0; i < m_creature_info_list.size(); ++i)
    {
        if(m_creature_info_list[i].second.m_id == creature.m_id)
        {
            m_creature_info_list[i].second = creature;
            break;
        }
    }
}

void ScrollBarCreatures::putOnMapAccepted(qlonglong id_creature)
{
    for(int i = 0; i < m_creature_info_list.size(); ++i)
    {
        if(m_creature_info_list[i].second.m_id == id_creature)
        {
            m_creature_info_list[i].first = true;
            break;
        }
    }

    int size_list = m_creature_info_list.size();
    refresh(m_selected_index, size_list);
}

void ScrollBarCreatures::putOffFromMapAccepted(qlonglong id_creature)
{
    for(int i = 0; i < m_creature_info_list.size(); ++i)
    {
        if(m_creature_info_list[i].second.m_id == id_creature)
        {
            m_creature_info_list[i].first = false;
            break;
        }
    }

    int size_list = m_creature_info_list.size();
    refresh(m_selected_index, size_list);
}

void ScrollBarCreatures::init()
{
    m_button_back = new OpenGLObject2D();
    m_body = new OpenGLObject2D();
    m_button_next = new OpenGLObject2D();

    m_texture_is_used = new Texture(QString(":/resources/is_used.png"));
    m_used_mask_back = new OpenGLObject2D();
    m_used_mask_back->setMesh(new PlateMesh());
    m_used_mask_back->setTexture(m_texture_is_used);
    m_used_mask_next = new OpenGLObject2D();
    m_used_mask_next->setMesh(new PlateMesh());
    m_used_mask_next->setTexture(m_texture_is_used);
    m_used_mask_selected = new OpenGLObject2D();
    m_used_mask_selected->setMesh(new PlateMesh());
    m_used_mask_selected->setTexture(m_texture_is_used);

    m_body->setMesh(new PlateMesh());
    m_button_back->setMesh(new PlateMesh());
    m_button_next->setMesh(new PlateMesh());

    m_body->setBaseColor(QColor(255,0,0));
    m_button_back->setBaseColor(QColor(0,255,0));
    m_button_next->setBaseColor(QColor(0,0,255));

    m_back = new Creature();
    m_next = new Creature();
    m_selected = new Creature();
}

void ScrollBarCreatures::select_next()
{
    int size_list = m_creature_info_list.size();

    if(size_list == 0 || m_selected_index + 1 == size_list)
        return;

    m_selected_index++;

    if(m_selected_index + 2 == size_list)
    {
        args.setArg(GetCreaturesLogicArgs::ArgumentsQuery::ID_GAMER, PlayerInfo::getIdPlayer());
        args.setArg(GetCreaturesLogicArgs::ArgumentsQuery::LP_CREATURE, m_creature_info_list.size());

        qDebug() << __PRETTY_FUNCTION__ << " QUERY: " << args.getQuery();
        emit sendToServer(args.getQuery());
    }

    refresh(m_selected_index, size_list);
}

void ScrollBarCreatures::select_back()
{
    int size_list = m_creature_info_list.size();

    if(size_list == 0 || m_selected_index == 0)
        return;

    m_selected_index--;

    refresh(m_selected_index, size_list);
}

void ScrollBarCreatures::refresh(int selected_index, int size_list)
{
    if(selected_index == 0 && size_list == 0)
    {
        m_draw_selected = false;
        m_draw_next = false;
        m_draw_back = false;

        return;
    }

    if(selected_index == 0) // jeśli pierwszy element listy jest zaznaczony
    {
        m_draw_next = true;
        m_draw_back = false;

        m_next->setInfo(m_creature_info_list.at(selected_index + 1).second);

        m_is_used_next = m_creature_info_list.at(selected_index + 1).first;
    }
    else if(m_selected_index > 0 && m_selected_index + 1 < size_list) // jeśli jakiś środkowy element listy jest zaznaczony
    {
        m_draw_next = true;
        m_draw_back = true;

        m_next->setInfo(m_creature_info_list.at(selected_index + 1).second);
        m_back->setInfo(m_creature_info_list.at(m_selected_index - 1).second);

        m_is_used_next = m_creature_info_list.at(selected_index + 1).first;
        m_is_used_back = m_creature_info_list.at(m_selected_index - 1).first;
    }
    else if(m_selected_index + 1 == size_list) // jeśli ostatni element listy jest zaznaczony
    {
        m_draw_next = false;
        m_draw_back = true;

        m_back->setInfo(m_creature_info_list.at(selected_index - 1).second);

        m_is_used_back = m_creature_info_list.at(selected_index - 1).first;
    }

    m_selected->setInfo(m_creature_info_list.at(selected_index).second);

    m_is_used_selected = m_creature_info_list.at(selected_index).first;

    if(false == m_is_used_selected)
    {
        emit selectedCreature(m_selected->getInfo());
    }
    else
    {
        CreatureInfo empty_info = m_selected->getInfo();
        empty_info.m_id = -1;
        empty_info.m_name += " [USED]";
        emit selectedCreature(empty_info);
    }
}

void ScrollBarCreatures::loadCreaturesFromServer()
{
    args.setArg(GetCreaturesLogicArgs::ArgumentsQuery::ID_GAMER, PlayerInfo::getIdPlayer());
    args.setArg(GetCreaturesLogicArgs::ArgumentsQuery::LP_CREATURE, m_creature_info_list.size());

    qDebug() << __PRETTY_FUNCTION__ << " QUERY: " << args.getQuery();
    emit sendToServer(args.getQuery());
}

void ScrollBarCreatures::clear()
{
    m_creature_info_list.clear();
    refresh(0,0);
}
