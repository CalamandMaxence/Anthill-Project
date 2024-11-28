/*
 * POOSV 2020-21
 * @author: Calamand Maxence & Verdillon Marie
 */
#pragma once
#include "Animal.hpp"

class Termite : public Animal
{

public :

    //Constructeur
    Termite (ToricPosition positionTermite);

    //Methodes
    void drawOnTermite(sf::RenderTarget& target, sf::Texture texture) const ;
    void drawOn(sf::RenderTarget& target) const override;
    double getSpeed() const override;
    void update(sf::Time dt) override;
    bool isEnemy (Animal const* animal) const override ;
    bool isEnemyDispatch (Termite const* other) const override;
    bool isEnemyDispatch(Ant const*other) const override;


} ;