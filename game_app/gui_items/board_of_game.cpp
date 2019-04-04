#include "board_of_game.h"

#include "plate_mesh.h"

BoardOfGame::BoardOfGame(QObject *parent)
{
    m_board = new OpenGLObject2D;
    m_board->setMesh(new PlateMesh);
    m_board->setBaseColor(QColor(0, 0, 255));

    m_top_cover = new OpenGLObject2D;
    m_top_cover->setMesh(new PlateMesh);
    m_top_cover->setBaseColor(QColor(200, 200, 200));

    m_bottom_cover = new OpenGLObject2D;
    m_bottom_cover->setMesh(new PlateMesh);
    m_bottom_cover->setBaseColor(QColor(200, 200, 200));

    m_left_cover = new OpenGLObject2D;
    m_left_cover->setMesh(new PlateMesh);
    m_left_cover->setBaseColor(QColor(200, 200, 200));

    m_right_cover = new OpenGLObject2D;
    m_right_cover->setMesh(new PlateMesh);
    m_right_cover->setBaseColor(QColor(200, 200, 200));

    m_last_position_mouse = QVector2D(-1, -1);

    m_definition_map = "11 4+"
                       "40 40+"
                       "4AD4A2E-"
                       "4AD4A2E-"
                       "9A2E-"
                       "9A2E+"
                       "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";


    generateBoard();
}

BoardOfGame::~BoardOfGame()
{

}

void BoardOfGame::setPositionBoard(float pos_x, float pos_y)
{
    m_board->setPosition(pos_x, pos_y);

    for(int y = 0; y < m_size_y_board; ++y)
    {
        for(int x = 0; x < m_size_x_board; ++x)
        {
            m_board_cells[y][x].setPosition(m_board->getPosition().x() + (x * m_size_x_cell), m_board->getPosition().y() + (y * m_size_y_cell));
        }
    }
}

void BoardOfGame::setSizeBoard()
{
    QVector2D last_cell = QVector2D(
        m_board_cells[m_size_y_board - 1][m_size_x_board - 1].getPosition().x() + m_board_cells[m_size_y_board - 1][m_size_x_board - 1].getSize().x(),
        m_board_cells[m_size_y_board - 1][m_size_x_board - 1].getPosition().y() + m_board_cells[m_size_y_board - 1][m_size_x_board - 1].getSize().y()
    );

    m_board->setScale(last_cell.x() - m_board->getPosition().x(), last_cell.y() - m_board->getPosition().y());
}

void BoardOfGame::setPositionWindow(float x, float y)
{
    m_position_window = QVector2D(x,y);

    m_left_cover->setPosition(0,0);
    m_left_cover->setScale(m_position_window.x(), 1000);

    m_top_cover->setPosition(m_position_window.x(), 0);
    m_top_cover->setScale(m_size_window.x(), m_position_window.y());

    m_right_cover->setPosition(m_position_window.x() + m_size_window.x(), 0);
    m_right_cover->setScale(1000, 1000);

    m_bottom_cover->setPosition(0, m_position_window.y() + m_size_window.y());
    m_bottom_cover->setScale(1000, 1000);
}

void BoardOfGame::setSizeWindow(float x, float y)
{
    m_size_window = QVector2D(x,y);

    m_left_cover->setPosition(0,0);
    m_left_cover->setScale(m_position_window.x(), 1000);

    m_top_cover->setPosition(m_position_window.x(), 0);
    m_top_cover->setScale(m_size_window.x(), m_position_window.y());

    m_right_cover->setPosition(m_position_window.x() + m_size_window.x(), 0);
    m_right_cover->setScale(1000, 1000);

    m_bottom_cover->setPosition(0, m_position_window.y() + m_size_window.y());
    m_bottom_cover->setScale(1000, 1000);
}

void BoardOfGame::setPositionFrame(float x, float y)
{

}

void BoardOfGame::setSizeFrame(float x, float y)
{

}

QVector2D BoardOfGame::getPositionBoard()
{
    return m_board->getPosition();
}

QVector2D BoardOfGame::getSizeBoard()
{
    return m_board->getScale();
}

QVector2D BoardOfGame::getSizeCell()
{
    return m_board_cells[0][0].getSize();
}

QVector2D BoardOfGame::getPositionWindow()
{
    return m_position_window;
}

QVector2D BoardOfGame::getSizeWindow()
{
    return m_size_window;
}

QVector2D BoardOfGame::getPositionFrame()
{
    return QVector2D();
}

QVector2D BoardOfGame::getSizeFrame()
{
    return QVector2D();
}

bool BoardOfGame::draw(Shader* shader)
{
    m_board->draw(shader);

    //TODO: w pierwszej kolejnosci rysowac cell który jest pod kursorem
    for(int y = 0; y < m_size_y_board; ++y)
    {
        for(int x = 0; x < m_size_x_board; ++x)
        {
            m_board_cells[y][x].draw(shader);
        }
    }

    m_top_cover->draw(shader);
    m_bottom_cover->draw(shader);
    m_left_cover->draw(shader);
    m_right_cover->draw(shader);

    return true;
}

