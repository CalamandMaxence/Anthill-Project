/*
 * POOSV 2020-21
 * @author: Calamand Maxence & Verdillon Marie
 */
#pragma once
#include <SFML/Graphics.hpp>
#include "Positionable.hpp"
#include "../Utility/Types.hpp"
#include "../Utility/Constants.hpp"
#include "../Random/Random.hpp"
#include "../Interface/Updatable.hpp"
#include "../Interface/Drawable.hpp"

class Ant;
class Termite;

enum Attitude {Attack, Idle};

class Animal : public Positionable, public Drawable, public Updatable
{
public :

    Animal(Vec2d pos = {0,0},double hp = 1,double lifespan = 500, sf::Time timer = sf::Time::Zero, sf::Time timer_fight = sf::Time::Zero, Attitude attitude = Idle)
        :Positionable(pos.x(),pos.y()), hp(hp),angle(uniform(0.0,TAU)), lifespan(lifespan), timer(timer), timer_fight(timer_fight), attitude(attitude)
    {}
    virtual ~Animal() {}

    double getDirection() const;
    virtual double getSpeed() const = 0;

    /*!
    * @brief Update the position each dt
     *
     * @note Use computeRotationProbs to generate random movements
     */
    void move(const sf::Time& dt);

    bool isDead() const;

    /*!
    * @brief return pairs of angles and probabilities
     */
    virtual RotationProbs computeRotationProbs() const;

    /*!
    * @brief All boolean methods below computes if the other animal is an enemy
     */
    virtual bool isEnemy (Animal const* entity) const = 0 ;
    virtual bool isEnemyDispatch (Termite const* other) const = 0 ;
    virtual bool isEnemyDispatch(Ant const* other) const = 0 ;

    Attitude getAttitude() const;
    void setAttitude(const Attitude& newAttitude);

    /*!
    * @brief computes the attack phase
     */
    void attack(Animal* closestEnemy, double const& strengh) const;
    void setDamage(double const& damage_taken);
    void setTimer_fight(sf::Time increment);
    sf::Time getTimer_fight() const;
    double getHP()const;

protected:

    void setDirection(double angle);

private:

    double hp;
    Angle angle;
    double lifespan;

    sf::Time timer;
    sf::Time timer_fight;

    Attitude attitude;
};
