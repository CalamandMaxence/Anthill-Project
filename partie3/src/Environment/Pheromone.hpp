/*
 * POOSV 2020-21
 * @author: Calamand Maxence & Verdillon Marie
 */

#pragma once
#include "Positionable.hpp"
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"

class Pheromone : public Positionable, public Drawable, public Updatable
{
public :
    Pheromone (ToricPosition position,double quantite) : Positionable(position),quantite(quantite) {}

    void update(sf::Time dt) override;
    void drawOn(sf::RenderTarget& target) const override;
    bool isNegligible();
    double getQuantity() const;

private :

    double quantite;
};