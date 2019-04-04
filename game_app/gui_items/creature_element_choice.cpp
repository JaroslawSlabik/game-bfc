#include "creature_element_choice.h"
#include "../logic_controler_lib/global_struct/elements.h"
#include "../logic_controler_lib/global_struct/attributes.h"
#include "../graphic_lib/plate_mesh.h"

CreatureElementChoice::CreatureElementChoice()
{
    m_background = new OpenGLObject2D;
    m_background->setMesh(new PlateMesh);
    m_background->setBaseColor(QColor(0, 200,200));

    m_creature = new Creature;

    m_used_mask = new OpenGLObject2D;
    m_used_mask->setMesh(new PlateMesh);
    m_used_mask->setTexture(new Texture(QString(":/is_used.png")));

    m_element_icon = new ElementIcon(ElementType_e::earth, QVector2D(460, 100), QVector2D(40,40));

    m_earth_element = new Button;
    m_earth_element->setFont("Arial.ttf", 10);
    m_earth_element->setText(s_elementTypeHash.value(ElementType_e::earth));
    m_earth_element->setTextPosition(QVector2D(70, 20));
    m_earth_element->setBaseColor(QColor(0,0,130));
    m_earth_element->setColorText(QColor(255,255,255));
    m_earth_element->setColorMoveOn(QColor(0,0,190));
    m_earth_element->setColorClicked(QColor(0,0,255));

    m_water_element = new Button;
    m_water_element->setFont("Arial.ttf", 10);
    m_water_element->setText(s_elementTypeHash.value(ElementType_e::water));
    m_water_element->setTextPosition(QVector2D(70, 20));
    m_water_element->setBaseColor(QColor(0,0,130));
    m_water_element->setColorText(QColor(255,255,255));
    m_water_element->setColorMoveOn(QColor(0,0,190));
    m_water_element->setColorClicked(QColor(0,0,255));

    m_air_element = new Button;
    m_air_element->setFont("Arial.ttf", 10);
    m_air_element->setText(s_elementTypeHash.value(ElementType_e::air));
    m_air_element->setBaseColor(QColor(0,0,130));
    m_air_element->setColorText(QColor(255,255,255));
    m_air_element->setColorMoveOn(QColor(0,0,190));
    m_air_element->setColorClicked(QColor(0,0,255));

    m_fire_element = new Button;
    m_fire_element->setFont("Arial.ttf", 10);
    m_fire_element->setText(s_elementTypeHash.value(ElementType_e::fire));
    m_fire_element->setTextPosition(QVector2D(70, 20));
    m_fire_element->setBaseColor(QColor(0,0,130));
    m_fire_element->setColorText(QColor(255,255,255));
    m_fire_element->setColorMoveOn(QColor(0,0,190));
    m_fire_element->setColorClicked(QColor(0,0,255));

    m_name = new OpenGLTextRender2D;
    m_name->setFontName("Arial.ttf");
    m_name->setFontSize(20);
    m_name->setColorText(QColor(255,255,255));
    m_name->setTextRender("--");

    m_health_label = new OpenGLTextRender2D;
    m_health_label->setFontName("Arial.ttf");
    m_health_label->setFontSize(20);
    m_health_label->setColorText(QColor(255,255,255));
    m_health_label->setTextRender(s_attributeTypeHash.value(AttributeType_e::health));

    m_health_value = new OpenGLTextRender2D;
    m_health_value->setFontName("Arial.ttf");
    m_health_value->setFontSize(20);
    m_health_value->setColorText(QColor(255,255,255));
    m_health_value->setTextRender("--");

    m_shield_label = new OpenGLTextRender2D;
    m_shield_label->setFontName("Arial.ttf");
    m_shield_label->setFontSize(20);
    m_shield_label->setColorText(QColor(255,255,255));
    m_shield_label->setTextRender(s_attributeTypeHash.value(AttributeType_e::shield));

    m_shield_value = new OpenGLTextRender2D;
    m_shield_value->setFontName("Arial.ttf");
    m_shield_value->setFontSize(20);
    m_shield_value->setColorText(QColor(255,255,255));
    m_shield_value->setTextRender("--");

    m_attack_label = new OpenGLTextRender2D;
    m_attack_label->setFontName("Arial.ttf");
    m_attack_label->setFontSize(20);
    m_attack_label->setColorText(QColor(255,255,255));
    m_attack_label->setTextRender(s_attributeTypeHash.value(AttributeType_e::attack));

    m_attack_value = new OpenGLTextRender2D;
    m_attack_value->setFontName("Arial.ttf");
    m_attack_value->setFontSize(20);
    m_attack_value->setColorText(QColor(255,255,255));
    m_attack_value->setTextRender("--");

    m_move_label = new OpenGLTextRender2D;
    m_move_label->setFontName("Arial.ttf");
    m_move_label->setFontSize(20);
    m_move_label->setColorText(QColor(255,255,255));
    m_move_label->setTextRender(s_attributeTypeHash.value(AttributeType_e::move));

    m_move_value = new OpenGLTextRender2D;
    m_move_value->setFontName("Arial.ttf");
    m_move_value->setFontSize(20);
    m_move_value->setColorText(QColor(255,255,255));
    m_move_value->setTextRender("--");

    //connects:
    connect(m_earth_element, &Button::clicked, this, &CreatureElementChoice::buttonEarthElementClicked);
    connect(m_water_element, &Button::clicked, this, &CreatureElementChoice::buttonWaterElementClicked);
    connect(m_air_element, &Button::clicked, this, &CreatureElementChoice::buttonAirElementClicked);
    connect(m_fire_element, &Button::clicked, this, &CreatureElementChoice::buttonFireElementClicked);
}

