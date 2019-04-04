#include "error_box.h"

#include "plate_mesh.h"

ErrorBox::ErrorBox(QObject *parent)
{
    Q_UNUSED(parent);

    this->setMesh(new PlateMesh);

    m_error_text_label = new OpenGLTextRender2D;

    m_button_ok = new Button;

    connect(m_button_ok, &Button::clicked, this, &ErrorBox::buttonOkClicked);
}

ErrorBox::~ErrorBox()
{
    disconnect(m_button_ok, &Button::clicked, this, &ErrorBox::buttonOkClicked);

    if(m_error_text_label)
        delete m_error_text_label;

    if(m_button_ok)
        delete m_button_ok;
}

bool ErrorBox::draw(Shader* shader)
{
    if(false == this->getVisible())
        return true;

    this->drawGL(shader);

    m_error_text_label->draw(shader);
    m_button_ok->draw(shader);

    return true;
}

void ErrorBox::setText(const QString& text)
{
    m_error_text_label->setTextRender(text);
}

void ErrorBox::mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button)
{
    if(false == this->getVisible())
        return;

    m_button_ok->mouseEventRec(type, pos, button);

    if(false == this->pointOnObject(pos) && QEvent::Type::MouseButtonRelease == type && Qt::MouseButton::LeftButton == button)
    {
        buttonOkClicked();
    }
}

void ErrorBox::kayboardEventRec(QEvent::Type type, Qt::Key key, QString text)
{
    Q_UNUSED(type);
    Q_UNUSED(key);
    Q_UNUSED(text);
}

void ErrorBox::receiveFromServer(const QString& response)
{
    Q_UNUSED(response);
}

void ErrorBox::buttonOkClicked()
{
    emit clickedButtonOk();

    this->setVisible(false);
}
