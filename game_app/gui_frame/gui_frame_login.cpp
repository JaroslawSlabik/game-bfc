#include "gui_frame_login.h"

#include <QApplication>

#include "gui_frame_manager.h"
#include "../logic_controler_lib/global_struct/player_info.h"

GUIFrameLogin::GUIFrameLogin(QWidget *parent)
{
    Q_UNUSED(parent);
}

GUIFrameLogin::~GUIFrameLogin()
{

}

void GUIFrameLogin::initialize()
{
    text_render_part1 = new OpenGLTextRender2D;
    text_render_part1->setFontName("Arial.ttf");
    text_render_part1->setFontSize(36);
    text_render_part1->setColorText(QColor(255,255,255));
    text_render_part1->setTextRender("The branch of the");
    text_render_part1->setPosition(QVector2D(100,150));

    text_render_part2 = new OpenGLTextRender2D;
    text_render_part2->setFontName("Arial.ttf");
    text_render_part2->setFontSize(36);
    text_render_part2->setColorText(QColor(255,255,255));
    text_render_part2->setTextRender("fighting creatures");
    text_render_part2->setPosition(QVector2D(100,200));

    m_login_textbox = new TextBox;
    m_login_textbox->setPosition(150, 300);
    m_login_textbox->setScale(300, 0);
    m_login_textbox->setColorText(QColor(0,0,255));
    m_login_textbox->setBaseColor(QColor(0,250,0));
    m_login_textbox->setColorClicked(QColor(100,100,100));
    m_login_textbox->setColorMoveOn(QColor(140,255,140));
    m_login_textbox->setFont("Arial.ttf", 20);
    m_login_textbox->setMaxLenght(50);
    m_login_textbox->setColorLabel(QColor(255,255,255));
    m_login_textbox->setTextLabel("Login:", QVector2D(-75, 22));

    m_password_textbox = new TextBox;
    m_password_textbox->setPosition(150, 350);
    m_password_textbox->setScale(300, 0);
    m_password_textbox->setColorText(QColor(0,0,255));
    m_password_textbox->setBaseColor(QColor(0,250,0));
    m_password_textbox->setColorClicked(QColor(100,100,100));
    m_password_textbox->setColorMoveOn(QColor(140,255,140));
    m_password_textbox->setMaskChar('*');
    m_password_textbox->setFont("Arial.ttf", 20);
    m_password_textbox->setMaxLenght(50);
    m_password_textbox->setColorLabel(QColor(255,255,255));
    m_password_textbox->setTextLabel("Password:", QVector2D(-130, 22));

    m_login_button = new Button;
    m_login_button->setPosition(350, 400);
    m_login_button->setScale(100, 30);
    m_login_button->setColorText(QColor(255,0,255));
    m_login_button->setBaseColor(QColor(0,0,255));
    m_login_button->setColorClicked(QColor(100,100,100));
    m_login_button->setColorMoveOn(QColor(140,255,140));
    m_login_button->setFont("Arial.ttf", 20);
    m_login_button->setText("Login", QVector2D(20, 22));

    m_registration_button = new Button;
    m_registration_button->setPosition(100, 400);
    m_registration_button->setScale(200, 30);
    m_registration_button->setColorText(QColor(255,0,255));
    m_registration_button->setBaseColor(QColor(0,0,255));
    m_registration_button->setColorClicked(QColor(100,100,100));
    m_registration_button->setColorMoveOn(QColor(140,255,140));
    m_registration_button->setFont("Arial.ttf", 20);
    m_registration_button->setText("Rejestracja", QVector2D(20, 22));

    m_message = new OpenGLTextRender2D;
    m_message->setFontName("Arial.ttf");
    m_message->setFontSize(20);
    m_message->setColorText(QColor(255,0,0));
    m_message->setTextRender("");
    m_message->setPosition(QVector2D(100,250));
}

void GUIFrameLogin::deinitialize()
{
    if(text_render_part1)
        delete text_render_part1;

    if(text_render_part2)
        delete text_render_part2;

    if(m_login_textbox)
        delete m_login_textbox;

    if(m_password_textbox)
        delete m_password_textbox;

    if(m_login_button)
        delete m_login_button;

    if(m_registration_button)
        delete m_registration_button;

    if(m_message)
        delete m_message;
}

void GUIFrameLogin::draw(Shader* shader)
{
    text_render_part1->draw(shader);
    text_render_part2->draw(shader);

    m_login_textbox->draw(shader);
    m_password_textbox->draw(shader);
    m_login_button->draw(shader);
    m_registration_button->draw(shader);
    m_message->draw(shader);
}

void GUIFrameLogin::timerEvent(QTimerEvent * timer_event)
{

}

void GUIFrameLogin::show()
{
    connect(m_login_button, &Button::clicked, this, &GUIFrameLogin::loginClicked);
    connect(m_registration_button, &Button::clicked, this, &GUIFrameLogin::registrationClicked);
}

void GUIFrameLogin::hide()
{
    disconnect(m_login_button, &Button::clicked, this, &GUIFrameLogin::loginClicked);
    disconnect(m_registration_button, &Button::clicked, this, &GUIFrameLogin::registrationClicked);
}

void GUIFrameLogin::receiveFromServer(const QString& response)
{
    if(args.setResponse(response))
    {
        qDebug() << __PRETTY_FUNCTION__ << " RESPONSE: " << response;
        bool was_ok = false;
        if(!args.getArg(LogInLogicArgs::ArgumentsResponse::WAS_OK, &was_ok).toBool())
        {
            m_message->setTextRender(args.getArg(LogInLogicArgs::ArgumentsResponse::MESSAGE, &was_ok).toString());
        }
        else
        {
            clear();
            PlayerInfo::setIdPlayer(args.getArg(LogInLogicArgs::ArgumentsResponse::ID_GAMER).toLongLong());
            emit skipToFrame(GUIFrameManager::Frame::mainWindowFrame);
        }
    }
}

void GUIFrameLogin::kayboardEventRec(QEvent::Type type, Qt::Key key, QString text)
{
    m_login_textbox->kayboardEventRec(type, key, text);
    m_password_textbox->kayboardEventRec(type, key, text);
    m_login_button->kayboardEventRec(type, key, text);
    m_registration_button->kayboardEventRec(type, key, text);
}

void GUIFrameLogin::mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button)
{
    m_login_textbox->mouseEventRec(type, pos, button);
    m_password_textbox->mouseEventRec(type, pos, button);
    m_login_button->mouseEventRec(type, pos, button);
    m_registration_button->mouseEventRec(type, pos, button);
}

void GUIFrameLogin::loginClicked()
{
    QString login = m_login_textbox->getText();
    QString password = m_password_textbox->getText();

    args.setArg(LogInLogicArgs::ArgumentsQuery::LOGIN, login);
    args.setArg(LogInLogicArgs::ArgumentsQuery::PASSWORD, password);

    qDebug() << __PRETTY_FUNCTION__ << " QUERY: " << args.getQuery();
    emit sendToServer(args.getQuery());
}

void GUIFrameLogin::registrationClicked()
{
    clear();
    emit skipToFrame(GUIFrameManager::Frame::RegistrationFrame);
}

void GUIFrameLogin::clear()
{
    m_login_textbox->setText("");
    m_password_textbox->setText("");
    m_message->setTextRender("");
}
