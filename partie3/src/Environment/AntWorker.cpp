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
    move(dt);
    spreadPheromones();

    if (quantiteTransportee==0) {
        ToricPosition pos = getPosition();
        Food* closestFood = getAppEnv().getClosestFoodForAnt(getPosition());
        if(closestFood != nullptr) {
            quantiteTransportee = closestFood->takeQuantity(getAppConfig().ant_max_food);
            setDirectionUturn();
        }
    } else {
        Anthill* anthill = getAnthillfromUid(getAssociatedAnthill());

        if(anthill != nullptr) {
            if(toricDistance (anthill->getPosition(), getPosition()) < getAppConfig().ant_max_perception_distance) {
                anthill->addStockNourriture(quantiteTransportee);
                quantiteTransportee = 0;
                setDirectionUturn();
            }
        }

    }
}