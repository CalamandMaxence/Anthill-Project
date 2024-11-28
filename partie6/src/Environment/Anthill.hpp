/*
 * POOSV 2020-21
 * @author: Calamand Maxence & Verdillon Marie
 */
#pragma once
#include "../Utility/Utility.hpp"
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"
#include "AntSoldier.hpp"
#include "AntWorker.hpp"


class Anthill : public Positionable, public Drawable, public Updatable
{
public :

    Anthill (ToricPosition anthillPosition );
    ~Anthill();

    void addFoodStock (const Quantity& addedQuantity);

    void drawOn(sf::RenderTarget& target) const override;
    /*!
    * @brief Generate ant after a specific delay
     */
    void update(sf::Time dt) override;

    double getWorkerProb () const;
    Quantity getFoodStock() const ;
    Uid getId() const ;

    /*!
    * @brief Generate an ant following uniform law to know if it generates a worker or soldier
     */
    void generateAnt()const;

private :

    Quantity foodStock;
    const Uid id;
    sf::Time anthillTimer;

};