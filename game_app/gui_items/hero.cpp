#include "hero.h"

Hero::Hero()
{

}

Hero::HeroInfo Hero::getInfo()
{
    return m_hero_info;
}

void Hero::setInfo(const HeroInfo& info)
{
    m_hero_info = info;
}

void Hero::setInfo() //TODO: setInfo from DB
{

}
