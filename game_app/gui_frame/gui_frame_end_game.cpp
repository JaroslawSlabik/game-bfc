#include "gui_frame_end_game.h"

GUIFrameEndGame::GUIFrameEndGame(QWidget *parent)
{

}

GUIFrameEndGame::~GUIFrameEndGame()
{

}

void GUIFrameEndGame::initialize()
{
    m_player_attributes = new PlayerAttributes;
    m_player_attributes->setPosition(QVector2D(40, 300));
    m_player_attributes->setSize(QVector2D(800, 40));
    PlayerInfo pl;
    pl.setLevel(1);
    pl.setExperience(0);
    pl.setExperienceToNextLevel(500);
    m_player_attributes->loadPlayerFromPLayerInfo(pl);

    m_button_main_windows = new Button;
    m_button_main_windows->setPosition(720, 700);
    m_button_main_windows->setScale(200, 30);
    m_button_main_windows->setColorText(QColor(255,0,255));
    m_button_main_windows->setBaseColor(QColor(0,0,255));
    m_button_main_windows->setColorClicked(QColor(100,100,100));
    m_button_main_windows->setColorMoveOn(QColor(140,255,140));
    m_button_main_windows->setFont("Arial.ttf", 20);
    m_button_main_windows->setText("Główne okno", QVector2D(10, 22));

    m_button_replay_game  = new Button;
    m_button_replay_game->setPosition(20, 700);
    m_button_replay_game->setScale(250, 30);
    m_button_replay_game->setColorText(QColor(255,0,255));
    m_button_replay_game->setBaseColor(QColor(0,0,255));
    m_button_replay_game->setColorClicked(QColor(100,100,100));
    m_button_replay_game->setColorMoveOn(QColor(140,255,140));
    m_button_replay_game->setFont("Arial.ttf", 20);
    m_button_replay_game->setText("Powtórz rogrywkę", QVector2D(10, 22));

    m_label_result = new OpenGLTextRender2D;
    m_label_result->setFontName("Arial.ttf");
    m_label_result->setFontSize(30);
    m_label_result->setColorText(QColor(255,0,0));
    m_label_result->setTextRender("PRZEGRANA");
    m_label_result->setPosition(QVector2D(400,200));

    m_label_score_points = new OpenGLTextRender2D;
    m_label_score_points->setFontName("Arial.ttf");
    m_label_score_points->setFontSize(15);
    m_label_score_points->setColorText(QColor(255,0,0));
    m_label_score_points->setTextRender("Zdobyte punkty: 0");
    m_label_score_points->setPosition(QVector2D(400,250));
}

void GUIFrameEndGame::deinitialize()
{
    if(m_player_attributes)
        delete m_player_attributes;

    if(m_button_main_windows)
        delete m_button_main_windows;

    if(m_button_replay_game)
        delete m_button_replay_game;

    if(m_label_result)
        delete m_label_result;

    if(m_label_score_points)
        delete m_label_score_points;
}

void GUIFrameEndGame::draw(Shader* shader)
{
    m_player_attributes->draw(shader);
    m_button_main_windows->draw(shader);
    m_button_replay_game->draw(shader);
    m_label_result->draw(shader);
    m_label_score_points->draw(shader);
}

void GUIFrameEndGame::timerEvent(QTimerEvent * timer_event)
{

}

void GUIFrameEndGame::show()
{
    connect(m_button_main_windows, &Button::clicked, this, &GUIFrameEndGame::buttonMainWindowsClicked);
    connect(m_button_replay_game, &Button::clicked, this, &GUIFrameEndGame::buttonReplayGameClicked);
}

void GUIFrameEndGame::hide()
{
    disconnect(m_button_main_windows, &Button::clicked, this, &GUIFrameEndGame::buttonMainWindowsClicked);
    disconnect(m_button_replay_game, &Button::clicked, this, &GUIFrameEndGame::buttonReplayGameClicked);
}

void GUIFrameEndGame::receiveFromServer(const QString& response)
{

}

void GUIFrameEndGame::kayboardEventRec(QEvent::Type type, Qt::Key key, QString text)
{

}

void GUIFrameEndGame::mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button)
{
    m_button_main_windows->mouseEventRec(type, pos, button);
    m_button_replay_game->mouseEventRec(type, pos, button);
}

void GUIFrameEndGame::buttonMainWindowsClicked()
{

}

void GUIFrameEndGame::buttonReplayGameClicked()
{

}
