#include "AntWorker.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"

AntWorker::AntWorker(ToricPosition position, Uid id)
    : Ant (position, id, getAppConfig().ant_soldier_hp, getAppConfig().ant_soldier_lifespan ), carryingQuantity(0.0)
{
    getAppEnv().incrementCounters(antWorker);
}

AntWorker::~AntWorker()
{
    getAppEnv().decrementCounters(antWorker);
}

void AntWorker::drawOn(sf::RenderTarget& target) const
{
    drawOnAnt(target,getAppTexture(getAppConfig().ant_worker_texture));

    if(isDebugOn()) {
        Vec2d d1 = {0,50} ;
        auto const text = buildText( to_nice_string(carryingQuantity), getPosition().toVec2d() +  d1, getAppFont(), 15, sf::Color::Black);
        target.draw(text);
    }
}

void AntWorker::update(sf::Time dt)
{
    Animal* closestEnemy = getAppEnv().getClosestEnemy(this);
    setTimer_fight(getTimer_fight()+dt);

    switch(getAttitude()) {
    case Attack:
        if(getTimer_fight().asSeconds() > getAppConfig().ant_attack_delay) {
            setAttitude(Idle);
        }
        break;

    case Idle:
        move(dt);
        spreadPheromones();
        if (carryingQuantity==0) {
            Food* closestFood = getAppEnv().getClosestFoodForAnt(getPosition());

            if(closestFood != nullptr) {
                carryingQuantity = closestFood->takeQuantity(getAppConfig().ant_max_food);
                setDirectionUTurn();
            }
        } else {
            Anthill* anthill = getAppEnv().getAnthillfromUid(getAssociatedAnthill());

            if(anthill != nullptr) {
                if(toricDistance (anthill->getPosition(), getPosition()) < getAppConfig().ant_max_perception_distance) {
                    anthill->addFoodStock(carryingQuantity);
                    carryingQuantity = 0;
                    setDirectionUTurn();
                }
            }
        }
        if(closestEnemy != nullptr && getTimer_fight().asSeconds() > getAppConfig().ant_attack_delay) {
            setAttitude(Attack);
            setTimer_fight(sf::Time::Zero);
        }
        break;
    }
}