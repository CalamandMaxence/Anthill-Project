/*
 * POOSV 2020-21
 * @author: Calamand Maxence & Verdillon Marie
 */
#pragma once
#include "Positionable.hpp"
#include "../Utility/Types.hpp"
#include <SFML/Graphics.hpp>
#include "../Interface/Drawable.hpp"

class Food : public Positionable, public Drawable
{
public :
    //Constructeur
    Food(Positionable positionNourriture, Quantity quantite)
        : Positionable(positionNourriture), quantite(quantite)
    {}
    Food(Vec2d pos, double q):Positionable(pos.x(),pos.y()),quantite(q) {}

    //Methodes
    /*!
    * @brief Remove a quantity of food from the source and return it
     */
    Quantity takeQuantity (Quantity const aPrelever);
    void drawOn(sf::RenderTarget& target) const override;
    bool isEmpty() const;

private:

    Quantity quantite;

};