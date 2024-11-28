/*
 * POOSV 2020-21
 * @author: Calamand Maxence & Verdillon Marie
 */
#pragma once
#include "Ant.hpp"
#include "../Random/Random.hpp"
#include "Animal.hpp"
#include "ToricPosition.hpp"

class AntWorker : public Ant
{
public :

    AntWorker (ToricPosition position = {0,0}, Uid id = 0);
    virtual ~AntWorker();

    /*!
     * @note Takes care of the interactions ant/food
     */
    void update(sf::Time dt) override;
    void drawOn(sf::RenderTarget& target) const override;

private :

    Quantity carryingQuantity;

} ;