#include "gui_frame/gui_frame_game.h"



GUIFrameGame::GUIFrameGame(QWidget *parent)
{

}

GUIFrameGame::~GUIFrameGame()
{

}

void GUIFrameGame::initialize()
{
    m_board_of_game = new BoardOfGame;
    m_board_of_game->setPositionWindow(20, 20);
    m_board_of_game->setSizeWindow(580, 580);

    m_map_of_pawn = new MapOfPawn;
    m_pawn_manager = new PawnManager;
    m_thread_for_pawn_manager = new QThread();

    m_pawn_review_player = new PawnReview();
    m_pawn_review_player->setSize(150, 150);
    m_pawn_review_player->setPosition(650, 50);
    m_pawn_review_player->setTitle("Twój pionek:");

    m_pawn_review_enemy = new PawnReview();
    m_pawn_review_enemy->setSize(150, 150);
    m_pawn_review_enemy->setPosition(650, 350);
    m_pawn_review_enemy->setTitle("Wrogi pionek:");

    m_new_turn = new Button;
    m_new_turn->setPosition(20 + 580, 20 + 580 + 20);
    m_new_turn->setScale(150, 30);
    m_new_turn->setColorText(QColor(255,0,255));
    m_new_turn->setBaseColor(QColor(0,0,255));
    m_new_turn->setColorClicked(QColor(100,100,100));
    m_new_turn->setColorMoveOn(QColor(140,255,140));
    m_new_turn->setFont("Arial.ttf", 20);
    m_new_turn->setText("Nowa tura", QVector2D(10, 22));

    m_unsubscribe = new Button;
    m_unsubscribe->setPosition(20, 20 + 580 + 20);
    m_unsubscribe->setScale(140, 30);
    m_unsubscribe->setColorText(QColor(255,0,255));
    m_unsubscribe->setBaseColor(QColor(0,0,255));
    m_unsubscribe->setColorClicked(QColor(100,100,100));
    m_unsubscribe->setColorMoveOn(QColor(140,255,140));
    m_unsubscribe->setFont("Arial.ttf", 20);
    m_unsubscribe->setText("Zrezygnuj", QVector2D(10, 22));

    m_map_element_label = new OpenGLTextRender2D;
    m_map_element_label->setFontName("Arial.ttf");
    m_map_element_label->setFontSize(15);
    m_map_element_label->setColorText(QColor(255, 255, 255));
    m_map_element_label->setTextRender(QString("Żywioł mapy:"));
    m_map_element_label->setPosition(650, 250);

    m_map_element_icon = new ElementIcon(ElementType_e::earth, QVector2D(650, 260), QVector2D(40,40));
}

void GUIFrameGame::deinitialize()
{
    if(m_thread_for_pawn_manager)
    {
        m_thread_for_pawn_manager->terminate();
        delete m_thread_for_pawn_manager;
    }

    if(m_board_of_game)
        delete m_board_of_game;

    if(m_map_of_pawn)
        delete m_map_of_pawn;

    if(m_pawn_manager)
        delete m_pawn_manager;

    if(m_pawn_review_player)
        delete m_pawn_review_player;

    if(m_pawn_review_enemy)
        delete m_pawn_review_enemy;

    if(m_map_element_label)
        delete m_map_element_label;

    if(m_unsubscribe)
        delete m_unsubscribe;

    if(m_new_turn)
        delete m_new_turn;

    if(m_map_element_icon)
        delete m_map_element_icon;
}

void GUIFrameGame::draw(Shader* shader)
{
    m_board_of_game->draw(shader);
    m_map_of_pawn->draw(shader);

    m_pawn_review_player->draw(shader);
    m_pawn_review_enemy->draw(shader);

    m_new_turn->draw(shader);
    m_unsubscribe->draw(shader);
    m_map_element_label->draw(shader);
    m_map_element_icon->draw(shader);
}

void GUIFrameGame::timerEvent(QTimerEvent * timer_event)
{

}