bool BoardOfGame::pointOnObject(QVector2D point)
{
    return true;
}

void BoardOfGame::kayboardEventRec(QEvent::Type type, Qt::Key key, QString text)
{

}

void BoardOfGame::mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button)
{
    if(pos.x() >= m_position_window.x() && pos.y() >= m_position_window.y() &&
       pos.x() <= m_position_window.x() + m_size_window.x() && pos.y() <= m_position_window.y() + m_size_window.y())
    {
        if(pos.x() >= m_board->getPosition().x() && pos.y() >= m_board->getPosition().y() &&
           pos.x() <= m_board->getPosition().x() + m_board->getScale().x() && pos.y() <= m_board->getPosition().y()  + m_board->getScale().y())
        {
            //Wyliczanie wektora potrzebnego do przesuwania mapy
            if(type == QEvent::Type::MouseButtonPress && button == Qt::MouseButton::RightButton)
            {
                m_last_position_mouse.setX(pos.x() - m_board->getPosition().x());
                m_last_position_mouse.setY(pos.y() - m_board->getPosition().y());

                m_mouse_right_button_pressing = true;
            }
            //przesuwanie mapy
            else if(type == QEvent::Type::MouseMove && m_mouse_right_button_pressing)
            {
                setPositionBoard(pos.x() - m_last_position_mouse.x(), pos.y() - m_last_position_mouse.y());

                emit Update(getPositionBoard(), getSizeCell());
            }
            //Koniec przesuwania po spuszczeniu guzika
            else if(type == QEvent::Type::MouseButtonRelease && button == Qt::MouseButton::RightButton)
            {
                m_mouse_right_button_pressing = false;
            }
            //jeśli to nie poruszanie mapą to fokusowanie pól na mapie
            else
            {
                moveOnBoard(pos);
            }
        }
        else
        {
            m_mouse_right_button_pressing = false;
            releaseBoard(pos);

            emit selectedNotCell();
        }

        if(type == QEvent::Type::MouseButtonRelease && button == Qt::MouseButton::LeftButton)
        {
            clickedBoard(pos);
        }
    }
    else
    {
        m_mouse_right_button_pressing = false;
        releaseBoard(pos);

        emit selectedNotCell();
    }
}

void BoardOfGame::receiveFromServer(const QString& response)
{
    if(args.setResponse(response))
    {
        qDebug() << __PRETTY_FUNCTION__ << " RESPONSE: " << response;
        bool was_ok = args.getArg(GetBattleMapForInitLogicArgs::ArgumentsResponse::WAS_OK).toBool();
        QString message = args.getArg(GetBattleMapForInitLogicArgs::ArgumentsResponse::MESSAGE).toString();

        if(false == was_ok)
        {
            qDebug() << message;
            return;
        }

        m_definition_map = args.getArg(GetBattleMapForInitLogicArgs::ArgumentsResponse::MAP_FILE).toString();

        was_ok = generateBoard();
        if(false == was_ok)
        {
            qDebug() << "nieudalosie";
            return;
        }

        QMap<std::pair<int, int>, BoardCellType_e> type_part_map;
        for(int y = 0; y < m_size_y_board; ++y)
        {
            for(int x = 0; x < m_size_x_board; ++x)
            {
                type_part_map.insert(std::make_pair(x, y), m_board_cells[y][x].getBoardCellType());
            }
        }
        emit initializationBoard(type_part_map, m_size_x_board, m_size_y_board);

        emit DoneInit(getPositionBoard(), getSizeCell());
    }
}

void BoardOfGame::releaseAllBoard()
{
    for(int y = 0; y < m_size_y_board; ++y)
    {
        for(int x = 0; x < m_size_x_board; ++x)
        {
            m_board_cells[y][x].setRelease(true);
        }
    }

    emit clearSelect();
}

void BoardOfGame::loadMapFromServer()
{
    args.setArg(GetBattleMapForInitLogicArgs::ArgumentsQuery::ID_PLAYER, PlayerInfo::getIdPlayer());

    qDebug() << __PRETTY_FUNCTION__ << " QUERY: " << args.getQuery();
    emit sendToServer(args.getQuery());
}

