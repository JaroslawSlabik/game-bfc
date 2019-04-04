#include "gui_frame_registration.h"

#include <QApplication>
#include "gui_frame_manager.h"

GUIFrameRegistration::GUIFrameRegistration(QWidget *parent)
{

}

GUIFrameRegistration::~GUIFrameRegistration()
{

}

void GUIFrameRegistration::initialize()
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

    m_name_textbox = new TextBox;
    m_name_textbox->setPosition(150, 300);
    m_name_textbox->setScale(300, 0);
    m_name_textbox->setColorText(QColor(0,0,255));
    m_name_textbox->setBaseColor(QColor(0,250,0));
    m_name_textbox->setColorClicked(QColor(100,100,100));
    m_name_textbox->setColorMoveOn(QColor(140,255,140));
    m_name_textbox->setFont("Arial.ttf", 20);
    m_name_textbox->setMaxLenght(50);
    m_name_textbox->setColorLabel(QColor(255,255,255));
    m_name_textbox->setTextLabel("Imię:", QVector2D(-65, 22));

    m_surname_textbox = new TextBox;
    m_surname_textbox->setPosition(150, 350);
    m_surname_textbox->setScale(300, 0);
    m_surname_textbox->setColorText(QColor(0,0,255));
    m_surname_textbox->setBaseColor(QColor(0,250,0));
    m_surname_textbox->setColorClicked(QColor(100,100,100));
    m_surname_textbox->setColorMoveOn(QColor(140,255,140));
    m_surname_textbox->setFont("Arial.ttf", 20);
    m_surname_textbox->setMaxLenght(50);
    m_surname_textbox->setColorLabel(QColor(255,255,255));
    m_surname_textbox->setTextLabel("Nazwisko:", QVector2D(-130, 22));

    m_email_textbox = new TextBox;
    m_email_textbox = new TextBox;
    m_email_textbox->setPosition(150, 400);
    m_email_textbox->setScale(300, 0);
    m_email_textbox->setColorText(QColor(0,0,255));
    m_email_textbox->setBaseColor(QColor(0,250,0));
    m_email_textbox->setColorClicked(QColor(100,100,100));
    m_email_textbox->setColorMoveOn(QColor(140,255,140));
    m_email_textbox->setFont("Arial.ttf", 20);
    m_email_textbox->setMaxLenght(50);
    m_email_textbox->setColorLabel(QColor(255,255,255));
    m_email_textbox->setTextLabel("E-mail:", QVector2D(-100, 22));

    m_password_textbox = new TextBox;
    m_password_textbox->setPosition(150, 450);
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

    m_registration_button = new Button;
    m_registration_button->setPosition(300, 500);
    m_registration_button->setScale(180, 30);
    m_registration_button->setColorText(QColor(255,0,255));
    m_registration_button->setBaseColor(QColor(0,0,255));
    m_registration_button->setColorClicked(QColor(100,100,100));
    m_registration_button->setColorMoveOn(QColor(140,255,140));
    m_registration_button->setFont("Arial.ttf", 20);
    m_registration_button->setText("Rejestracja", QVector2D(20, 22));

    m_back_button = new Button;
    m_back_button->setPosition(100, 500);
    m_back_button->setScale(120, 30);
    m_back_button->setColorText(QColor(255,0,255));
    m_back_button->setBaseColor(QColor(0,0,255));
    m_back_button->setColorClicked(QColor(100,100,100));
    m_back_button->setColorMoveOn(QColor(140,255,140));
    m_back_button->setFont("Arial.ttf", 20);
    m_back_button->setText("Powrót", QVector2D(20, 22));

    m_message = new OpenGLTextRender2D;
    m_message->setFontName("Arial.ttf");
    m_message->setFontSize(20);
    m_message->setColorText(QColor(255,0,0));
    m_message->setTextRender("");
    m_message->setPosition(QVector2D(100,250));
}

