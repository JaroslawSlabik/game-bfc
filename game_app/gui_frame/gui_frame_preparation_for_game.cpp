#include "gui_frame_preparation_for_game.h"

#include "../logic_controler_lib/global_struct/player_info.h"
#include "gui_frame_manager.h"

GUIFramePreparationForGame::GUIFramePreparationForGame(QWidget *parent)
{

}

GUIFramePreparationForGame::~GUIFramePreparationForGame()
{

}

void GUIFramePreparationForGame::initialize()
{
    m_player_attributes = new PlayerAttributes;
    m_player_attributes->setPosition(QVector2D(10, 10));
    m_player_attributes->setSize(QVector2D(800, 40));

    m_scroll_bar_creatures = new ScrollBarCreatures;
    m_scroll_bar_creatures->setPosition(QVector2D(20,100));
    m_scroll_bar_creatures->setSize(QVector2D(150,500));
    m_scroll_bar_creatures->setSizeItem(QVector2D(80,80), QVector2D(50,50));

    m_creature_element_choice = new CreatureElementChoice;
    m_creature_element_choice->setPosition(QVector2D(200, 100));
    m_creature_element_choice->setSize(QVector2D(300, 500));

    m_map_position_pawn_choice = new MapPositionPawnChoice;
    m_map_position_pawn_choice->setPosition(QVector2D(520, 100));
    m_map_position_pawn_choice->setSize(QVector2D(400, 400));

    m_button_put_on_map = new Button;
    m_button_put_on_map->setPosition(820, 520);
    m_button_put_on_map->setScale(100, 30);
    m_button_put_on_map->setColorText(QColor(255,0,255));
    m_button_put_on_map->setBaseColor(QColor(0,0,255));
    m_button_put_on_map->setColorClicked(QColor(100,100,100));
    m_button_put_on_map->setColorMoveOn(QColor(140,255,140));
    m_button_put_on_map->setFont("Arial.ttf", 20);
    m_button_put_on_map->setText("Postaw", QVector2D(10, 22));
    m_button_put_on_map->setVisible(false);

    m_button_put_off_map = new Button;
    m_button_put_off_map->setPosition(620, 520);
    m_button_put_off_map->setScale(100, 30);
    m_button_put_off_map->setColorText(QColor(255,0,255));
    m_button_put_off_map->setBaseColor(QColor(0,0,255));
    m_button_put_off_map->setColorClicked(QColor(100, 100, 100));
    m_button_put_off_map->setColorMoveOn(QColor(140, 255, 140));
    m_button_put_off_map->setFont("Arial.ttf", 20);
    m_button_put_off_map->setText("Usuń", QVector2D(20, 22));
    m_button_put_off_map->setVisible(false);

    m_button_start_game = new Button;
    m_button_start_game->setPosition(830, 700);
    m_button_start_game->setScale(100, 30);
    m_button_start_game->setColorText(QColor(255,0,255));
    m_button_start_game->setBaseColor(QColor(0,0,255));
    m_button_start_game->setColorClicked(QColor(100,100,100));
    m_button_start_game->setColorMoveOn(QColor(140,255,140));
    m_button_start_game->setFont("Arial.ttf", 20);
    m_button_start_game->setText("Graj", QVector2D(20, 22));

    m_button_back = new Button;
    m_button_back->setPosition(20, 700);
    m_button_back->setScale(100, 30);
    m_button_back->setColorText(QColor(255,0,255));
    m_button_back->setBaseColor(QColor(0,0,255));
    m_button_back->setColorClicked(QColor(100,100,100));
    m_button_back->setColorMoveOn(QColor(140,255,140));
    m_button_back->setFont("Arial.ttf", 20);
    m_button_back->setText("Powrót", QVector2D(20, 22));

    m_button_1_vs_1 = new Button;
    m_button_1_vs_1->setPosition(890, 560);
    m_button_1_vs_1->setScale(30, 30);
    m_button_1_vs_1->setColorText(QColor(255, 255, 255));
    m_button_1_vs_1->setBaseColor(QColor(0, 255, 0));
    m_button_1_vs_1->setColorClicked(QColor(100, 100, 100));
    m_button_1_vs_1->setColorMoveOn(QColor(140, 255, 140));
    m_button_1_vs_1->setFont("Arial.ttf", 15);
    m_button_1_vs_1->setText("1 Gracz VS 1 Gracz", QVector2D(-240, 22));

    m_button_2_vs_2 = new Button;
    m_button_2_vs_2->setPosition(890, 600);
    m_button_2_vs_2->setScale(30, 30);
    m_button_2_vs_2->setColorText(QColor(255, 255, 255));
    m_button_2_vs_2->setBaseColor(QColor(255, 0, 0));
    m_button_2_vs_2->setColorClicked(QColor(100, 100, 100));
    m_button_2_vs_2->setColorMoveOn(QColor(140, 255, 140));
    m_button_2_vs_2->setFont("Arial.ttf", 15);
    m_button_2_vs_2->setText("2 Graczy VS 2 Graczy", QVector2D(-240, 22));

    m_button_1_vs_PC = new Button;
    m_button_1_vs_PC->setPosition(890, 640);
    m_button_1_vs_PC->setScale(30, 30);
    m_button_1_vs_PC->setColorText(QColor(255, 255, 255));
    m_button_1_vs_PC->setBaseColor(QColor(255, 0, 0));
    m_button_1_vs_PC->setColorClicked(QColor(100, 100, 100));
    m_button_1_vs_PC->setColorMoveOn(QColor(140, 255, 140));
    m_button_1_vs_PC->setFont("Arial.ttf", 15);
    m_button_1_vs_PC->setText("1 Gracz VS komputer", QVector2D(-240, 22));

    m_waiting_box = new WaitingBox;
    connect(m_waiting_box, &WaitingBox::abortWaiting, this, &GUIFramePreparationForGame::GoAbort);
    connect(m_waiting_box, &WaitingBox::startGame, this, &GUIFramePreparationForGame::GoStartGame);
    connect(m_waiting_box, SIGNAL(sendToServer(QString)), this, SIGNAL(sendToServer(QString)));
}

