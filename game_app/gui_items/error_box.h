#ifndef ERROR_BOX_H
#define ERROR_BOX_H
#include <QObject>
#include <QEvent>
#include "opengl_object_2d.h"
#include "opengl_text_render_2d.h"
#include "i_gui_item.h"
#include "button.h"

class ErrorBox : public I_GUIItem, public OpenGLObject2D
{
    Q_OBJECT

public:
    explicit ErrorBox(QObject *parent = 0) ;
    ~ErrorBox();

    virtual bool draw(Shader* shader) override;

    void setText(const QString& text);

public slots:
    virtual void mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button) override;
    virtual void kayboardEventRec(QEvent::Type type, Qt::Key key, QString text) override;
    virtual void receiveFromServer(const QString& response) override;

signals:
    void clickedButtonOk();

private:
    OpenGLTextRender2D* m_error_text_label = nullptr;
    Button* m_button_ok = nullptr;

private slots:
    void buttonOkClicked();

};

#endif // ERROR_BOX_H
