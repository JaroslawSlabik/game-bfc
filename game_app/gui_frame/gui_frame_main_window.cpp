#include "gui_frame_main_window.h"

#include "gui_frame_manager.h"
#include "../logic_controler_lib/global_struct/player_info.h"

GUIFrameMainWindow::GUIFrameMainWindow(QWidget *parent)
{

}

GUIFrameMainWindow::~GUIFrameMainWindow()
{

}

void GUIFrameMainWindow::initialize()
{
    m_player_attributes = new PlayerAttributes;
    m_player_attributes->setPosition(QVector2D(10, 10));
    m_player_attributes->setSize(QVector2D(600, 40));

    m_scroll_bar_creatures = new ScrollBarCreatures;
    m_scroll_bar_creatures->setPosition(QVector2D(20,100));
    m_scroll_bar_creatures->setSize(QVector2D(150,500));
    m_scroll_bar_creatures->setSizeItem(QVector2D(80,80), QVector2D(50,50));

    m_creature_attributes_view = new CreatureAttributesView;
    m_creature_attributes_view->setPosition(QVector2D(200,160));
    m_creature_attributes_view->setSize(QVector2D(580,390));

    m_play = new Button;
    m_play->setPosition(660, 35);
    m_play->setScale(100, 30);
    m_play->setColorText(QColor(255,0,255));
    m_play->setBaseColor(QColor(0,0,255));
    m_play->setColorClicked(QColor(100,100,100));
    m_play->setColorMoveOn(QColor(140,255,140));
    m_play->setFont("Arial.ttf", 20);
    m_play->setText("Graj", QVector2D(25, 22));

    m_logout = new Button;
    m_logout->setPosition(660, 570);
    m_logout->setScale(110, 30);
    m_logout->setColorText(QColor(255,0,255));
    m_logout->setBaseColor(QColor(0,0,255));
    m_logout->setColorClicked(QColor(100,100,100));
    m_logout->setColorMoveOn(QColor(140,255,140));
    m_logout->setFont("Arial.ttf", 20);
    m_logout->setText("Wyloguj", QVector2D(10, 22));
}

void GUIFrameMainWindow::deinitialize()
{
    if(m_logout)
        delete m_logout;

    if(m_play)
        delete m_play;

    if(m_player_attributes)
        delete m_player_attributes;

    if(m_scroll_bar_creatures)
        delete m_scroll_bar_creatures;

    if(m_creature_attributes_view)
        delete m_creature_attributes_view;
}

void GUIFrameMainWindow::draw(Shader* shader)
{
    m_player_attributes->draw(shader);
    m_scroll_bar_creatures->draw(shader);
    m_creature_attributes_view->draw(shader);
    m_logout->draw(shader);
    m_play->draw(shader);
}

void GUIFrameMainWindow::timerEvent(QTimerEvent * timer_event)
{

}

void GUIFrameMainWindow::show()
{
    connect(m_player_attributes, SIGNAL(sendToServer(QString)), this, SIGNAL(sendToServer(QString)));
    connect(m_scroll_bar_creatures, SIGNAL(sendToServer(QString)), this, SIGNAL(sendToServer(QString)));
    connect(m_creature_attributes_view, SIGNAL(sendToServer(QString)), this, SIGNAL(sendToServer(QString)));
    connect(m_scroll_bar_creatures, &ScrollBarCreatures::selectedCreature, m_creature_attributes_view, &CreatureAttributesView::selectedCreature);
    connect(m_player_attributes, &PlayerAttributes::existPoints, m_creature_attributes_view, &CreatureAttributesView::existPoints);
    connect(m_creature_attributes_view, &CreatureAttributesView::minusClicked, m_player_attributes, &PlayerAttributes::minusClicked);
    connect(m_creature_attributes_view, &CreatureAttributesView::plusClicked, m_player_attributes, &PlayerAttributes::plusClicked);
    connect(m_creature_attributes_view, &CreatureAttributesView::anulujClicked, m_player_attributes, &PlayerAttributes::anulujClicked);
    connect(m_creature_attributes_view, &CreatureAttributesView::saveClicked, m_player_attributes, &PlayerAttributes::saveClicked);
    connect(m_creature_attributes_view, &CreatureAttributesView::saveClicked, m_scroll_bar_creatures, &ScrollBarCreatures::saveClicked);

    connect(m_play, &Button::clicked, this, &GUIFrameMainWindow::buttonPlayClicked);
    connect(m_logout, &Button::clicked, this, &GUIFrameMainWindow::buttonLogoutClicked);

    PlayerInfo::setLevel(1);
    PlayerInfo::setExperience(0);
    PlayerInfo::setExperienceToNextLevel(500);
    PlayerInfo::setPointsToDistribution(3);
    PlayerInfo pl;
    m_player_attributes->loadPlayerFromPLayerInfo(pl);
    m_scroll_bar_creatures->loadCreaturesFromServer();
}

void GUIFrameMainWindow::hide()
{
    disconnect(m_player_attributes, SIGNAL(sendToServer(QString)), nullptr, nullptr);
    disconnect(m_scroll_bar_creatures, SIGNAL(sendToServer(QString)), nullptr, nullptr);
    disconnect(m_creature_attributes_view, SIGNAL(sendToServer(QString)), nullptr, nullptr);
    disconnect(m_scroll_bar_creatures, &ScrollBarCreatures::selectedCreature, m_creature_attributes_view, &CreatureAttributesView::selectedCreature);
    disconnect(m_player_attributes, &PlayerAttributes::existPoints, m_creature_attributes_view, &CreatureAttributesView::existPoints);
    disconnect(m_creature_attributes_view, &CreatureAttributesView::minusClicked, m_player_attributes, &PlayerAttributes::minusClicked);
    disconnect(m_creature_attributes_view, &CreatureAttributesView::plusClicked, m_player_attributes, &PlayerAttributes::plusClicked);
    disconnect(m_creature_attributes_view, &CreatureAttributesView::anulujClicked, m_player_attributes, &PlayerAttributes::anulujClicked);
    disconnect(m_creature_attributes_view, &CreatureAttributesView::saveClicked, m_player_attributes, &PlayerAttributes::saveClicked);
    disconnect(m_creature_attributes_view, &CreatureAttributesView::saveClicked, m_scroll_bar_creatures, &ScrollBarCreatures::saveClicked);

    disconnect(m_play, &Button::clicked, this, &GUIFrameMainWindow::buttonPlayClicked);
    disconnect(m_logout, &Button::clicked, this, &GUIFrameMainWindow::buttonLogoutClicked);
}

void GUIFrameMainWindow::receiveFromServer(const QString& response)
{
    m_player_attributes->receiveFromServer(response);
    m_scroll_bar_creatures->receiveFromServer(response);
    m_creature_attributes_view->receiveFromServer(response);
}

void GUIFrameMainWindow::kayboardEventRec(QEvent::Type type, Qt::Key key, QString text)
{

}

void GUIFrameMainWindow::mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button)
{
    m_scroll_bar_creatures->mouseEventRec(type, pos, button);
    m_creature_attributes_view->mouseEventRec(type, pos, button);
    m_logout->mouseEventRec(type, pos, button);
    m_play->mouseEventRec(type, pos, button);
}

void GUIFrameMainWindow::buttonPlayClicked()
{
    emit skipToFrame(GUIFrameManager::Frame::prepareToGrameFrame);
}

void GUIFrameMainWindow::buttonLogoutClicked()
{
    PlayerInfo::clear();

    emit skipToFrame(GUIFrameManager::Frame::loginFrame);
}
