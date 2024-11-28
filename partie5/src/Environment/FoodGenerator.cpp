#include "FoodGenerator.hpp"
#include "../Random/Random.hpp"
#include "../Application.hpp"
#include "Food.hpp"

#include <cmath>


void FoodGenerator::update(sf::Time dt)
{
    timer += dt;
    if (sf::seconds(getAppConfig().food_generator_delta) < timer ) {

        timer = sf::Time::Zero ;
        double randomX = normal(getAppConfig().simulation_size/2, pow(2,getAppConfig().simulation_size*1/4) );
        double randomY = normal(getAppConfig().simulation_size/2, pow(2,getAppConfig().simulation_size*1/4) );

        Positionable randomPlace (randomX,randomY);
        Food* newFood = new Food(randomPlace,uniform(getAppConfig().food_min_qty,getAppConfig().food_max_qty ));
        getAppEnv().addFood(newFood);
    }
}