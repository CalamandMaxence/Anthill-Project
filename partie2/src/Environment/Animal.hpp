#pragma once
#include <SFML/Graphics.hpp>
#include "Positionable.hpp"
#include "../Utility/Types.hpp"
#include "../Utility/Constants.hpp"
#include "../Random/Random.hpp"

class Animal : public Positionable
{
public :

    //Constructeurs
    Animal(Vec2d pos = {0,0},double pv = 1,double esperance = 100, sf::Time timer = sf::Time::Zero)
        :Positionable(pos.x(),pos.y()), pv(pv),angle(uniform(0.0,TAU)), esperance(100), timer(timer)
    {}

    //Getters
    double getDirection() const;
    double getSpeed() const;
    bool isDead() const;
    void drawOn(sf::RenderTarget& target) const;

    //Methodes
    void move(sf::Time dt);
    void update(sf::Time& dt);
    RotationProbs computeRotationProbs();

protected:

    void setDirection(double angle);

private:

    double pv;
    Angle angle;
    double esperance;

    sf::Time timer;
};
