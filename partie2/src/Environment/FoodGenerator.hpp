#pragma once
#include "../Utility/Types.hpp"
#include <SFML/Graphics.hpp>

class FoodGenerator
{

public :
    FoodGenerator() : compteur (sf::Time::Zero) {}

    //Méthodes
    void update(sf::Time& dt);

private :
    sf::Time compteur;

} ;