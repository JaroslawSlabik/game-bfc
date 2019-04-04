#include "creature_attributes_view.h"

#include "../graphic_lib/plate_mesh.h"
#include "../graphic_lib/texture.h"
#include "../logic_controler_lib/global_struct/attributes.h"

#include <QDebug>

CreatureAttributesView::CreatureAttributesView()
{
    m_creature = new Creature();
    m_background = new OpenGLObject2D;
    m_background->setMesh(new PlateMesh);
    m_background->setBaseColor(QColor(0, 100, 100));

    m_titles_of_attributes = new OpenGLTextRender2D[AttributeType_e::AttributeTypeCount];
    for(int i = 0; i < AttributeType_e::AttributeTypeCount; ++i)
    {
        m_titles_of_attributes[i].setFontName("Arial.ttf");
        m_titles_of_attributes[i].setFontSize(20);
        m_titles_of_attributes[i].setColorText(QColor(255,255,255));
        m_titles_of_attributes[i].setTextRender(s_attributeTypeHash.value(static_cast<AttributeType_e>(i)));
    }

    Texture* texture_minus = new Texture(QString(":/resources/minus.png"));
    m_minus = new Button[AttributeType_e::AttributeTypeCount];
    for(int i = 0; i < AttributeType_e::AttributeTypeCount; ++i)
    {
        m_minus[i].setFont("Arial.ttf", 10);
        m_minus[i].setText("M");
        m_minus[i].setBaseColor(QColor(0,0,150));
        m_minus[i].setColorText(QColor(255,255,255));
        m_minus[i].setColorMoveOn(QColor(0,0,200));
        m_minus[i].setColorClicked(QColor(0,0,255));
        m_minus[i].setTexture(texture_minus);
    }

    m_points_of_attributes = new OpenGLTextRender2D[AttributeType_e::AttributeTypeCount];
    for(int i = 0; i < AttributeType_e::AttributeTypeCount; ++i)
    {
        m_points_of_attributes[i].setFontName("Arial.ttf");
        m_points_of_attributes[i].setFontSize(20);
        m_points_of_attributes[i].setColorText(QColor(255,255,255));
        m_points_of_attributes[i].setTextRender("--");
    }

    Texture* texture_plus = new Texture(QString(":/resources/plus.png"));
    m_plus = new Button[AttributeType_e::AttributeTypeCount];
    for(int i = 0; i < AttributeType_e::AttributeTypeCount; ++i)
    {
        m_plus[i].setFont("Arial.ttf", 10);
        m_plus[i].setText("P");
        m_plus[i].setBaseColor(QColor(130,0,0));
        m_plus[i].setColorText(QColor(255,255,255));
        m_plus[i].setColorMoveOn(QColor(190,0,0));
        m_plus[i].setColorClicked(QColor(255,0,0));
        m_plus[i].setTexture(texture_plus);
    }

    m_anuluj = new Button;
    m_anuluj->setFont("Arial.ttf", 20);
    m_anuluj->setText("Anuluj");
    m_anuluj->setBaseColor(QColor(0,130,0));
    m_anuluj->setColorText(QColor(255,255,255));
    m_anuluj->setColorMoveOn(QColor(0,190,0));
    m_anuluj->setColorClicked(QColor(0,255,0));

    m_save = new Button;
    m_save->setFont("Arial.ttf", 20);
    m_save->setText("Save");
    m_save->setBaseColor(QColor(0,130,0));
    m_save->setColorText(QColor(255,255,255));
    m_save->setColorMoveOn(QColor(0,190,0));
    m_save->setColorClicked(QColor(0,255,0));

    m_description = new OpenGLTextRender2D;
    m_description->setFontName("Arial.ttf");
    m_description->setFontSize(20);
    m_description->setColorText(QColor(255,255,255));
    m_description->setTextRender("--");

    m_name = new OpenGLTextRender2D;
    m_name->setFontName("Arial.ttf");
    m_name->setFontSize(20);
    m_name->setColorText(QColor(255,255,255));
    m_name->setTextRender("--");


    //connections:
    connect(m_anuluj, &Button::clicked, this, &CreatureAttributesView::button_anuluj_clicked);
    connect(m_save, &Button::clicked, this, &CreatureAttributesView::button_save_clicked);
    for(int i = 0; i < AttributeType_e::AttributeTypeCount; ++i)
    {
        connect(&m_minus[i], &Button::clicked,[=](){
            button_minus_clicked(i);
        });

        connect(&m_plus[i], &Button::clicked,[=](){
            button_plus_clicked(i);
        });
    }
}

