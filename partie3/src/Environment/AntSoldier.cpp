#include "AntSoldier.hpp"
#include "../Utility/Utility.hpp"
#include "../Application.hpp"

//Constructeur

AntSoldier :: AntSoldier (ToricPosition position, Uid indicateur)
    : Ant (position, indicateur, getAppConfig().ant_soldier_hp, getAppConfig().ant_soldier_lifespan)
{}

//Methodes

void AntSoldier::drawOn(sf::RenderTarget& target) const
{
    drawOnAnt(target,getAppTexture(getAppConfig().ant_soldier_texture));
}

void AntSoldier::update(sf::Time dt)
{
    move(dt);
    spreadPheromones();
}
