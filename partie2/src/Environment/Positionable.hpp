/*
 * POOSV 2020-21
 * @author:
 */

#pragma once
#include "ToricPosition.hpp"

/*!
 * @brief Manage a position in a toric world
 *
 *
 */
class Positionable
{
public :

    // Constructeurs
    Positionable(ToricPosition position) : position(position) {}	   	   //considérer a rajouter des constructeurs(pour Vec2d par exemple si besoin)
    Positionable(double x=0, double y=0) : position(x,y) {}
    // Getter
    ToricPosition const& getPosition() const;

    // Methodes
    void setPosition(const ToricPosition& position);
    std::ostream& display(std::ostream& out) const;

private :

    ToricPosition position;

};

std::ostream& operator<<(std::ostream& out,Positionable p);