CreatureAttributesView::~CreatureAttributesView()
{
    disconnect(m_anuluj, &Button::clicked, this, &CreatureAttributesView::button_anuluj_clicked);
    disconnect(m_save, &Button::clicked, this, &CreatureAttributesView::button_save_clicked);

    for(int i = 0; i < AttributeType_e::AttributeTypeCount; ++i)
    {
        disconnect(&m_minus[i], &Button::clicked, nullptr, nullptr);
        disconnect(&m_plus[i], &Button::clicked, nullptr, nullptr);
    }

    delete m_name;
    delete m_description;
    delete m_save;
    delete m_anuluj;
    delete[] m_plus;
    delete[] m_minus;
    delete[] m_titles_of_attributes;
    delete m_creature;
    delete m_background;
}

void CreatureAttributesView::setPosition(const QVector2D& pos)
{
    m_position = pos;

    resize();
}

void CreatureAttributesView::setSize(const QVector2D& size)
{
    m_size = size;

    resize();
}

bool CreatureAttributesView::draw(Shader* shader)
{
    m_background->draw(shader);

    m_anuluj->draw(shader);
    m_save->draw(shader);
    m_creature->draw(shader);

    for(int i = 0; i < AttributeType_e::AttributeTypeCount; ++i)
    {
        m_plus[i].draw(shader);
        m_minus[i].draw(shader);
        m_titles_of_attributes[i].draw(shader);
        m_points_of_attributes[i].draw(shader);
    }

    m_name->draw(shader);
    m_description->draw(shader);

    return true;
}

void CreatureAttributesView::clear()
{

}

void CreatureAttributesView::mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button)
{
    m_anuluj->mouseEventRec(type, pos, button);
    m_save->mouseEventRec(type, pos, button);
    for(int i = 0; i < AttributeType_e::AttributeTypeCount; ++i)
    {
        m_minus[i].mouseEventRec(type, pos, button);
        m_plus[i].mouseEventRec(type, pos, button);
    }
}

void CreatureAttributesView::kayboardEventRec(QEvent::Type type, Qt::Key key, QString text)
{
    Q_UNUSED(type);
    Q_UNUSED(key);
    Q_UNUSED(text);
}

void CreatureAttributesView::receiveFromServer(const QString& response)
{
    if(!args.setResponse(response))
    {//bad
        //TODO: wyswietlić gdzieś kominikat
        button_anuluj_clicked();
        return;
    }

    if(!args.getArg(SetCreatureAttributesLogicArgs::ArgumentsResponse::WAS_OK).toBool())
    {//bad
        //TODO: wyswietlić gdzieś kominikat
        qDebug() << __PRETTY_FUNCTION__ << ": " << args.getArg(SetCreatureAttributesLogicArgs::ArgumentsResponse::MESSAGE).toString();
        button_anuluj_clicked();
        return;
    }

    //good
    m_creature->setInfo(m_creature_info_modification);
}

void CreatureAttributesView::selectedCreature(CreatureInfo creature)
{
    emit anulujClicked();

    m_creature_info_modification = creature;
    m_creature->setInfo(creature);

    setAttributesToShow(m_creature_info_modification);

    m_name->setTextRender(creature.m_name);

    m_description->setTextRender(creature.m_description);
}

