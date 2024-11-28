/*
 * POOSV 2020-21
 * @author: Calamand Maxence & Verdillon Marie
 */

#pragma once
#include "ToricPosition.hpp"

enum Entity {antWorker, antSoldier, termite, food, anthill};

/*!
 * @brief Manage a position in a toric world
 *
 *
 */
class Positionable
{
public :

    Positionable(const ToricPosition& position) : position(position) {}
    Positionable(double x=0, double y=0) : position(x,y) {}
    virtual ~Positionable() {}

    ToricPosition getPosition() const;
    void setPosition(const ToricPosition& position);
    std::ostream& display(std::ostream& out) const;

private :

    ToricPosition position;

};

std::ostream& operator<<(std::ostream& out,Positionable p);


