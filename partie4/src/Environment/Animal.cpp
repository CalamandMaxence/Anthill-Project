#include "Animal.hpp"
#include <cmath>
#include "../Application.hpp"
#include "../Utility/Utility.hpp"

double Animal::getSpeed() const
{
    return getAppConfig().animal_default_speed;
}

double Animal::getDirection() const
{
    return angle;
}

void Animal::setDirection(double angle)
{
    this->angle = angle;
}

bool Animal::isDead() const
{
    return hp <= 0 or esperance <= 0;
}

void Animal::move(sf::Time dt)
{
    auto dx = getPosition().toVec2d().fromAngle(angle)*getSpeed()*dt.asSeconds();
    setPosition(dx + getPosition());
    timer += dt;

    if(sf::seconds(getAppConfig().animal_next_rotation_delay) < timer) {
        timer = sf::Time::Zero;
        Intervals i = computeRotationProbs().first;
        Probs p = computeRotationProbs().second;

        std::piecewise_linear_distribution<> dist(i.begin(),
                i.end(),
                p.begin());

        setDirection(dist(getRandomGenerator())*DEG_TO_RAD + angle);
    }
    esperance -= dt.asSeconds();
}

RotationProbs Animal::computeRotationProbs() const
{
    RotationProbs r(    {-180, -100, -55, -25, -10, 0, 10, 25, 55, 100, 180},
    {0.0000,0.0000,0.0005,0.0010,0.0050,0.9870,0.0050,0.0010,0.0005,0.0000,0.0000});
    return r;
}

Attitude Animal::getAttitude()
{
    return attitude;
}

void Animal::setAttitude(Attitude newAttitude)
{
    attitude = newAttitude;
}

void Animal::attack(Animal* closestEnemy, double const& strengh)
{
    closestEnemy->setDamage(strengh);
}

void Animal::setDamage(double const& damage_taken)
{
    hp -= damage_taken;
}

void Animal::setTimer_fight(sf::Time increment)
{
    timer_fight = increment;
}

sf::Time Animal::getTimer_fight() const
{
    return timer_fight;
}

double Animal::getHP()const
{
    return hp;
}