#include "waiting_box.h"

#include "plate_mesh.h"
#include "../logic_controler_lib/global_struct/player_info.h"


WaitingBox::WaitingBox(QObject *parent)
{
    Q_UNUSED(parent);

    this->setMesh(new PlateMesh);
    this->setBaseColor(QColor(255, 0, 0));
    this->setScale(400,200);
    this->setPosition(200,200);

    m_info_text_label = new OpenGLTextRender2D;
    m_info_text_label->setFontName("Arial.ttf");
    m_info_text_label->setFontSize(20);
    m_info_text_label->setColorText(QColor(255,255,255));
    m_info_text_label->setTextRender("Czekaj, trwa inicjalizowanie rozrywki.");
    m_info_text_label->setPosition(210, 250);

    m_button_abort = new Button;
    m_button_abort->setPosition(450, 350);
    m_button_abort->setScale(140,40);
    m_button_abort->setFont("Arial.ttf", 10);
    m_button_abort->setText("Anuluj");
    m_button_abort->setTextPosition(QVector2D(70, 20));
    m_button_abort->setBaseColor(QColor(0,0,130));
    m_button_abort->setColorText(QColor(255,255,255));
    m_button_abort->setColorMoveOn(QColor(0,0,190));
    m_button_abort->setColorClicked(QColor(0,0,255));

    m_timer_waiting_info.setInterval(1000);

    m_waiting_info_args.setArg(GetWaitingInfoLogicArgs::ArgumentsQuery::ID_PLAYER, PlayerInfo::getIdPlayer());
    m_abort_waiting_args.setArg(SetAbortWaitingLogicArgs::ArgumentsQuery::ID_PLAYER, PlayerInfo::getIdPlayer());

    connect(m_button_abort, &Button::clicked, this, &WaitingBox::buttonAbortClicked);
    connect(&m_timer_waiting_info, &QTimer::timeout, this, &WaitingBox::sendRequestWaitingInfo);

    m_timer_waiting_info.start();

    this->setVisible(false);
}

WaitingBox::~WaitingBox()
{
    disconnect(m_button_abort, &Button::clicked, this, &WaitingBox::buttonAbortClicked);

    if(m_info_text_label)
        delete m_info_text_label;

    if(m_button_abort)
        delete m_button_abort;
}

bool WaitingBox::draw(Shader* shader)
{
    if(false == this->getVisible())
        return true;

    this->drawGL(shader);

    m_info_text_label->draw(shader);
    m_button_abort->draw(shader);

    return true;
}

void WaitingBox::mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button)
{
    if(false == this->getVisible())
        return;

    m_button_abort->mouseEventRec(type, pos, button);
}

void WaitingBox::kayboardEventRec(QEvent::Type type, Qt::Key key, QString text)
{
    Q_UNUSED(type);
    Q_UNUSED(key);
    Q_UNUSED(text);
}

void WaitingBox::receiveFromServer(const QString& response)
{
    if(true == m_waiting_info_args.setResponse(response))
    {
        qDebug() << __PRETTY_FUNCTION__ << " RESPONSE: " << response;
        m_info_text_label->setTextRender(m_waiting_info_args.getArg(GetWaitingInfoLogicArgs::ArgumentsResponse::MESSAGE).toString());
        int status = m_waiting_info_args.getArg(GetWaitingInfoLogicArgs::ArgumentsResponse::STATUS).toInt();
        if(4 == status)
        {
            QTimer::singleShot(4000, [&](){
                emit startGame();
                this->setVisible(false);
            });

        }
    }

    if(true == m_abort_waiting_args.setResponse(response))
    {
        qDebug() << __PRETTY_FUNCTION__ << " RESPONSE: " << response;
        m_info_text_label->setTextRender(m_waiting_info_args.getArg(SetAbortWaitingLogicArgs::ArgumentsResponse::MESSAGE).toString());
        int status = m_waiting_info_args.getArg(SetAbortWaitingLogicArgs::ArgumentsResponse::STATUS).toInt();
        if(3 == status)
        {
            QTimer::singleShot(4000, [&](){
                emit abortWaiting();
                this->setVisible(false);
            });
        }
    }
}

void WaitingBox::show()
{
    this->setVisible(true);
}

void WaitingBox::buttonAbortClicked()
{
    qDebug() << __PRETTY_FUNCTION__ << " QUERY: " << m_abort_waiting_args.getQuery();
    emit sendToServer(m_abort_waiting_args.getQuery());
}

void WaitingBox::sendRequestWaitingInfo()
{
    if(true == this->getVisible())
    {
        qDebug() << __PRETTY_FUNCTION__ << " QUERY: " << m_waiting_info_args.getQuery();
        emit sendToServer(m_waiting_info_args.getQuery());
    }
}