void GUIFramePreparationForGame::deinitialize()
{
    disconnect(m_waiting_box, &WaitingBox::abortWaiting, this, &GUIFramePreparationForGame::GoAbort);
    disconnect(m_waiting_box, &WaitingBox::startGame, this, &GUIFramePreparationForGame::GoStartGame);
    disconnect(m_waiting_box, SIGNAL(sendToServer(QString)), this, SIGNAL(sendToServer(QString)));

    if(m_player_attributes)
        delete m_player_attributes;

    if(m_scroll_bar_creatures)
        delete m_scroll_bar_creatures;

    if(m_creature_element_choice)
        delete m_creature_element_choice;

    if(m_map_position_pawn_choice)
        delete m_map_position_pawn_choice;

    if(m_waiting_box)
        delete m_waiting_box;

    if(m_button_put_on_map)
        delete m_button_put_on_map;

    if(m_button_put_off_map)
        delete m_button_put_off_map;

    if(m_button_start_game)
        delete m_button_start_game;

    if(m_button_back)
        delete m_button_back;

    if(m_button_1_vs_1)
        delete m_button_1_vs_1;

    if(m_button_2_vs_2)
        delete m_button_2_vs_2;

    if(m_button_1_vs_PC)
        delete m_button_1_vs_PC;
}

void GUIFramePreparationForGame::draw(Shader* shader)
{
    m_player_attributes->draw(shader);
    m_scroll_bar_creatures->draw(shader);
    m_creature_element_choice->draw(shader);
    m_map_position_pawn_choice->draw(shader);
    m_waiting_box->draw(shader);

    m_button_put_on_map->draw(shader);
    m_button_put_off_map->draw(shader);

    m_button_start_game->draw(shader);

    m_button_back->draw(shader);

    m_button_1_vs_1->draw(shader);
    m_button_2_vs_2->draw(shader);
    m_button_1_vs_PC->draw(shader);
}