void CreatureAttributesView::existPoints(bool exist)
{
    m_exist_points_to_distribution = exist;

    m_anuluj->setVisible(false);
    m_save->setVisible(false);

    //jesli istnieja jeszcze punkty do rozdania to pokaż wszystkie przyciski do ich dodawania do atrybutów
    for(int i = 0; i < AttributeType_e::AttributeTypeCount; ++i)
    {
        m_plus[i].setVisible(m_exist_points_to_distribution);
    }

    bool istnieje_roznica = false;

    //pokazuj przyciski do odejmowania atrybutów tylko wtedy kiedy istnieje różnica tych atrybutów
    if(m_creature->getInfo().m_health == m_creature_info_modification.m_health)
    {
        m_minus[AttributeType_e::health].setVisible(false);
    }
    else
    {
        m_minus[AttributeType_e::health].setVisible(true);
        istnieje_roznica = true;
    }

    if(m_creature->getInfo().m_shield == m_creature_info_modification.m_shield)
    {
        m_minus[AttributeType_e::shield].setVisible(false);
    }
    else
    {
        m_minus[AttributeType_e::shield].setVisible(true);
        istnieje_roznica = true;
    }

    if(m_creature->getInfo().m_attack == m_creature_info_modification.m_attack)
    {
        m_minus[AttributeType_e::attack].setVisible(false);
    }
    else
    {
        m_minus[AttributeType_e::attack].setVisible(true);
        istnieje_roznica = true;
    }

    if(m_creature->getInfo().m_point_of_move == m_creature_info_modification.m_point_of_move)
    {
        m_minus[AttributeType_e::move].setVisible(false);
    }
    else
    {
        m_minus[AttributeType_e::move].setVisible(true);
        istnieje_roznica = true;
    }

    //pokazuj przyciski do zapisu i anulacji tylko wtedy kiedy sa różnice w punktach
    if(istnieje_roznica)
    {
        m_anuluj->setVisible(true);
        m_save->setVisible(true);
    }
}

void CreatureAttributesView::button_minus_clicked(int attribute_id)
{
    switch(static_cast<AttributeType_e>(attribute_id))
    {
        case AttributeType_e::health:
            m_creature_info_modification.m_health = m_creature_info_modification.m_health - 1;
            break;
        case AttributeType_e::shield:
            m_creature_info_modification.m_shield = m_creature_info_modification.m_shield - 1;
        break;
        case AttributeType_e::attack:
            m_creature_info_modification.m_attack = m_creature_info_modification.m_attack - 1;
        break;
        case AttributeType_e::move:
            m_creature_info_modification.m_point_of_move = m_creature_info_modification.m_point_of_move - 1;
        break;
        default:
        break;
    }

    setAttributesToShow(m_creature_info_modification);

    emit minusClicked();
}

void CreatureAttributesView::button_plus_clicked(int attribute_id)
{
    switch(static_cast<AttributeType_e>(attribute_id))
    {
        case AttributeType_e::health:
            m_creature_info_modification.m_health = m_creature_info_modification.m_health + 1;
            break;
        case AttributeType_e::shield:
            m_creature_info_modification.m_shield = m_creature_info_modification.m_shield + 1;
        break;
        case AttributeType_e::attack:
            m_creature_info_modification.m_attack = m_creature_info_modification.m_attack + 1;
        break;
        case AttributeType_e::move:
            m_creature_info_modification.m_point_of_move = m_creature_info_modification.m_point_of_move + 1;
        break;
        default:
        break;
    }

    setAttributesToShow(m_creature_info_modification);

    emit plusClicked();
}

void CreatureAttributesView::button_anuluj_clicked()
{
    qDebug() << __PRETTY_FUNCTION__;

    m_creature_info_modification = m_creature->getInfo();

    setAttributesToShow(m_creature_info_modification);

    emit anulujClicked();
}