CreatureElementChoice::~CreatureElementChoice()
{
    //disconnects:
    disconnect(m_earth_element, &Button::clicked, this, &CreatureElementChoice::buttonEarthElementClicked);
    disconnect(m_water_element, &Button::clicked, this, &CreatureElementChoice::buttonWaterElementClicked);
    disconnect(m_air_element, &Button::clicked, this, &CreatureElementChoice::buttonAirElementClicked);
    disconnect(m_fire_element, &Button::clicked, this, &CreatureElementChoice::buttonFireElementClicked);

    if(m_earth_element)
        delete m_earth_element;

    if(m_water_element)
        delete m_water_element;

    if(m_air_element)
        delete m_air_element;

    if(m_fire_element)
        delete m_fire_element;

    if(m_creature)
        delete m_creature;

    if(m_name)
        delete m_name;

    if(m_health_label)
        delete m_health_label;

    if(m_health_value)
        delete m_health_value;

    if(m_shield_label)
        delete m_shield_label;

    if(m_shield_value)
        delete m_shield_value;

    if(m_attack_label)
        delete m_attack_label;

    if(m_attack_value)
        delete m_attack_value;

    if(m_move_label)
        delete m_move_label;

    if(m_move_value)
        delete m_move_value;

    if(m_element_icon)
        delete m_element_icon;

    if(m_used_mask)
        delete m_used_mask;

}

void CreatureElementChoice::setPosition(const QVector2D& pos)
{
    m_position = pos;

    resize();
}

void CreatureElementChoice::setSize(const QVector2D& size)
{
    m_size = size;

    resize();
}

bool CreatureElementChoice::draw(Shader* shader)
{
    m_background->draw(shader);

    m_earth_element->draw(shader);
    m_water_element->draw(shader);
    m_air_element->draw(shader);
    m_fire_element->draw(shader);
    m_creature->draw(shader);
    m_name->draw(shader);
    m_health_label->draw(shader);
    m_health_value->draw(shader);
    m_shield_label->draw(shader);
    m_shield_value->draw(shader);
    m_attack_label->draw(shader);
    m_attack_value->draw(shader);
    m_move_label->draw(shader);
    m_move_value->draw(shader);
    m_element_icon->draw(shader);
    m_used_mask->draw(shader);

    return true;
}

void CreatureElementChoice::clear()
{

}

ElementType_e CreatureElementChoice::getChoiceElement()
{
    return m_element_icon->getElement();
}

