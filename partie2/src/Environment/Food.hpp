#pragma once
#include "Positionable.hpp"
#include "../Utility/Types.hpp"
#include <SFML/Graphics.hpp>

class Food : public Positionable
{
public :
    //Constructeur
    Food(Positionable positionNourriture, Quantity quantite)
        : Positionable(positionNourriture), quantite(quantite)
    {}
    Food(Vec2d pos, double q):Positionable(pos.x(),pos.y()),quantite(q) {}

    //Methodes
    Quantity takeQuantity (Quantity aPrelever);
    void drawOn(sf::RenderTarget& target) const ;

private:

    Quantity quantite;

};