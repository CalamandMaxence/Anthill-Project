#include "Ant.hpp"
#include "../Application.hpp"
#include "../Utility/Constants.hpp"
#include <cmath>

Ant::Ant (ToricPosition positionFourmi, Uid fourmiliere, double pointdevie, double esperance, Pheromone* lastPheromone)
    : Animal(positionFourmi.toVec2d(), pointdevie, esperance ),associatedAnthill(fourmiliere),lastPheromone(lastPheromone)
{}

double Ant::getSpeed() const
{
    return getAppConfig().ant_speed;
}

void Ant::spreadPheromones()
{
    double nbr_instances = toricDistance(getPosition(),lastPheromone->getPosition())*getAppConfig().ant_pheromone_density;
    for(double i = 1; i< nbr_instances; i++) {
        ToricPosition pos = getPosition();
        pos.toricVector(lastPheromone->getPosition());
        Pheromone* newPheromone = new Pheromone(pos,getAppConfig().ant_pheromone_energy);
        getAppEnv().addPheromone(newPheromone);
        lastPheromone = newPheromone;
    }
}

void Ant::debugProba(sf::RenderTarget& target) const
{
    auto const intervalProbs = computeRotationProbs();
    // pour intervalProbs (first désigne l'ensemble des angles)
    for (std::size_t i = 0; i < intervalProbs.first.size(); ++i) {
        // "second" designe l'ensemble des probabilités
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

void Ant::setDirectionUturn ()
{
    Angle angle (getDirection());
    angle += PI;
    setDirection(angle);
}

Uid Ant::getAssociatedAnthill ()const
{
    return associatedAnthill;
}

void Ant::drawOnAnt(sf::RenderTarget& target, sf::Texture texture) const
{
    auto antWorkerSprite = buildSprite(getPosition().toVec2d(), 30,texture);
    antWorkerSprite.setRotation(getDirection() / DEG_TO_RAD);
    target.draw(antWorkerSprite);

    if(isDebugOn()) {
        sf::VertexArray ligne(sf::PrimitiveType::Lines, 2);
        ligne[0] = { getPosition().toVec2d(), sf::Color::Black };
        ligne[1] = { Vec2d::fromAngle(getDirection())*50 + getPosition().toVec2d(), sf::Color::Blue };
        target.draw(ligne);

        auto const annulusSprite = buildAnnulus(getPosition().toVec2d(), getAppConfig().ant_smell_max_distance, sf::Color::Blue,5);
        target.draw(annulusSprite);
    }

    if(getAppConfig().getProbaDebug()) {
        debugProba(target);
    }
}