void GUIFrameGame::show()
{
    //Query connects
    connect(m_board_of_game, SIGNAL(sendToServer(QString)), this, SIGNAL(sendToServer(QString)));
    connect(m_map_of_pawn, SIGNAL(sendToServer(QString)), this, SIGNAL(sendToServer(QString)));

    //Select and move cells connects
    connect(m_board_of_game, &BoardOfGame::selectedCell, m_map_of_pawn, &MapOfPawn::selectedCell);
    connect(m_board_of_game, &BoardOfGame::Update, m_map_of_pawn, &MapOfPawn::Update);
    connect(m_board_of_game, &BoardOfGame::selectedNotCell, m_map_of_pawn, &MapOfPawn::selectedNotCell);

    //initialization connects
    connect(m_board_of_game, &BoardOfGame::DoneInit, m_map_of_pawn, &MapOfPawn::Initialization);
    connect(m_board_of_game, &BoardOfGame::initializationBoard, m_pawn_manager, &PawnManager::initializationBoard);
    connect(m_map_of_pawn, &MapOfPawn::initializationPawns, m_pawn_manager, &PawnManager::initializationPawns);

    //pawn control connects
    connect(m_map_of_pawn, &MapOfPawn::setNewPositionPawn, m_pawn_manager, &PawnManager::setNewPositionPawn);
    connect(m_pawn_manager, &PawnManager::movePawnBaseVector, m_map_of_pawn, &MapOfPawn::movePawnBaseVector);
    connect(m_pawn_manager, &PawnManager::endWork, m_map_of_pawn, &MapOfPawn::endWork);
    connect(m_pawn_manager, &PawnManager::endWork, m_board_of_game, &BoardOfGame::releaseAllBoard);

    //pawn info update connects
    connect(m_pawn_manager, &PawnManager::updatePawnInfo, m_map_of_pawn, &MapOfPawn::updatePawnInfo);

    //pawn review connects
    connect(m_map_of_pawn, &MapOfPawn::selectPawn, this, &GUIFrameGame::selectPawn);
    connect(m_map_of_pawn, &MapOfPawn::selectNotPawn, this, &GUIFrameGame::selectNotPawn);
    connect(m_board_of_game, &BoardOfGame::clearSelect, this, &GUIFrameGame::clearSelect);


    m_pawn_manager->moveToThread(m_thread_for_pawn_manager);
    m_thread_for_pawn_manager->start();

    //m_board_of_game->loadMapFromServer();

    //DELETE after TEST
    m_board_of_game->generateBoard();
}

void GUIFrameGame::hide()
{
    //Query connects
    disconnect(m_board_of_game, SIGNAL(sendToServer(QString)), this, SIGNAL(sendToServer(QString)));
    disconnect(m_map_of_pawn, SIGNAL(sendToServer(QString)), this, SIGNAL(sendToServer(QString)));

    //Select and move cells connects
    disconnect(m_board_of_game, &BoardOfGame::selectedCell, m_map_of_pawn, &MapOfPawn::selectedCell);
    disconnect(m_board_of_game, &BoardOfGame::Update, m_map_of_pawn, &MapOfPawn::Update);
    disconnect(m_board_of_game, &BoardOfGame::selectedNotCell, m_map_of_pawn, &MapOfPawn::selectedNotCell);

    //initialization connects
    disconnect(m_board_of_game, &BoardOfGame::DoneInit, m_map_of_pawn, &MapOfPawn::Initialization);
    disconnect(m_board_of_game, &BoardOfGame::initializationBoard, m_pawn_manager, &PawnManager::initializationBoard);
    disconnect(m_map_of_pawn, &MapOfPawn::initializationPawns, m_pawn_manager, &PawnManager::initializationPawns);

    //pawn control connects
    disconnect(m_map_of_pawn, &MapOfPawn::setNewPositionPawn, m_pawn_manager, &PawnManager::setNewPositionPawn);
    disconnect(m_pawn_manager, &PawnManager::movePawnBaseVector, m_map_of_pawn, &MapOfPawn::movePawnBaseVector);
    disconnect(m_pawn_manager, &PawnManager::endWork, m_map_of_pawn, &MapOfPawn::endWork);
    disconnect(m_pawn_manager, &PawnManager::endWork, m_board_of_game, &BoardOfGame::releaseAllBoard);

    //pawn info update connects
    disconnect(m_pawn_manager, &PawnManager::updatePawnInfo, m_map_of_pawn, &MapOfPawn::updatePawnInfo);
}

void GUIFrameGame::receiveFromServer(const QString& response)
{
    m_board_of_game->receiveFromServer(response);
    m_map_of_pawn->receiveFromServer(response);
}

void GUIFrameGame::kayboardEventRec(QEvent::Type type, Qt::Key key, QString text)
{

}

void GUIFrameGame::mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button)
{
    m_board_of_game->mouseEventRec(type, pos, button);
    m_new_turn->mouseEventRec(type, pos, button);
    m_unsubscribe->mouseEventRec(type, pos, button);
}

void GUIFrameGame::selectPawn(CreatureInfo info, bool mark)
{
    if(true == info.m_enemy)
    {
        if(true == mark)
        {
            m_pawn_review_enemy->setPermanentlyInfo(info);
            m_pawn_review_player->revertToPermanentlyInfo();
        }
        else
        {
            m_pawn_review_enemy->setMomentInfo(info);
            m_pawn_review_player->revertToPermanentlyInfo();
        }
    }
    else
    {
        if(true == mark)
        {
            m_pawn_review_player->setPermanentlyInfo(info);
            m_pawn_review_enemy->clear();
        }
        else
        {
            m_pawn_review_player->setMomentInfo(info);
            m_pawn_review_enemy->clear();
        }
    }
}

void GUIFrameGame::selectNotPawn(bool mark)
{
    m_pawn_review_player->revertToPermanentlyInfo();
    m_pawn_review_enemy->clear();
}

void GUIFrameGame::clearSelect()
{
    m_pawn_review_player->clear();
    m_pawn_review_enemy->clear();
}
