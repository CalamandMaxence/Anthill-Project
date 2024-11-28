#include "Environment.hpp"
#include "../Application.hpp"
#include <cmath>

Environment::Environment()
{
    displayPheromone = false;
    counters = std::vector<double>(4,0);
    temperature = 20;
}

void Environment::addAnimal(Animal* newAnimal)
{
    if (newAnimal != nullptr) {
        fauna.push_back(newAnimal);
    }
}

void Environment::addFood(Food* newFood)
{
    if (newFood != nullptr) {
        foodSources.push_back(newFood);
    }
}

void Environment::addAnthill(Anthill* newAnthill)
{
    if (newAnthill != nullptr) {
        anthills.push_back(newAnthill);
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
    for(auto& animal : fauna) {
        if(animal != nullptr) {
            animal->update(dt);
            if(animal->isDead()) {
                delete animal;
                animal = nullptr;
            }
        }
    }
    fauna.erase(std::remove(fauna.begin(), fauna.end(), nullptr), fauna.end());

    for(auto& source : foodSources) {
        if(source != nullptr) {
            if(source->isEmpty()) {
                delete source;
                source = nullptr;
            }
        }
    }
    foodSources.erase(std::remove(foodSources.begin(), foodSources.end(), nullptr), foodSources.end());

    for(auto& anthill : anthills) {
        if (anthill != nullptr) {
            anthill->update(dt);
        }
    }

    for(auto& pheromone : pheromones) {
        if(pheromone != nullptr) {
            pheromone->update(dt);
            if(pheromone->isNegligible()) {
                delete pheromone;
                pheromone = nullptr;
            }
        }
    }
    pheromones.erase(std::remove(pheromones.begin(), pheromones.end(), nullptr), pheromones.end());

    foodGenerator.update(dt);
}

void Environment::drawOn(sf::RenderTarget& targetWindow) const
{
    for(auto& animal : fauna) {
        if(animal != nullptr) {
            animal->drawOn(targetWindow);
        }
    }

    for(auto& source : foodSources) {
        if(source != nullptr) {
            source->drawOn(targetWindow);
        }
    }

    for(auto& anthill : anthills) {
        if(anthill != nullptr) {
            anthill->drawOn(targetWindow);
        }
    }

    if(displayPheromone) {
        for(auto& pheromone : pheromones) {
            if(pheromone != nullptr) {
                pheromone->drawOn(targetWindow);
            }
        }
    }
}

void Environment::reset()
{
    for (auto& animal : fauna) {
        delete animal;
        animal = nullptr;
    }
    fauna.clear();

    for (auto& source : foodSources) {
        delete source;
        source = nullptr;
    }
    foodSources.clear();

    for (auto& anthill : anthills) {
        delete anthill;
        anthill = nullptr;
    }
    anthills.clear();

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

Quantities Environment::getPheromoneQuantitiesPerIntervalForAnt(const ToricPosition &position,Angle direction_rad,const Intervals &angles) const
{
    Quantities quantities(angles.size(),0);
    ToricPosition pos = position;

    for(auto pheromone : pheromones) {
        if(pheromone != nullptr) {
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

                quantities[indice] += pheromone->getQuantity();
            }
        }
    }

    return quantities;
}

Anthill* Environment::getAnthillfromUid(Uid id) const
{
    for ( auto anthill : anthills) {
        if(anthill != nullptr) {
            if (id== anthill->getId()) {
                return anthill;
            }
        }
    }
    return nullptr ;
}

Food* Environment::getClosestFoodForAnt (ToricPosition const& antPosition)const
{
    Food* closestFood = nullptr;
    double distance (getAppConfig().ant_max_perception_distance) ;

    for (auto source : foodSources) {
        if(source != nullptr) {
            if (toricDistance (source->getPosition(), antPosition) < distance) {
                distance = toricDistance (source->getPosition(), antPosition) ;
                closestFood = source ;
            }
        }
    }

    if (closestFood != nullptr and toricDistance (closestFood->getPosition(), antPosition) < getAppConfig().ant_max_perception_distance) return closestFood;
    else return nullptr;
}

Animal* Environment::getClosestEnemy (Animal* seekingAnimal)const
{
    Animal* closestEnemy = nullptr ;
    double distance (getAppConfig().animal_sight_distance) ;

    for (auto& animal : fauna) {
        if(animal != nullptr && seekingAnimal != nullptr) {
            if (toricDistance (animal->getPosition(), seekingAnimal->getPosition()) < distance && seekingAnimal->isEnemy(animal)) {
                distance = toricDistance (animal->getPosition(), seekingAnimal->getPosition()) ;
                closestEnemy = animal ;
            }
        }
    }

    if(closestEnemy != nullptr  and toricDistance (closestEnemy->getPosition(), seekingAnimal->getPosition()) < getAppConfig().animal_sight_distance) return closestEnemy;
    else return nullptr;
}

double Environment::getTemperature() const
{
    return temperature;
}

void Environment::setTemperature(double temperature)
{
    this->temperature = temperature;
}

void Environment::incrementCounters(Entity entity)
{
    switch(entity) {
    case antWorker :
        counters[0] += 1;
        break;
    case antSoldier :
        counters[1] += 1;
        break;
    case termite :
        counters[2] += 1;
        break;
    case food :
        counters[3] += 1;
        break;
    case anthill :
        counters[4] += 1;
        break;
    }

}

void Environment::decrementCounters(Entity entity)
{
    switch(entity) {
    case antWorker :
        counters[0] -= 1;
        break;
    case antSoldier :
        counters[1] -= 1;
        break;
    case termite :
        counters[2] -= 1;
        break;
    case food :
        counters[3] -= 1;
        break;
    case anthill :
        counters[4] -= 1;
        break;
    }

}

double Environment::getCounters(Entity entity) const
{
    switch(entity) {
    case antWorker :
        return counters[0];
        break;
    case antSoldier :
        return counters[1];
        break;
    case termite :
        return counters[2];
        break;
    case food :
        return counters[3];
        break;
    case anthill :
        return counters[4];
        break;
    }
    return 0;
}

std::vector<std::string> Environment::getAnthillsIds() const
{
    std::vector<std::string> namesAnthill (anthills.size(),"no Anthill");
    std::string name ("anthill #");
    for (size_t i (0); i < anthills.size(); ++i) {
        if(anthills[i] != nullptr) {
            namesAnthill[i] = name+std::to_string(anthills[i]->getId()) ;
        }
    }
    return namesAnthill;
}

std::unordered_map<std::string, double> Environment::fetchData(const std::string& graphTitle) const
{
    std::unordered_map<std::string, double> new_data;

    if (graphTitle == s::GENERAL) {
        new_data = {
            {s::WORKER_ANTS, getCounters(antWorker)},
            {s::SOLDIER_ANTS, getCounters(antSoldier)},
            {s::TERMITES, getCounters(termite)},
            {s::TEMPERATURE, getTemperature()}
        } ;
    }

    if (graphTitle == s::FOOD) {
        new_data = {{s::FOOD, getFoodTotalAmount()}} ;
    }

    if (graphTitle == s::ANTHILLS) {
        std::vector<std::string> names (getAnthillsIds());

        for (size_t i(0); i < names.size(); ++i) {
            if(anthills[i] != nullptr) {
                std::pair<std::string,double> newData (names[i],anthills[i]->getFoodStock());
                new_data.insert (newData);
            }
        }
    }

    return new_data;
}

double Environment::getFoodTotalAmount() const
{
    double totalAmount(0);
    for(auto source : foodSources) {
        if(source != nullptr) {
            totalAmount += source->getQuantity();
        }
    }
    return totalAmount;
}
