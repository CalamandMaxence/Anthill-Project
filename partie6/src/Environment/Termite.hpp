/*
 * POOSV 2020-21
 * @author: Calamand Maxence & Verdillon Marie
 */
#pragma once
#include "Animal.hpp"

class Termite : public Animal
{

public :

    Termite (ToricPosition termitePosition);
    ~Termite();

    void drawOn(sf::RenderTarget& target) const override;
    double getSpeed() const override;

    /*!
    * @brief Attack an enemy if detected, else move
     */
    void update(sf::Time dt) override;

    /*!
    * @brief All boolean methods below computes if the other animal is an enemy
     */
    bool isEnemy (Animal const* animal) const override ;
    bool isEnemyDispatch (Termite const* other) const override;
    bool isEnemyDispatch(Ant const*other) const override;
} ;