#include "FoodGenerator.hpp"
#include "../Random/Random.hpp"
#include "../Application.hpp"
#include "Food.hpp"

#include <cmath>


void FoodGenerator::update(sf::Time dt)
{
    compteur += dt;
    if (sf::seconds(getAppConfig().food_generator_delta) < compteur ) {

        compteur = sf::Time::Zero ;
        double placeAleatoireX = normal(getAppConfig().simulation_size/2, pow(2,getAppConfig().simulation_size*1/4) );
        double placeAleatoireY = normal(getAppConfig().simulation_size/2, pow(2,getAppConfig().simulation_size*1/4) );

        Positionable placeAleatoire (placeAleatoireX,placeAleatoireY);
        Food* newFood = new Food(placeAleatoire,uniform(getAppConfig().food_min_qty,getAppConfig().food_max_qty ));
        getAppEnv().addFood(newFood);
    }
}