#include "Anthill.hpp"
#include "Random/Random.hpp"
#include "../Application.hpp"

Anthill::Anthill (ToricPosition anthillPosition )
    : Positionable (anthillPosition),foodStock (0.0),id (createUid()),anthillTimer(sf::Time::Zero)
{
    generateAnt();
    getAppEnv().incrementCounters(anthill);
}

Anthill::~Anthill()
{
    getAppEnv().decrementCounters(anthill);
}

void Anthill::drawOn(sf::RenderTarget& target) const
{
    auto const anthillSprite = buildSprite(getPosition().toVec2d(), 75,getAppTexture(getAppConfig().anthill_texture));
    target.draw(anthillSprite);

    if(isDebugOn()) {
        Vec2d d1 = {0,50};
        Vec2d d2 = {0,70};
        auto const text1 = buildText( to_nice_string(this->foodStock), getPosition().toVec2d() + d1, getAppFont(), 15, sf::Color::Black);
        target.draw(text1);
        auto const text2 = buildText( to_nice_string(this->id), getPosition().toVec2d() + d2, getAppFont(), 15, sf::Color::Magenta);
        target.draw(text2);
    }
}

void Anthill::update(sf::Time dt)
{
    anthillTimer+=dt;
    if (sf::seconds(getAppConfig().anthill_spawn_delay) < anthillTimer)  {
        anthillTimer = sf::Time::Zero;
        generateAnt();
    }
}

Quantity Anthill::getFoodStock() const
{
    return foodStock ;
}

Uid Anthill::getId() const
{
    return id;
}

double Anthill:: getWorkerProb () const
{
    return getAppConfig().anthill_worker_prob_default ;
}

void Anthill::addFoodStock (const Quantity& addedQuantity)
{
    foodStock += addedQuantity;
}

void Anthill::generateAnt()const
{
    double prob = uniform(0,1);

    if (prob<=getWorkerProb()) {
        AntWorker* newWorker = new AntWorker(getPosition(),getId());
        getAppEnv().addAnimal(newWorker);
    } else {
        AntSoldier* newSoldier = new AntSoldier(getPosition(),getId());
        getAppEnv().addAnimal(newSoldier);
    }
}
