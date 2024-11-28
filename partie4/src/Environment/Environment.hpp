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
#include "Pheromone.hpp"


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
    void addAnthill(Anthill* newAntHill);
    void addPheromone(Pheromone* newPheromone);

    /*!
     * @note Takes care of supressing dead animals, empty foods and evaporate pheromones
     */
    void update(sf::Time dt);
    void drawOn(sf::RenderTarget& targetWindow) const;

    void reset();
    bool togglePheromoneDisplay();

    //Getters

    /*!
    * @brief Get the pheromone quantity around the ant
     */
    Quantities getPheromoneQuantitiesPerIntervalForAnt(const ToricPosition &position,Angle direction_rad,const Intervals &angles);

    /*!
    * @brief Get the closest food in the viewing range of the ant
     */
    Food* getClosestFoodForAnt (ToricPosition const& position);

    std::vector<Food*> getSourcesNourriture() const;
    std::vector<Anthill*> getEnsembleFourmilieres() const ;
    Anthill* getAnthillForAnt (ToricPosition const& position, Uid anthillId);
    Animal* getClosestEnemy (Animal* seekingAnimal) const;

private:

    std::vector <Animal*> faune;
    std::vector <Food*> sourcesNourriture;
    std::vector <Anthill*> antHills;
    std::vector <Pheromone*> pheromones;

    FoodGenerator foodGenerator;

    bool displayPheromone;

};