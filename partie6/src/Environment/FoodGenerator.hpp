/*
 * POOSV 2020-21
 * @author: Calamand Maxence & Verdillon Marie
 */
#pragma once
#include "../Utility/Types.hpp"
#include <SFML/Graphics.hpp>
#include "../Interface/Updatable.hpp"

class FoodGenerator : public Updatable
{

public :
    FoodGenerator() : timer (sf::Time::Zero) {}
    virtual ~FoodGenerator() {}

    /*!
    * @brief Generate food at random places
     */
    void update(sf::Time dt) override;

private :
    sf::Time timer;
} ;