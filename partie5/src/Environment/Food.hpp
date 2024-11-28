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

    Food(Positionable positionNourriture, Quantity quantite);
    Food(Vec2d pos, double q);
    virtual ~Food();

    /*!
    * @brief Remove a quantity of food from the source and return it
     */
    Quantity takeQuantity (Quantity const aPrelever);
    Quantity getQuantity() const;
    void drawOn(sf::RenderTarget& target) const override;
    bool isEmpty() const;

private:

    Quantity quantity;
};