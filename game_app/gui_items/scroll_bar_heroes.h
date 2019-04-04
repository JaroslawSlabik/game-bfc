#ifndef SCROLL_BAR_HEROES_H
#define SCROLL_BAR_HEROES_H

#include <QString>
#include <QByteArray>
#include <QObject>
#include <QEvent>

#include "i_gui_item.h"
#include "shader.h"


#include "hero.h"

class ScrollBarHeroes : public I_GUIItem, public OpenGLObject2D
{
public:
    explicit ScrollBarHeroes(QObject *parent = 0) ;
    explicit ScrollBarHeroes(const QVector2D& pos, const QVector2D& size, const QList<Hero::HeroInfo>& list_of_heroes = QList<Hero::HeroInfo>(), QObject *parent = 0);
    ~ScrollBarHeroes();

    void setHeroesList(const QList<Hero::HeroInfo>& list_of_heroes);
    void setPosition(const QVector2D& pos);
    void setSize(const QVector2D& size);
    bool setSizeItem(const QVector2D& size_selected, const QVector2D& size_unselected);

    virtual bool draw(Shader* shader) override;

public slots:
    virtual void mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button) override;
    virtual void kayboardEventRec(QEvent::Type type, Qt::Key key, QString text) override {}
    virtual void receiveFromServer(const QString& response) override;
signals:
    void selectedHeroId(unsigned int id);

private:
    const float m_size_button_y = 20.0f;
    unsigned int m_selected_index = 0;
    void init();
    void select_next();
    void select_back();
    void set_texture();

    QList<Hero::HeroInfo> m_heroes_info_list;

    Hero* m_back;
    Hero* m_selected;
    Hero* m_next;

    OpenGLObject2D* m_button_back;
    OpenGLObject2D* m_body;
    OpenGLObject2D* m_button_next;

    bool m_draw_next = true;
    bool m_draw_back = false;

    Q_OBJECT
};

#endif // SCROLL_BAR_HEROES_H
