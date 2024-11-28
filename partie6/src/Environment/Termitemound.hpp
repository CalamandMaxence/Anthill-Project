/*
 * POOSV 2020-21
 * @author: Calamand Maxence & Verdillon Marie
 */
#pragma once
#include "../Utility/Utility.hpp"
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"
#include "Termite.hpp"

class Termite_mound : public Positionable, public Drawable, public Updatable
{
public :

    Termite_mound (ToricPosition termitemoundPosition );
    ~Termite_mound();

    /*!
    * @brief Draw the termite mound so the termite generated appear at the entry
     */
    void drawOn(sf::RenderTarget& target) const override;
    /*!
    * @brief Generate termites after a specific delay
     */
    void update(sf::Time dt) override;

    /*!
    * @brief Generate an termite
     */
    void generateTermite()const;

private :

    sf::Time termitemoundTimer;

};