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
    Pheromone (ToricPosition position,double quantity) : Positionable(position),quantity(quantity) {}
    virtual ~Pheromone() {}

    void update(sf::Time dt) override;
    void drawOn(sf::RenderTarget& target) const override;
    bool isNegligible() const;
    double getQuantity() const;

private :

    double quantity;
};