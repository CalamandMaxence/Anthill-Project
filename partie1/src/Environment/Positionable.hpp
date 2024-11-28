/*
 * POOSV 2020-21
 * @author:
 */

#pragma once
#include <iostream>
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
    Positionable() : position(0,0) {}									//constructeur par defaut
    Positionable(ToricPosition position) : position(position) {}	   	//constructeur via un paramètre de type ToricPosition

    // Getter
    ToricPosition getPosition();

    // Methodes
    void setPosition(const ToricPosition& position);
    std::ostream& display(std::ostream& out);							//display qui affiche la position : sert à une bonne encapsulation

private :

    ToricPosition position;

};

std::ostream& operator<<(std::ostream& out,Positionable p);


