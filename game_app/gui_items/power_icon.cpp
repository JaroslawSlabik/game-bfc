#include "power_icon.h"

ElementIcon::ElementIcon()
{
    initPowerTextureRect();
    bool was_ok = false;
    m_texture = new Texture();
    was_ok = m_texture->loadFromFile(QString(":/resources/elements.png"), false, false);
    this->setTexture(m_texture->getTexture());
    this->setMesh(new PlateMesh());

    setElement(ElementType_e::earth);
}

ElementIcon::ElementIcon(ElementType_e element, const QVector2D& pos, const QVector2D& size)
{
    initPowerTextureRect();
    bool was_ok = false;
    m_texture = new Texture();
    was_ok = m_texture->loadFromFile(QString(":/resources/elements.png"), false, false);


    this->setPosition(pos);
    this->setScale(size);
    this->setTexture(m_texture->getTexture());
    this->setMesh(new PlateMesh());

    setElement(element);
}

ElementIcon::~ElementIcon()
{
    if(m_texture)
        delete m_texture;
}

void ElementIcon::setElement(ElementType_e element)
{
    m_element = element;

    this->setTextureRect(powerTextureRect[m_element].x, powerTextureRect[m_element].y, powerTextureRect[m_element].width, powerTextureRect[m_element].height);
}

ElementType_e ElementIcon::getElement()
{
    return m_element;
}

void ElementIcon::initPowerTextureRect()
{
    powerTextureRect[ElementType_e::earth].x = 0;
    powerTextureRect[ElementType_e::earth].y = 0;
    powerTextureRect[ElementType_e::earth].width = 50;
    powerTextureRect[ElementType_e::earth].height = 50;

    powerTextureRect[ElementType_e::water].x = 50;
    powerTextureRect[ElementType_e::water].y = 0;
    powerTextureRect[ElementType_e::water].width = 50;
    powerTextureRect[ElementType_e::water].height = 50;

    powerTextureRect[ElementType_e::fire].x = 100;
    powerTextureRect[ElementType_e::fire].y = 0;
    powerTextureRect[ElementType_e::fire].width = 50;
    powerTextureRect[ElementType_e::fire].height = 50;

    powerTextureRect[ElementType_e::air].x = 150;
    powerTextureRect[ElementType_e::air].y = 0;
    powerTextureRect[ElementType_e::air].width = 50;
    powerTextureRect[ElementType_e::air].height = 50;
}
