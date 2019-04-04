#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>
#include <QEvent>
#include "opengl_object_2d.h"
#include "opengl_text_render_2d.h"

class Button : public QObject, public OpenGLObject2D
{
public:
    explicit Button(QObject* parent = 0);

    void setColorClicked(const QColor& color);
    void setColorMoveOn(const QColor& color);
    void setText(const QString& text, const QVector2D& pos_txt = QVector2D(0,0));
    void setTextPosition(const QVector2D& pos_txt);
    void setColorText(const QColor& color);
    bool setFont(const QString& font_name, int size);

    QString getText();

    virtual bool draw(Shader* shader) override;

public slots:
    void mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button);
    void kayboardEventRec(QEvent::Type type, Qt::Key key, QString text);

signals:
    void clicked();
    void moveOn();

private:
    QColor m_color_clicked;
    QColor m_color_moved_on;
    QColor m_color_base = QColor();
    QString m_text;
    OpenGLTextRender2D* m_text_render;
    bool m_focus;
    bool m_mouse_on_object;

    Q_OBJECT
};

#endif // BUTTON_H
