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

    Ant (ToricPosition antPosition = {0,0}, Uid anthillId = 0, double hp = 1, double lifespan = 100, Pheromone* lastPheromone = new Pheromone({0,0},0) );

    virtual ~Ant() {}


    double getSpeed() const override;

    /*!
    * @brief draw all types of ants
     */
    void drawOnAnt(sf::RenderTarget& target, const sf::Texture& texture) const;

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

    void setDirectionUTurn();

    Uid getAssociatedAnthill ()const;

    /*!
    * @brief All boolean methods below computes if the other animal is an enemy
     */
    bool isEnemy (Animal const* animal) const override;
    bool isEnemyDispatch (Termite const* other) const override;
    bool isEnemyDispatch(Ant const* other) const override;

private :

    const Uid associatedAnthill;
    Pheromone* lastPheromone;
};