void GUIFramePreparationForGame::timerEvent(QTimerEvent * timer_event)
{

}

void GUIFramePreparationForGame::show()
{
    connect(m_player_attributes, SIGNAL(sendToServer(QString)), this, SIGNAL(sendToServer(QString)));
    connect(m_scroll_bar_creatures, SIGNAL(sendToServer(QString)), this, SIGNAL(sendToServer(QString)));
    connect(m_map_position_pawn_choice, SIGNAL(sendToServer(QString)), this, SIGNAL(sendToServer(QString)));
    connect(m_scroll_bar_creatures, &ScrollBarCreatures::selectedCreature, m_creature_element_choice, &CreatureElementChoice::selectedCreature);
    connect(m_scroll_bar_creatures, &ScrollBarCreatures::selectedCreature, m_map_position_pawn_choice, &MapPositionPawnChoice::selectedCreature);
    connect(m_button_put_on_map, &Button::clicked, this, &GUIFramePreparationForGame::putOnCliecked);
    connect(m_button_put_off_map, &Button::clicked, m_map_position_pawn_choice, &MapPositionPawnChoice::putOff);
    connect(m_map_position_pawn_choice, &MapPositionPawnChoice::selectedPawn, this, &GUIFramePreparationForGame::selectedPawn);
    connect(m_map_position_pawn_choice, &MapPositionPawnChoice::selectedEmptyCell, this, &GUIFramePreparationForGame::selectedEmptyCell);
    connect(m_map_position_pawn_choice, &MapPositionPawnChoice::selectedOutsideMap, this, &GUIFramePreparationForGame::selectedOutsideMap);
    connect(m_map_position_pawn_choice, &MapPositionPawnChoice::putOffFromMap, m_scroll_bar_creatures, &ScrollBarCreatures::putOffFromMapAccepted);
    connect(m_map_position_pawn_choice, &MapPositionPawnChoice::putOnMap, m_scroll_bar_creatures, &ScrollBarCreatures::putOnMapAccepted);
    connect(m_button_start_game, &Button::clicked, this, &GUIFramePreparationForGame::buttonStartGameClicked);
    connect(m_button_back, &Button::clicked, this, &GUIFramePreparationForGame::buttonBackClicked);

    m_player_attributes->loadPlayerFromServer();
    m_scroll_bar_creatures->loadCreaturesFromServer();
}

void GUIFramePreparationForGame::hide()
{
    disconnect(m_player_attributes, SIGNAL(sendToServer(QString)), this, SIGNAL(sendToServer(QString)));
    disconnect(m_scroll_bar_creatures, SIGNAL(sendToServer(QString)), this, SIGNAL(sendToServer(QString)));
    disconnect(m_map_position_pawn_choice, SIGNAL(sendToServer(QString)), this, SIGNAL(sendToServer(QString)));
    disconnect(m_scroll_bar_creatures, &ScrollBarCreatures::selectedCreature, m_creature_element_choice, &CreatureElementChoice::selectedCreature);
    disconnect(m_scroll_bar_creatures, &ScrollBarCreatures::selectedCreature, m_map_position_pawn_choice, &MapPositionPawnChoice::selectedCreature);
    disconnect(m_button_put_on_map, &Button::clicked, nullptr, nullptr);
    disconnect(m_button_put_off_map, &Button::clicked, m_map_position_pawn_choice, &MapPositionPawnChoice::putOff);
    disconnect(m_map_position_pawn_choice, &MapPositionPawnChoice::selectedPawn, this, &GUIFramePreparationForGame::selectedPawn);
    disconnect(m_map_position_pawn_choice, &MapPositionPawnChoice::selectedEmptyCell, this, &GUIFramePreparationForGame::selectedEmptyCell);
    disconnect(m_map_position_pawn_choice, &MapPositionPawnChoice::selectedOutsideMap, this, &GUIFramePreparationForGame::selectedOutsideMap);
    disconnect(m_map_position_pawn_choice, &MapPositionPawnChoice::putOffFromMap, m_scroll_bar_creatures, &ScrollBarCreatures::putOffFromMapAccepted);
    disconnect(m_map_position_pawn_choice, &MapPositionPawnChoice::putOnMap, m_scroll_bar_creatures, &ScrollBarCreatures::putOnMapAccepted);
    disconnect(m_button_start_game, &Button::clicked, this, &GUIFramePreparationForGame::buttonStartGameClicked);
    disconnect(m_button_back, &Button::clicked, this, &GUIFramePreparationForGame::buttonBackClicked);
}

