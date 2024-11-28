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

    //Constructeur

    Anthill (ToricPosition positionFourmiliere );

    //Methodes

    void addStockNourriture (Quantity quantite);

    void drawOn(sf::RenderTarget& target) const override;
    void update(sf::Time dt) override;

    //Getter
    double getProbabiliteSortieOuvriere () const;
    Quantity getStockNourriture() const ;
    Uid getIdentifiant() const ;
    void generateAnt()const;

private :

    Quantity stockNourriture;
    const Uid identifiant;
    sf::Time compteurFourmiliere;

};

/*!
* @brief Return the anthill associated to the parameter
*/
Anthill* getAnthillfromUid(Uid identifiant);