void CreatureAttributesView::button_save_clicked()
{
    qDebug() << __PRETTY_FUNCTION__;

    emit saveClicked(m_creature_info_modification);

    m_creature->setInfo(m_creature_info_modification);

    args.setArg(SetCreatureAttributesLogicArgs::ArgumentsQuery::HEALTHS, m_creature_info_modification.m_health);
    args.setArg(SetCreatureAttributesLogicArgs::ArgumentsQuery::SHIELDS, m_creature_info_modification.m_shield);
    args.setArg(SetCreatureAttributesLogicArgs::ArgumentsQuery::ATTACKS, m_creature_info_modification.m_attack);
    args.setArg(SetCreatureAttributesLogicArgs::ArgumentsQuery::POINTS_OF_MOVE, m_creature_info_modification.m_point_of_move);
    args.setArg(SetCreatureAttributesLogicArgs::ArgumentsQuery::ID_CREATURE, m_creature_info_modification.m_id);

    emit sendToServer(args.getQuery());
}

void CreatureAttributesView::inicjalize()
{

}

void CreatureAttributesView::setAttributesToShow(CreatureInfo creature)
{
    m_points_of_attributes[AttributeType_e::health].setTextRender(QString::number(creature.m_health));
    m_points_of_attributes[AttributeType_e::shield].setTextRender(QString::number(creature.m_shield));
    m_points_of_attributes[AttributeType_e::attack].setTextRender(QString::number(creature.m_attack));
    m_points_of_attributes[AttributeType_e::move].setTextRender(QString::number(creature.m_point_of_move));
}

void CreatureAttributesView::resize()
{
    m_background->setPosition(m_position);
    m_background->setScale(m_size);

    m_creature->setPosition(m_position.x() + 10, m_position.y() + 10);
    m_creature->setScale(m_size.x() * 0.5f, m_size.y() * 0.75f);

    float poz_x = m_creature->getPosition().x() + m_creature->getScale().x() + 10;
    float poz_y = m_creature->getPosition().y() + 20;

    for(int i = 0; i < AttributeType_e::AttributeTypeCount; ++i)
    {
        m_titles_of_attributes[i].setPosition(poz_x, poz_y);
        poz_y += 30.0f;
    }

    m_anuluj->setPosition(poz_x, poz_y + 20);
    m_anuluj->setScale(100, 30);
    m_anuluj->setText("Anuluj", QVector2D(10, 22));

    m_save->setPosition(m_position.x() + m_size.x() - 110.f, poz_y + 20);
    m_save->setScale(100, 30);
    m_save->setText("Zapisz", QVector2D(10, 22));

    m_name->setPosition(m_creature->getPosition().x(), m_creature->getPosition().y() + m_creature->getScale().y() + 10);

    m_description->setPosition(m_creature->getPosition().x(), m_creature->getPosition().y() + m_creature->getScale().y() + 40);

    int size_button = 20;

    poz_x = m_position.x() + m_size.x() - (size_button + 10);
    poz_y = m_creature->getPosition().y();
    for(int i = 0; i < AttributeType_e::AttributeTypeCount; ++i)
    {
        m_plus[i].setPosition(poz_x, poz_y);
        m_plus[i].setScale(size_button, size_button);
        poz_y += 30.0f;
    }

    poz_x = m_position.x() + m_size.x() - ((size_button * 2) + 25);
    poz_y = m_creature->getPosition().y() + 20;
    for(int i = 0; i < AttributeType_e::AttributeTypeCount; ++i)
    {
        m_points_of_attributes[i].setPosition(poz_x, poz_y);
        poz_y += 30.0f;
    }

    poz_x = m_position.x() + m_size.x() - ((size_button * 3) + 30);
    poz_y = m_creature->getPosition().y();
    for(int i = 0; i < AttributeType_e::AttributeTypeCount; ++i)
    {
        m_minus[i].setPosition(poz_x, poz_y);
        m_minus[i].setScale(size_button, size_button);
        poz_y += 30.0f;
    }
}
