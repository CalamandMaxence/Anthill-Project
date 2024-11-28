/*
 * POOSV 2020-21
 * @author: Calamand Maxence & Verdillon Marie
 */
#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Animal.hpp"
#include "Food.hpp"
#include "FoodGenerator.hpp"
#include "Anthill.hpp"
#include "Termitemound.hpp"
#include "Pheromone.hpp"
#include <unordered_map>

class Environment
{
public:

    Environment();
    ~Environment()
    {
        reset();
    }

    void addAnimal (Animal* newAnimal);
    void addFood(Food* newFood) ;
    void addAnthill(Anthill* newAnthill);
    void addTermitemound(Termite_mound* newTermitemound);
    void addPheromone(Pheromone* newPheromone);

    /*!
     * @note Takes care of supressing dead animals, empty foods and evaporate pheromones
     */
    void update(sf::Time dt);
    void drawOn(sf::RenderTarget& targetWindow) const;

    void reset();
    bool togglePheromoneDisplay();

    /*!
    * @brief Get the pheromone quantity around the ant
     */
    Quantities getPheromoneQuantitiesPerIntervalForAnt(const ToricPosition &position,Angle direction_rad,const Intervals &angles) const;

    /*!
    * @brief Get the closest food in the viewing range of the ant
     */
    Food* getClosestFoodForAnt (ToricPosition const& position)const;

    /*!
    * @brief Return the anthill associated
     */
    Anthill* getAnthillfromUid(Uid id) const;

    Animal* getClosestEnemy (Animal* seekingAnimal) const;

    /*!
    * @return Return the amount of food
     */
    double getFoodTotalAmount() const;

    double getTemperature() const;

    /*!
    * @brief Compute all data and associate them
     */
    std::unordered_map<std::string, double> fetchData(const std::string& graphTitle) const;

    void setTemperature(double newTemperature);

    std::vector<std::string> getAnthillsIds() const ;

    /*!
    * @brief All methods below take care of counting all entities
     */
    void incrementCounters(Entity entity);
    void decrementCounters(Entity entity);
    double getCounters(Entity entity) const;

private:

    std::vector <Animal*> fauna;
    std::vector <Food*> foodSources;
    std::vector <Anthill*> anthills;
    std::vector <Termite_mound*> termitemounds;
    std::vector <Pheromone*> pheromones;

    FoodGenerator foodGenerator;

    bool displayPheromone;
    double temperature;

    std::vector<double> counters;
};