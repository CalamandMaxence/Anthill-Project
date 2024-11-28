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
    if(pv == 0 or esperance <= 0) return true;
    return false;
}

void Animal::drawOn(sf::RenderTarget& target) const
{
    auto animalSprite = buildSprite(getPosition().toVec2d(), 50,getAppTexture(getAppConfig().animal_default_texture));
    animalSprite.setRotation(angle / DEG_TO_RAD);
    target.draw(animalSprite);

    if(isDebugOn()) {
        sf::VertexArray ligne(sf::PrimitiveType::Lines, 2);
        ligne[0] = { getPosition().toVec2d(), sf::Color::Black };
        ligne[1] = { Vec2d::fromAngle(angle)*50 + getPosition().toVec2d(), sf::Color::Blue };
        target.draw(ligne);
    }
}

void Animal::move(sf::Time dt)
{
    auto dx = getPosition().toVec2d().fromAngle(angle)*getSpeed()*dt.asSeconds();
    setPosition(dx + getPosition());
    timer += dt;

    if(sf::seconds(getAppConfig().animal_next_rotation_delay) < timer) {
        timer = sf::Time::Zero;

        /*std::piecewise_linear_distribution<> dist(computeRotationProbs().first.begin(),
                                                  computeRotationProbs().first.end(),
                                                  computeRotationProbs().second.begin());*/

        setDirection(//dist(getRandomGenerator())
            uniform(-10,10)
            *DEG_TO_RAD + angle);
    }
}

void Animal::update(sf::Time& dt)
{
    move(dt);
    esperance -= dt.asSeconds();

}

RotationProbs Animal::computeRotationProbs()
{
    RotationProbs r(    {-180, -100, -55, -25, -10, 0, 10, 25, 55, 100, 180},
    {0.0000,0.0000,0.0005,0.0010,0.0050,0.9870,0.0050,0.0010,0.0005,0.0000,0.0000});
    return r;
}