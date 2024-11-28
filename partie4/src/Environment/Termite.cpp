#include "Termite.hpp"
#include "../Application.hpp"

//Constructeur

Termite::Termite (ToricPosition positionTermite)
    : Animal(positionTermite.toVec2d(), getAppConfig().termite_hp,getAppConfig().termite_lifespan) {}

//Methodes

void Termite::drawOn(sf::RenderTarget& target) const
{
    auto TermiteSprite = buildSprite(getPosition().toVec2d(), 30,getAppTexture(getAppConfig().termite_texture));
    TermiteSprite.setRotation(getDirection() / DEG_TO_RAD);
    target.draw(TermiteSprite);

    if(isDebugOn()) {
        sf::VertexArray ligne(sf::PrimitiveType::Lines, 2);
        ligne[0] = { getPosition().toVec2d(), sf::Color::Red };
        ligne[1] = { Vec2d::fromAngle(getDirection())*50 + getPosition().toVec2d(), sf::Color::Red };
        target.draw(ligne);
    }
}

double Termite::getSpeed() const
{
    return getAppConfig().termite_speed;
}

void Termite::update(sf::Time dt)
{
    Animal* closestEnemy = getAppEnv().getClosestEnemy(this);

    switch(getAttitude()) {
    case Attack:
        if(closestEnemy != nullptr) attack(closestEnemy,getAppConfig().termite_strength);
        setTimer_fight(getTimer_fight()+dt);

        if(getTimer_fight().asSeconds() > getAppConfig().termite_attack_delay) {
            setAttitude(Idle);
            setTimer_fight(sf::Time::Zero);
        }
        break;

    case Idle:
        move(dt);
        if(closestEnemy != nullptr) {
            setAttitude(Attack);
        }
        break;

    }
}

bool Termite::isEnemy (Animal const* animal) const
{
    return !isDead() && !animal->isDead() && animal->isEnemyDispatch(this);
}

bool Termite::isEnemyDispatch (Termite const* other) const
{
    return false;
}

bool Termite::isEnemyDispatch(Ant const*other) const
{
    return true;
}

