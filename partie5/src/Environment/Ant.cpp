#include "Ant.hpp"
#include "../Application.hpp"
#include "../Utility/Constants.hpp"
#include <cmath>

Ant::Ant (ToricPosition antPosition, Uid anthillId, double hp, double lifespan, Pheromone* lastPheromone)
    : Animal(antPosition.toVec2d(), hp, lifespan ),associatedAnthill(anthillId),lastPheromone(lastPheromone)
{}

double Ant::getSpeed() const
{
    return getAppConfig().ant_speed;
}

void Ant::spreadPheromones()
{
    if(lastPheromone != nullptr) {
        double instances = toricDistance(getPosition(),lastPheromone->getPosition())*getAppConfig().ant_pheromone_density;
        for(double i = 1; i< instances; i++) {
            ToricPosition position = getPosition();
            position.toricVector(lastPheromone->getPosition());
            Pheromone* newPheromone = new Pheromone(position,getAppConfig().ant_pheromone_energy);
            getAppEnv().addPheromone(newPheromone);
            lastPheromone = newPheromone;
        }
    }
}

void Ant::debugProba(sf::RenderTarget& target) const
{
    auto const intervalProbs = computeRotationProbs();
    for (std::size_t i = 0; i < intervalProbs.first.size(); ++i) {
        auto const msg = std::to_string(intervalProbs.second[i]).substr(2, 4);
        auto const angle = intervalProbs.first[i];
        auto const local = Vec2d::fromAngle(getDirection() + angle * DEG_TO_RAD) * 250;

        auto const text = buildText(msg, getPosition().toVec2d() + local, getAppFont(), 15, sf::Color::Black);
        target.draw(text);
    }

    Intervals intervals = computeRotationProbs().first;
    auto const quantities = getAppEnv().getPheromoneQuantitiesPerIntervalForAnt(getPosition(), getDirection(), intervals);
    for (std::size_t i = 0; i < quantities.size(); ++i) {
        auto const msg = std::to_string(quantities[i]).substr(0, 4);
        auto const angle = intervals[i];
        auto const local = Vec2d::fromAngle(getDirection() + angle * DEG_TO_RAD) * 200;

        auto const text = buildText(msg, getPosition().toVec2d() + local, getAppFont(), 15, sf::Color::Red);
        target.draw(text);
    }
}

RotationProbs Ant::computeRotationProbs() const
{
    Probs pm = { 0.0000, 0.0005, 0.0010, 0.0050, 0.9870, 0.0050, 0.0010, 0.0005, 0.0000, 0.0000};
    Intervals I = {   -100,    -55,    -25,    -10,      0,     10,     25,     55,    100,    180 };

    Probs pphi;
    for(std::size_t i(0); i < pm.size(); ++i) {
        pphi.push_back(   1/ (  1+exp(  -getAppConfig().beta_d * (getAppEnv().getPheromoneQuantitiesPerIntervalForAnt(getPosition(),getDirection(),I)[i] - getAppConfig().q_zero )  )   ));
    }

    Probs tmp;
    for(std::size_t i(0); i < pm.size(); ++i) {
        tmp.push_back(pm[i]*pow(pphi[i], getAppConfig().alpha));
    }

    double z(0);
    for(std::size_t i(0); i < pm.size(); ++i) {
        z += tmp[i];
    }

    Probs pm2;
    for(std::size_t i(0); i < pm.size(); ++i) {
        pm2.push_back(tmp[i]/z);
    }

    RotationProbs r({I,pm2});

    return r;
}

void Ant::setDirectionUTurn ()
{
    Angle angle (getDirection());
    angle += PI;
    setDirection(angle);
}

Uid Ant::getAssociatedAnthill ()const
{
    return associatedAnthill;
}

void Ant::drawOnAnt(sf::RenderTarget& target, const sf::Texture& texture) const
{
    auto antSprite = buildSprite(getPosition().toVec2d(), 30,texture);
    antSprite.setRotation(getDirection() / DEG_TO_RAD);
    target.draw(antSprite);

    if(isDebugOn()) {
        sf::VertexArray line(sf::PrimitiveType::Lines, 2);
        line[0] = { getPosition().toVec2d(), sf::Color::Black };
        line[1] = { Vec2d::fromAngle(getDirection())*50 + getPosition().toVec2d(), sf::Color::Blue };
        target.draw(line);

        auto const annulusSprite = buildAnnulus(getPosition().toVec2d(), getAppConfig().ant_smell_max_distance, sf::Color::Blue,5);
        target.draw(annulusSprite);
    }

    if(getAppConfig().getProbaDebug()) {
        debugProba(target);
    }
}

bool Ant::isEnemyDispatch (Termite const* other) const
{
    return true;
}

bool Ant::isEnemyDispatch(Ant const* other) const
{
    return getAssociatedAnthill() != other->getAssociatedAnthill();
}

bool Ant::isEnemy (Animal const* animal) const
{
    return  (!isDead()) && (!animal->isDead()) && (animal->isEnemyDispatch(this)) ;
}