void GUIFrameRegistration::deinitialize()
{
    if(text_render_part1)
        delete text_render_part1;

    if(text_render_part2)
        delete text_render_part2;

    if(m_name_textbox)
        delete m_name_textbox;

    if(m_surname_textbox)
        delete m_surname_textbox;

    if(m_email_textbox)
        delete m_email_textbox;

    if(m_password_textbox)
        delete m_password_textbox;

    if(m_back_button)
        delete m_back_button;

    if(m_registration_button)
        delete m_registration_button;

    if(m_message)
        delete m_message;
}

void GUIFrameRegistration::draw(Shader* shader)
{
    text_render_part1->draw(shader);
    text_render_part2->draw(shader);

    m_name_textbox->draw(shader);
    m_surname_textbox->draw(shader);
    m_email_textbox->draw(shader);
    m_password_textbox->draw(shader);
    m_registration_button->draw(shader);
    m_back_button->draw(shader);
    m_message->draw(shader);
}

void GUIFrameRegistration::timerEvent(QTimerEvent * timer_event)
{

}

void GUIFrameRegistration::show()
{
    connect(m_registration_button, &Button::clicked, this, &GUIFrameRegistration::registrationClicked);
    connect(m_back_button, &Button::clicked, this, &GUIFrameRegistration::backClicked);
}

void GUIFrameRegistration::hide()
{
    disconnect(m_registration_button, &Button::clicked, this, &GUIFrameRegistration::registrationClicked);
    disconnect(m_back_button, &Button::clicked, this, &GUIFrameRegistration::backClicked);
}

void GUIFrameRegistration::receiveFromServer(const QString& response)
{
    if(args.setResponse(response))
    {
        qDebug() << __PRETTY_FUNCTION__ << " RESPONSE: " << response;
        bool was_ok = false;
        if(false == args.getArg(RegistrationPlayerLogicArgs::ArgumentsResponse::WAS_OK, &was_ok).toBool())
        {
            m_message->setTextRender(args.getArg(RegistrationPlayerLogicArgs::ArgumentsResponse::MESSAGE, &was_ok).toString());
            m_password_textbox->setText("");
        }
        else
        {
            clear();
            emit skipToFrame(GUIFrameManager::Frame::loginFrame);
        }
    }
}

void GUIFrameRegistration::kayboardEventRec(QEvent::Type type, Qt::Key key, QString text)
{
    m_name_textbox->kayboardEventRec(type, key, text);
    m_surname_textbox->kayboardEventRec(type, key, text);
    m_email_textbox->kayboardEventRec(type, key, text);
    m_password_textbox->kayboardEventRec(type, key, text);
    m_registration_button->kayboardEventRec(type, key, text);
    m_back_button->kayboardEventRec(type, key, text);
}

void GUIFrameRegistration::mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button)
{
    m_name_textbox->mouseEventRec(type, pos, button);
    m_surname_textbox->mouseEventRec(type, pos, button);
    m_email_textbox->mouseEventRec(type, pos, button);
    m_password_textbox->mouseEventRec(type, pos, button);
    m_registration_button->mouseEventRec(type, pos, button);
    m_back_button->mouseEventRec(type, pos, button);
}

void GUIFrameRegistration::registrationClicked()
{
    QString name = m_name_textbox->getText();
    QString surname = m_surname_textbox->getText();
    QString email = m_email_textbox->getText();
    QString password = m_password_textbox->getText();

    args.setArg(RegistrationPlayerLogicArgs::ArgumentsQuery::NAME, name);
    args.setArg(RegistrationPlayerLogicArgs::ArgumentsQuery::SURNAME, surname);
    args.setArg(RegistrationPlayerLogicArgs::ArgumentsQuery::EMAIL, email);
    args.setArg(RegistrationPlayerLogicArgs::ArgumentsQuery::PASSWORD, password);

    qDebug() << __PRETTY_FUNCTION__ << " QUERY: " << args.getQuery();
    emit sendToServer(args.getQuery());
}

void GUIFrameRegistration::backClicked()
{
    clear();
    emit skipToFrame(GUIFrameManager::Frame::loginFrame);
}

void GUIFrameRegistration::clear()
{
    m_name_textbox->setText("");
    m_surname_textbox->setText("");
    m_email_textbox->setText("");
    m_password_textbox->setText("");
    m_message->setTextRender("");
}
