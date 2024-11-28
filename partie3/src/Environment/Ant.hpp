/*
 * POOSV 2020-21
 * @author: Calamand Maxence & Verdillon Marie
 */
#pragma once
#include "Animal.hpp"
#include "../Utility/Types.hpp"
#include "Pheromone.hpp"

class Ant : public Animal
{

public:

    //Constructeur

    Ant (ToricPosition positionFourmi = {0,0}, Uid fourmiliere = 0, double pointdevie = 1, double esperance = 100, Pheromone* lastPheromone = new Pheromone({0,0},0) );

    //Methodes

    double getSpeed() const override;

    void drawOnAnt(sf::RenderTarget& target, sf::Texture texture) const;

    /*!
    * @brief Create the right amount of pheromones between the last one created
     *
     * @note Calculate the number of instances of pheromones to create thanks to the distance to the last pheromone created
     */
    void spreadPheromones();

    /*!
    * @brief Display the probabilities to rotate
     */
    void debugProba(sf::RenderTarget& target) const;

    /*!
    * @brief Calculate the probabilities to rotate based on the quantity of pheromones around the ant
     */
    RotationProbs computeRotationProbs() const override;

    void setDirectionUturn();

    Uid getAssociatedAnthill ()const;

private :

    const Uid associatedAnthill;
    Pheromone* lastPheromone;
    //Anthill* homeAnthill;
};