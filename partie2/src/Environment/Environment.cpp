#include "Environment.hpp"
#include "../Application.hpp"

void Environment::addAnimal(Animal* nouvelAnimal)
{
    if (nouvelAnimal != nullptr) {
        faune.push_back(nouvelAnimal);
    }
}

void Environment::addFood(Food* nouvelleFood)
{
    if (nouvelleFood != nullptr) {
        sourcesNourriture.push_back(nouvelleFood);
    }
}

void Environment::update(sf::Time dt)
{
    for(auto& animal : faune) {
        animal->update(dt);
        if(animal->isDead()) {
            delete animal;
            animal = nullptr;
        }
    }
    faune.erase(std::remove(faune.begin(), faune.end(), nullptr), faune.end());

    foodGenerator.update(dt);
}

void Environment::drawOn(sf::RenderTarget& targetWindow) const
{
    for(auto& animal : faune) {
        animal->drawOn(targetWindow);
    }
    for(auto& source : sourcesNourriture) {
        source->drawOn(targetWindow);
    }
}

void Environment::reset()
{
    for (auto& animal : faune) {
        delete animal;
        animal = nullptr;
    }
    faune.clear();
    for (auto& source : sourcesNourriture) {
        delete source;
        source = nullptr;
    }
    sourcesNourriture.clear();
}