void GUIFramePreparationForGame::receiveFromServer(const QString& response)
{
    m_scroll_bar_creatures->receiveFromServer(response);
    m_player_attributes->receiveFromServer(response);
    m_map_position_pawn_choice->receiveFromServer(response);
    m_waiting_box->receiveFromServer(response);

    if(true == args.setResponse(response))
    {
        qDebug() << __PRETTY_FUNCTION__ << " RESPONSE: " << response;

        bool was_ok = args.getArg(SetPlayerWaitingLogicArgs::ArgumentsResponse::WAS_OK).toBool();
        int status = args.getArg(SetPlayerWaitingLogicArgs::ArgumentsResponse::STATUS).toInt();
        if(true == was_ok && 4 == status)
        {
            m_waiting_box->show();
        }
        else
        {
            //TODO: wyświetl okno błędu
            qDebug() << "ERROR: " << args.getArg(SetPlayerWaitingLogicArgs::ArgumentsResponse::MESSAGE).toString();
            return;
        }
    }
}

void GUIFramePreparationForGame::kayboardEventRec(QEvent::Type type, Qt::Key key, QString text)
{
    Q_UNUSED(type);
    Q_UNUSED(key);
    Q_UNUSED(text);
}

void GUIFramePreparationForGame::mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button)
{
    if(false == m_waiting_box->getVisible())
    {
        m_scroll_bar_creatures->mouseEventRec(type, pos, button);
        m_creature_element_choice->mouseEventRec(type, pos, button);
        m_map_position_pawn_choice->mouseEventRec(type, pos, button);
        m_button_put_on_map->mouseEventRec(type, pos, button);
        m_button_put_off_map->mouseEventRec(type, pos, button);
        m_button_start_game->mouseEventRec(type, pos, button);
        m_button_back->mouseEventRec(type, pos, button);
    }

    m_waiting_box->mouseEventRec(type, pos, button);
}

void GUIFramePreparationForGame::selectedPawn()
{
    m_button_put_on_map->setVisible(false);
    m_button_put_off_map->setVisible(true);
}

void GUIFramePreparationForGame::selectedEmptyCell()
{
    m_button_put_on_map->setVisible(true);
    m_button_put_off_map->setVisible(false);
}

void GUIFramePreparationForGame::selectedOutsideMap()
{
    m_button_put_on_map->setVisible(false);
    m_button_put_off_map->setVisible(false);
}

void GUIFramePreparationForGame::putOnCliecked()
{
    m_map_position_pawn_choice->putOn(m_creature_element_choice->getChoiceElement());
}

void GUIFramePreparationForGame::GoAbort()
{
    emit backFrame();
}

void GUIFramePreparationForGame::GoStartGame()
{
    emit nextFrame();
}

void GUIFramePreparationForGame::buttonStartGameClicked()
{
    args.setArg(SetPlayerWaitingLogicArgs::ArgumentsQuery::ID_PLAYER, PlayerInfo::getIdPlayer());
    args.setArg(SetPlayerWaitingLogicArgs::ArgumentsQuery::ID_GAME_MODE, 1); //TODO: zrobić wybór game modów 1 VS 1, 2 VS 2, 1 VS PC
    qDebug() << __PRETTY_FUNCTION__ << " QUERY: " << args.getQuery();
    emit sendToServer(args.getQuery());
}

void GUIFramePreparationForGame::buttonBackClicked()
{
    emit skipToFrame(GUIFrameManager::Frame::mainWindowFrame);
}
