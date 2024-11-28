#include "AntWorker.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"

//Constructeur
AntWorker::AntWorker(ToricPosition position, Uid indicateur)
    : Ant (position, indicateur, getAppConfig().ant_soldier_hp, getAppConfig().ant_soldier_lifespan ), quantiteTransportee(0.0)
{}

//Methodes

void AntWorker::drawOn(sf::RenderTarget& target) const
{
    drawOnAnt(target,getAppTexture(getAppConfig().ant_worker_texture));

    if(isDebugOn()) {
        Vec2d d1 = {0,50} ;
        auto const text = buildText( to_nice_string(quantiteTransportee), getPosition().toVec2d() +  d1, getAppFont(), 15, sf::Color::Black);
        target.draw(text);


    }
}

void AntWorker::update(sf::Time dt)
{
    Animal* closestEnemy = getAppEnv().getClosestEnemy(this);

    switch(getAttitude()) {
    case Attack:
        setTimer_fight(getTimer_fight()+dt);
        if(getTimer_fight().asSeconds() > getAppConfig().ant_attack_delay) {
            setAttitude(Idle);
            setTimer_fight(sf::Time::Zero);
        }
        break;

    case Idle:
        move(dt);
        spreadPheromones();
        if (quantiteTransportee==0) {
            Food* closestFood = getAppEnv().getClosestFoodForAnt(getPosition());

            if(closestFood != nullptr) {
                quantiteTransportee = closestFood->takeQuantity(getAppConfig().ant_max_food);
                setDirectionDemiTour();
            }
        } else {
            Anthill* anthill = getAnthillfromUid(getfourmiliereAssociee());

            if(anthill != nullptr) {
                if(toricDistance (anthill->getPosition(), getPosition()) < getAppConfig().ant_max_perception_distance) {
                    anthill->addStockNourriture(quantiteTransportee);
                    quantiteTransportee = 0;
                    setDirectionDemiTour();
                }
            }
        }
        if(closestEnemy != nullptr) {
            setAttitude(Attack);
        }
        break;
    }
}