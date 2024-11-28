#include "Environment.hpp"
#include "../Application.hpp"
#include <cmath>

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

void Environment::addAnthill(Anthill* newAntHill)
{
    if (newAntHill != nullptr) {
        antHills.push_back(newAntHill);
    }
}

void Environment::addPheromone(Pheromone* newPheromone)
{
    if (newPheromone != nullptr) {
        pheromones.push_back(newPheromone);
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

    for(auto& source : sourcesNourriture) {
        if(source->isEmpty()) {
            delete source;
            source = nullptr;
        }
    }
    sourcesNourriture.erase(std::remove(sourcesNourriture.begin(), sourcesNourriture.end(), nullptr), sourcesNourriture.end());

    for(auto& anthill : antHills) {
        anthill->update(dt);
    }

    for(auto& pheromone : pheromones) {
        pheromone->update(dt);
        if(pheromone->isNegligible()) {
            delete pheromone;
            pheromone = nullptr;
        }
    }
    pheromones.erase(std::remove(pheromones.begin(), pheromones.end(), nullptr), pheromones.end());

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

    for(auto& anthill : antHills) {
        anthill->drawOn(targetWindow);
    }

    if(displayPheromone) {
        for(auto& pheromone : pheromones) {
            pheromone->drawOn(targetWindow);
        }
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

    for (auto& anthill : antHills) {
        delete anthill;
        anthill = nullptr;
    }
    antHills.clear();

    for (auto& pheromone : pheromones) {
        delete pheromone;
        pheromone = nullptr;
    }
    pheromones.clear();
}

bool Environment::togglePheromoneDisplay()
{
    if(displayPheromone) {
        displayPheromone = false;
        return displayPheromone;
    }
    displayPheromone = true;
    return displayPheromone;
}

Quantities Environment::getPheromoneQuantitiesPerIntervalForAnt(const ToricPosition &position,Angle direction_rad,const Intervals &angles)
{
    Quantities quantitees(angles.size(),0);
    ToricPosition pos = position;

    for(auto pheromone : pheromones) {
        if(toricDistance(position,pheromone->getPosition()) < getAppConfig().ant_smell_max_distance) {
            Angle beta = (pos.toricVector(pheromone->getPosition()).angle() - direction_rad)/DEG_TO_RAD;
            if(beta < 0) {
                beta += 360;
            } else if(beta >= 360) {
                beta -= 360;
            }

            Angle dist(360);
            int indice;

            for(std::size_t i(0); i<angles.size(); ++i) {
                if(abs(beta - angles[i]) < dist) {
                    dist = beta - angles[i];
                    indice = i;
                }
            }

            quantitees[indice] += pheromone->getQuantity();
        }
    }

    return quantitees;
}

std::vector<Food*> Environment::getSourcesNourriture() const
{
    return sourcesNourriture;
}

std::vector<Anthill*> Environment::getEnsembleFourmilieres() const
{
    return antHills;
}

Food* Environment::getClosestFoodForAnt (ToricPosition const& antPosition)
{
    Food* closestFood = nullptr;
    double distance (getAppConfig().ant_max_perception_distance) ;

    for (auto source : sourcesNourriture) {
        if (toricDistance (source->getPosition(), antPosition) < distance) {
            distance = toricDistance (source->getPosition(), antPosition) ;
            closestFood = source ;
        }

    }

    if (closestFood != nullptr and toricDistance (closestFood->getPosition(), antPosition) < getAppConfig().ant_max_perception_distance) return closestFood;
    else return nullptr;
}

Anthill* Environment::getAnthillForAnt (ToricPosition const& position, Uid anthillId)
{
    if (toricDistance (getAnthillfromUid(anthillId)->getPosition(), position) < getAppConfig().ant_max_perception_distance) {
        return getAnthillfromUid(anthillId);
    }
    return nullptr;
}

Animal* Environment::getClosestEnemy (Animal* seekingAnimal)const
{
    Animal* closestEnemy = nullptr ;
    double distance (getAppConfig().animal_sight_distance) ;

    for (auto& animal : faune) {
        if(animal != nullptr) {
            if (toricDistance (animal->getPosition(), seekingAnimal->getPosition()) < distance && seekingAnimal->isEnemy(animal)) {
                distance = toricDistance (animal->getPosition(), seekingAnimal->getPosition()) ;
                closestEnemy = animal ;
            }
        }
    }

    if(closestEnemy != nullptr  and toricDistance (closestEnemy->getPosition(), seekingAnimal->getPosition()) < getAppConfig().animal_sight_distance) return closestEnemy;
    else return nullptr;
}