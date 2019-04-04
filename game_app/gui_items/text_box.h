#ifndef TEXT_BOX_H
#define TEXT_BOX_H
#include <QObject>
#include <QEvent>
#include "opengl_object_2d.h"
#include "opengl_text_render_2d.h"
#include "i_gui_item.h"

class TextBox : public I_GUIItem, public OpenGLObject2D
{
public:
    explicit TextBox(QObject* parent = 0);

    void setColorClicked(const QColor& color);
    void setColorMoveOn(const QColor& color);
    void setText(const QString& text);
    bool setFont(const QString& font_name, int size);
    void setColorText(const QColor& color);
    void setMaskChar(const QChar& char_mask);
    void setMaxLenght(int lenght);
    void setColorLabel(const QColor& color);
    void setTextLabel(const QString& text, const QVector2D& pos = QVector2D(20, 22));
    void setTextPositionLabel(const QVector2D& pos);

    QString getText();

    virtual bool draw(Shader* shader) override;

public slots:
    virtual void mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button) override;
    virtual void kayboardEventRec(QEvent::Type type, Qt::Key key, QString text) override;

signals:
    void changed();
    void moveOn();

private:
    QColor m_color_clicked;
    QColor m_color_moved_on;
    QColor m_color_base = QColor();
    QString m_text;
    OpenGLTextRender2D* m_text_render;
    OpenGLTextRender2D* m_text_label;
    bool m_focus;
    bool m_mouse_on_object;
    int m_max_lenght;
    int m_size_top_in_pixels;
    int m_size_bottom_in_pixels;
    QChar m_char_mask;

    virtual void receiveFromServer(const QString& response) override {}

    Q_OBJECT
};

#endif // TEXT_BOX_H
