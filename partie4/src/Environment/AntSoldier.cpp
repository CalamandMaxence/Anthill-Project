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
    Animal* closestEnemy = getAppEnv().getClosestEnemy(this);

    switch(getAttitude()) {
    case Attack:
        if(closestEnemy != nullptr) attack(closestEnemy,getAppConfig().ant_soldier_strength);
        setTimer_fight(getTimer_fight()+dt);
        if(getTimer_fight().asSeconds() > getAppConfig().ant_attack_delay) {
            setAttitude(Idle);
            setTimer_fight(sf::Time::Zero);
        }
        break;

    case Idle:
        move(dt);
        spreadPheromones();
        if(closestEnemy != nullptr) {
            setAttitude(Attack);
        }
        break;
    }
}
