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

    //Constructeurs
    Animal(Vec2d pos = {0,0},double hp = 1,double esperance = 500, sf::Time timer = sf::Time::Zero, sf::Time timer_fight = sf::Time::Zero, Attitude attitude = Idle)
        :Positionable(pos.x(),pos.y()), hp(hp),angle(uniform(0.0,TAU)), esperance(esperance), timer(timer), timer_fight(timer_fight), attitude(attitude)
    {}

    //Getters

    double getDirection() const;

    virtual double getSpeed() const = 0;

    //Methodes

    /*!
    * @brief Update the position each dt
     *
     * @note Use computeRotationProbs to generate random movements
     */
    void move(sf::Time dt);

    bool isDead() const;

    /*!
    * @brief return pairs of angles and probabilities
     */
    virtual RotationProbs computeRotationProbs() const;

    virtual bool isEnemy (Animal const* entity) const = 0 ;
    virtual bool isEnemyDispatch (Termite const* other) const = 0 ;
    virtual bool isEnemyDispatch(Ant const* other) const = 0 ;

    Attitude getAttitude();
    void setAttitude(Attitude newAttitude);

    void attack(Animal* closestEnemy, double const& strengh);
    void setDamage(double const& damage_taken);
    void setTimer_fight(sf::Time increment);
    sf::Time getTimer_fight() const;
    double getHP()const;

protected:

    void setDirection(double angle);

private:

    double hp;
    Angle angle;
    double esperance;

    sf::Time timer;
    sf::Time timer_fight;

    Attitude attitude;
};
