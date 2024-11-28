/*
 * POOSV 2020-21
 * @author: Calamand Maxence & Verdillon Marie
 */
#pragma once
#include "Ant.hpp"
#include "../Random/Random.hpp"
#include "Animal.hpp"


class AntSoldier : public Ant
{
public :

    AntSoldier(ToricPosition position = {0,0}, Uid id = 0);
    virtual ~AntSoldier();

    /*!
    * @brief Attack an enemy if detected, else spread pheromones and move
     */
    void update(sf::Time dt) override;
    void drawOn(sf::RenderTarget& target) const override;
} ;


