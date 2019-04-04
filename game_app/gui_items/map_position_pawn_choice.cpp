#include "map_position_pawn_choice.h"

#define MAX_X 4
#define MAX_Y 4

MapPositionPawnChoice::MapPositionPawnChoice()
{
    m_background = new OpenGLObject2D();
    m_background->setMesh(new PlateMesh);
    m_background->setBaseColor(QColor(120, 120, 120));

    m_map_fields = new OpenGLObject2D*[MAX_X];
    m_map_fields_creature = new Creature*[MAX_X];
    m_map_fields_element = new ElementIcon*[MAX_X];
    m_mark_position_map = new bool*[MAX_X];

    for(int i = 0; i < MAX_X; ++i)
    {
        m_map_fields[i] = new OpenGLObject2D[MAX_Y];
        m_map_fields_creature[i] = new Creature[MAX_Y];
        m_map_fields_element[i] = new ElementIcon[MAX_Y];
        m_mark_position_map[i] = new bool[MAX_Y];
    }

    for(int y = 0; y < MAX_Y; ++y)
    {
        for(int x = 0; x < MAX_X; ++x)
        {
            m_map_fields[y][x].setMesh(new PlateMesh);

            m_map_fields_creature[y][x].setVisible(false);
            m_map_fields_element[y][x].setVisible(false);

            m_map_fields[y][x].setBaseColor(QColor(200,60,60));

            m_mark_position_map[y][x] = false;
        }
    }
}

MapPositionPawnChoice::~MapPositionPawnChoice()
{

}

bool MapPositionPawnChoice::draw(Shader* shader)
{
    m_background->draw(shader);

    for(int y = 0; y < MAX_Y; ++y)
    {
        for(int x = 0; x < MAX_X; ++x)
        {
            m_map_fields[y][x].draw(shader);
            m_map_fields_creature[y][x].draw(shader);
            m_map_fields_element[y][x].draw(shader);
        }
    }

    return true;
}

void MapPositionPawnChoice::clear()
{

}

void MapPositionPawnChoice::mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button)
{
    for(int y = 0; y < MAX_Y; ++y)
    {
        for(int x = 0; x < MAX_X; ++x)
        {
            if(true == m_mark_position_map[y][x])
                continue;

            if(true == m_map_fields[y][x].pointOnObject(pos))
            {
                if(QEvent::Type::MouseButtonRelease == type && Qt::MouseButton::LeftButton == button)
                {
                    if(true == m_map_fields_creature[y][x].getVisible())
                    {
                        emit selectedPawn();
                    }
                    else
                    {
                        emit selectedEmptyCell();
                    }

                    m_map_fields[y][x].setBaseColor(QColor(60, 60, 200));

                    setMarkPosition(x, y);
                }
                else
                {
                    m_map_fields[y][x].setBaseColor(QColor(60, 200, 60));
                }
            }
            else
            {
                m_map_fields[y][x].setBaseColor(QColor(200,60,60));
            }
        }
    }
}

void MapPositionPawnChoice::kayboardEventRec(QEvent::Type type, Qt::Key key, QString text)
{
    Q_UNUSED(type);
    Q_UNUSED(key);
    Q_UNUSED(text);
}

void MapPositionPawnChoice::receiveFromServer(const QString& response)
{
    if(args.setResponse(response))
    {
        qDebug() << __PRETTY_FUNCTION__ << " RESPONSE: " << response;
        bool was_ok = args.getArg(SetCreatureWaitingLogicArgs::ArgumentsResponse::WAS_OK).toBool();
        if(false == was_ok)
        {
            qDebug() << "ERROR: " << args.getArg(SetCreatureWaitingLogicArgs::ArgumentsResponse::MESSAGE).toString();
            return;
        }

        bool putOn = args.getArg(SetCreatureWaitingLogicArgs::ArgumentsQuery::INSERTING).toBool();

        int x_mark = 0;
        int y_mark = 0;
        getMarkPosition(x_mark, y_mark);

        if(putOn)
        {
            m_map_fields_creature[y_mark][x_mark].setInfo(m_selected_creature_info);
            m_map_fields_creature[y_mark][x_mark].setVisible(true);
            m_map_fields_element[y_mark][x_mark].setElement(m_selected_element);
            m_map_fields_element[y_mark][x_mark].setVisible(true);

            emit putOnMap(m_selected_creature_info.m_id);
        }
        else // putOff
        {
            m_map_fields_creature[y_mark][x_mark].setVisible(false);
            m_map_fields_element[y_mark][x_mark].setVisible(false);

            emit putOffFromMap(m_map_fields_creature[y_mark][x_mark].getInfo().m_id);
        }

        clearMark();

        emit selectedOutsideMap();
    }
}

