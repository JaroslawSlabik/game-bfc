#include "creature.h"

#include "plate_mesh.h"

Creature::Creature()
{
    this->setMesh(new PlateMesh);
}

Creature::Creature(const CreatureInfo& info)
{
    m_info = info;

    this->setMesh(new PlateMesh);
    m_texture = new Texture(m_info.m_texture);
    this->setTexture(m_texture->getTexture());
}

Creature::~Creature()
{
    if(m_texture)
        delete m_texture;
}

CreatureInfo Creature::getInfo()
{
    return m_info;
}

void Creature::setInfo(const CreatureInfo& info)
{
    m_info = info;

    if(m_texture)
        delete m_texture;

    m_texture = new Texture(m_info.m_texture);
    this->setTexture(m_texture->getTexture());
}

bool Creature::draw(Shader* shader)
{
    return this->drawGL(shader);
}