bool BoardOfGame::generateBoard()
{
    /*odczyt definicji mapy*/
    bool was_ok = false;
    QString size_map;
    QString size_cell;
    QString def_board;
    QString def_image;
    decompositionDefinitionMap(m_definition_map, size_map, size_cell, def_board, def_image);
    was_ok = stringToXandY(size_map, m_size_x_board, m_size_y_board);
    if(false == was_ok)
    {
        return false;
    }
    was_ok = stringToXandY(size_cell, m_size_x_cell, m_size_y_cell);
    if(false == was_ok)
    {
        return false;
    }

    /*tworzenie mapy*/
    m_board_cells = new BoardCell*[m_size_y_board];
    for(int y = 0; y < m_size_y_board; ++y)
    {
        m_board_cells[y] = new BoardCell[m_size_x_board];
        for(int x = 0; x < m_size_x_board; ++x)
        {
            m_board_cells[y][x].setMesh(new PlateMesh);
            m_board_cells[y][x].setBaseColor(QColor(120, 120, 120));
            m_board_cells[y][x].setSize(m_size_x_cell, m_size_y_cell);
        }
    }

    setPositionBoard(200, 200);
    setSizeBoard();

    /*zapełnianie mapę polami */
    int count = 0;
    QString count_str = "";
    QString type = "";
    QString numbers = "0123456789";
    int x = 0;
    int y = 0;
    for( QChar ch : def_board)
    {
        //jeśli znak jest cyfrą to dodaj do 'count_str'
        if(numbers.contains(ch))
        {
            count_str += ch;
            continue;
        }
        else if(QChar('-') == ch) // jeśli znak to '-' wtedy utwóż nową linię
        {
            y++;
            x = 0;
            continue;
        }
        else// W przeciwnym razie zamień 'count_str' na int i odczytaj typ pod znakiem; jeśli 'count_str' jest pusty to daj 1
        {
            if(count_str.isEmpty())
            {
                count = 1;
            }
            else
            {
                count = count_str.toInt(&was_ok);
                count_str.clear();
                if(false == was_ok)
                {
                    return false;
                }
            }

            type = ch.toUpper();
        }

        for(int i = 0; i < count; ++i)
        {
            m_board_cells[y][x].setCell(x,y, s_boardCellTypeHash.value(type), QByteArray::fromBase64(def_image.toUtf8()));
            x++;
        }
    }

    //DELETE AFTER TEST:
    QMap<std::pair<int, int>, BoardCellType_e> type_part_map;
    for(int y = 0; y < m_size_y_board; ++y)
    {
        for(int x = 0; x < m_size_x_board; ++x)
        {
            type_part_map.insert(std::make_pair(x, y), m_board_cells[y][x].getBoardCellType());
        }
    }
    emit initializationBoard(type_part_map, m_size_x_board, m_size_y_board);

    emit DoneInit(getPositionBoard(), getSizeCell());

    return true;
}

void BoardOfGame::moveOnBoard(QVector2D pos)
{
    for(int y = 0; y < m_size_y_board; ++y)
    {
        for(int x = 0; x < m_size_x_board; ++x)
        {
            m_board_cells[y][x].setRelease();
            if(m_board_cells[y][x].pointOnObject(pos))
            {
                m_board_cells[y][x].setMovedOn();

                emit selectedCell(x, y, false);
            }
        }
    }
}

void BoardOfGame::clickedBoard(QVector2D pos)
{
    bool fit = false;
    for(int y = 0; y < m_size_y_board; ++y)
    {
        for(int x = 0; x < m_size_x_board; ++x)
        {
            m_board_cells[y][x].setRelease(true);

            if(m_board_cells[y][x].pointOnObject(pos))
            {
                fit = true;

                m_board_cells[y][x].setClicked();

                emit selectedCell(x, y, true);
            }
        }
    }

    if(false == fit)
    {
        emit clearSelect();
    }
}

void BoardOfGame::releaseBoard(QVector2D pos, bool all)
{
    for(int y = 0; y < m_size_y_board; ++y)
    {
        for(int x = 0; x < m_size_x_board; ++x)
        {
            m_board_cells[y][x].setRelease(all);
            if(m_board_cells[y][x].pointOnObject(pos))
            {
                m_board_cells[y][x].setMovedOn();
            }
        }
    }
}

void BoardOfGame::decompositionDefinitionMap(const QString& def_map, QString& size_map, QString& size_cell, QString& def_board, QString& def_image)
{
    int index = 0;

    for(QChar ch : def_map)
    {
        if(0 == index)
        {
            if(QChar('+') == ch)
            {
                index++;
                continue;
            }

            size_map += ch;
        }

        if(1 == index)
        {
            if(QChar('+') == ch)
            {
                index++;
                continue;
            }

            size_cell += ch;
        }

        if(2 == index)
        {
            if(QChar('+') == ch)
            {
                index++;
                continue;
            }

            def_board += ch;
        }

        if(3 == index)
        {
            def_image += ch;
        }
    }
}

bool BoardOfGame::stringToXandY(const QString& size, int& x, int& y)
{
    bool was_ok = false;
    QString tmp;
    for(QChar ch : size)
    {
        if(QChar(' ') == ch)
        {
            x = tmp.toInt(&was_ok);
            tmp.clear();
            continue;
        }

        tmp += ch;
    }

    if(false == was_ok)
    {
        return was_ok;
    }

    y = tmp.toInt(&was_ok);

    return was_ok;
}