void MapPositionPawnChoice::selectedCreature(CreatureInfo creature)
{
    m_selected_creature_info = creature;
}

void MapPositionPawnChoice::putOn(ElementType_e element)
{
    //When id < 1 then creature is using or creature is lost
    if(m_selected_creature_info.m_id < 1)
        return;

    m_selected_element = element;

    int x_mark = 0;
    int y_mark = 0;
    getMarkPosition(x_mark, y_mark);

    args.setArg(SetCreatureWaitingLogicArgs::ArgumentsQuery::ID_CREATURE, m_selected_creature_info.m_id);
    args.setArg(SetCreatureWaitingLogicArgs::ArgumentsQuery::ID_ELEMENT, static_cast<int>(m_selected_element));
    args.setArg(SetCreatureWaitingLogicArgs::ArgumentsQuery::POSITION_X, x_mark);
    args.setArg(SetCreatureWaitingLogicArgs::ArgumentsQuery::POSITION_Y, y_mark);
    args.setArg(SetCreatureWaitingLogicArgs::ArgumentsQuery::INSERTING, true);

    qDebug() << __PRETTY_FUNCTION__ << " QUERY: " << args.getQuery();
    emit sendToServer(args.getQuery());
}

void MapPositionPawnChoice::putOff()
{
    int x_mark = 0;
    int y_mark = 0;
    getMarkPosition(x_mark, y_mark);
    qlonglong creature_id = m_map_fields_creature[y_mark][x_mark].getInfo().m_id;

    args.setArg(SetCreatureWaitingLogicArgs::ArgumentsQuery::ID_CREATURE, creature_id);
    args.setArg(SetCreatureWaitingLogicArgs::ArgumentsQuery::INSERTING, false);

    qDebug() << __PRETTY_FUNCTION__ << " QUERY: " << args.getQuery();
    emit sendToServer(args.getQuery());
}

void MapPositionPawnChoice::clearMark()
{
    for(int y = 0; y < MAX_Y; ++y)
    {
        for(int x = 0; x < MAX_X; ++x)
        {
            m_mark_position_map[y][x] = false;
        }
    }
}

void MapPositionPawnChoice::setMarkPosition(int x, int y)
{
    clearMark();

    m_mark_position_map[y][x] = true;
}

void MapPositionPawnChoice::getMarkPosition(int& x_pos, int& y_pos)
{
    for(int y = 0; y < MAX_Y; ++y)
    {
        for(int x = 0; x < MAX_X; ++x)
        {
            if(true == m_mark_position_map[y][x])
            {
                x_pos = x;
                y_pos = y;
                return;
            }
        }
    }
}

void MapPositionPawnChoice::setPosition(const QVector2D& pos)
{
    m_position = pos;

    resize();
}

void MapPositionPawnChoice::setSize(const QVector2D& size)
{
    m_size = size;

    resize();
}

void MapPositionPawnChoice::resize()
{
    float margin_x_size = (m_size.x() / MAX_X) * 0.01f;
    float margin_y_size = (m_size.y() / MAX_Y) * 0.01f;

    float field_x_size = (m_size.x() / MAX_X) - (margin_x_size * 2.0f);
    float field_y_size = (m_size.y() / MAX_Y) - (margin_y_size * 2.0f);

    m_background->setPosition(m_position.x(), m_position.y());
    m_background->setScale(m_size.x(), m_size.y());

    float pos_x = m_position.x();
    float pos_y = m_position.y();
    for(int y = 0; y < MAX_Y; ++y)
    {
        pos_y += margin_y_size;

        for(int x = 0; x < MAX_X; ++x)
        {
            pos_x += margin_x_size;

            m_map_fields[y][x].setPosition(pos_x, pos_y);
            m_map_fields[y][x].setScale(field_x_size, field_y_size);

            m_map_fields_creature[y][x].setPosition(pos_x + margin_x_size, pos_y + margin_y_size);
            m_map_fields_creature[y][x].setScale(field_x_size - (margin_x_size * 2.f), field_y_size - (margin_y_size * 2.f));

            m_map_fields_element[y][x].setPosition(pos_x + field_x_size - margin_x_size - 40, pos_y + margin_y_size);
            m_map_fields_element[y][x].setScale(40, 40);

            pos_x += field_x_size + margin_x_size;
        }

        pos_x = m_position.x();
        pos_y += field_y_size + margin_y_size;
    }
}
