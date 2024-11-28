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

class Animal : public Positionable, public Drawable, public Updatable
{
public :

    //Constructeurs
    Animal(Vec2d pos = {0,0},double pv = 1,double esperance = 500, sf::Time timer = sf::Time::Zero)
        :Positionable(pos.x(),pos.y()), pv(pv),angle(uniform(0.0,TAU)), esperance(esperance), timer(timer)
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

protected:

    void setDirection(double angle);

private:

    double pv;
    Angle angle;
    double esperance;

    sf::Time timer;
};
