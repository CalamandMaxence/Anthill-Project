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

    //Constructeur
    AntSoldier(ToricPosition position = {0,0}, Uid indicateur = 0);

    //Methodes
    void update(sf::Time dt) override;
    void drawOn(sf::RenderTarget& target) const override;
} ;