void CreatureElementChoice::mouseEventRec(QEvent::Type type, QVector2D pos, Qt::MouseButton button)
{
    m_earth_element->mouseEventRec(type, pos, button);
    m_water_element->mouseEventRec(type, pos, button);
    m_air_element->mouseEventRec(type, pos, button);
    m_fire_element->mouseEventRec(type, pos, button);
}

void CreatureElementChoice::kayboardEventRec(QEvent::Type type, Qt::Key key, QString text)
{
    Q_UNUSED(type);
    Q_UNUSED(key);
    Q_UNUSED(text);
}

void CreatureElementChoice::receiveFromServer(const QString& response)
{
    Q_UNUSED(response);
}

void CreatureElementChoice::selectedCreature(CreatureInfo creature)
{
    m_used_mask->setVisible((creature.m_id < 1)? true : false);

    m_creature->setInfo(creature);

    m_name->setTextRender(creature.m_name);
    m_health_value->setTextRender(QString::number(creature.m_health));
    m_shield_value->setTextRender(QString::number(creature.m_shield));
    m_attack_value->setTextRender(QString::number(creature.m_attack));
    m_move_value->setTextRender(QString::number(creature.m_point_of_move));
}

void CreatureElementChoice::buttonEarthElementClicked()
{
    m_element_icon->setElement(ElementType_e::earth);
}

void CreatureElementChoice::buttonWaterElementClicked()
{
    m_element_icon->setElement(ElementType_e::water);
}

void CreatureElementChoice::buttonAirElementClicked()
{
    m_element_icon->setElement(ElementType_e::air);
}

void CreatureElementChoice::buttonFireElementClicked()
{
    m_element_icon->setElement(ElementType_e::fire);
}

void CreatureElementChoice::resize()
{
    m_background->setPosition(m_position.x(), m_position.y());
    m_background->setScale(m_size.x(), m_size.y());

    m_creature->setPosition(m_position.x(), m_position.y());
    m_creature->setScale(m_size.x() * 0.55f, m_size.x() * 0.55f);

    m_used_mask->setPosition(m_position.x(), m_position.y());
    m_used_mask->setScale(m_size.x() * 0.75f, m_size.x() * 0.75f);

    m_element_icon->setPosition(m_position.x() + m_creature->getPosition().x() - m_element_icon->getScale().x(), m_position.y());

    QVector2D labels_pos_start = QVector2D(m_position.x() + 20, m_position.y() + m_creature->getScale().y() + 10);

    m_name->setPosition(labels_pos_start);

    labels_pos_start.setY(labels_pos_start.y() + 30);
    m_health_label->setPosition(labels_pos_start);
    m_health_value->setPosition(labels_pos_start.x() + 105, labels_pos_start.y());

    labels_pos_start.setY(labels_pos_start.y() + 30);
    m_shield_label->setPosition(labels_pos_start);
    m_shield_value->setPosition(labels_pos_start.x() + 105, labels_pos_start.y());

    labels_pos_start.setY(labels_pos_start.y() + 30);
    m_attack_label->setPosition(labels_pos_start);
    m_attack_value->setPosition(labels_pos_start.x() + 105, labels_pos_start.y());

    labels_pos_start.setY(labels_pos_start.y() + 30);
    m_move_label->setPosition(labels_pos_start);
    m_move_value->setPosition(labels_pos_start.x() + 105, labels_pos_start.y());

    QVector2D buttons_pos_start = QVector2D(labels_pos_start.x(), labels_pos_start.y() + 20);

    m_earth_element->setPosition(buttons_pos_start.x(), buttons_pos_start.y());
    m_earth_element->setScale(120,40);
    m_earth_element->setTextPosition(QVector2D(50, 25));

    m_water_element->setPosition(buttons_pos_start.x() + 140, buttons_pos_start.y());
    m_water_element->setScale(120,40);
    m_water_element->setTextPosition(QVector2D(50, 25));

    m_air_element->setPosition(buttons_pos_start.x(), buttons_pos_start.y() + 60);
    m_air_element->setScale(120,40);
    m_air_element->setTextPosition(QVector2D(20, 25));

    m_fire_element->setPosition(buttons_pos_start.x() + 140, buttons_pos_start.y() + 60);
    m_fire_element->setScale(120,40);
    m_fire_element->setTextPosition(QVector2D(50, 25));
}
