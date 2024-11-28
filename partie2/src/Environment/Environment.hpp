#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Animal.hpp"
#include "Food.hpp"
#include "FoodGenerator.hpp"

class Environment
{
public:
    ~Environment()
    {
        reset();
    }

    //Methodes
    void addAnimal (Animal* nouvelAnimal);
    void addFood(Food* nouvelleFood) ;
    void update(sf::Time dt);
    void drawOn(sf::RenderTarget& targetWindow) const;
    void reset();

private:

    std::vector <Animal*> faune;
    std::vector <Food*> sourcesNourriture;
    FoodGenerator foodGenerator;

};