/*
 * POOSV 2020-21
 * @author: Calamand Maxence & Verdillon Marie
 */

#pragma once
#include <utility>
#include <iostream>
#include "../Utility/Vec2d.hpp"


/*!
 * @brief Handle toric coordinate, distance and other
 * basic math operation in a toric world
 *
 * @note Gets the dimensions of the world from getAppConfig()
 */

class ToricPosition
{
public :

    //Constructeurs
    ToricPosition (const Vec2d& coordonnees, const Vec2d& dimensions_monde);

    ToricPosition (double x = 0, double y = 0);

    ToricPosition(const Vec2d& coordonnees);

    ToricPosition(ToricPosition const& autre);

    //Getters
    double x() const;
    double y() const;

    //Operators
    bool operator==(ToricPosition const& autre) const;
    void operator+= (Vec2d const& autre);
    void operator=(ToricPosition const& b);
    double operator[](int index) const;

    //Méthodes

    /*!
    * @brief Return the smallest path to the target (argument that)
     *
     * @note Evaluate the distance between the current instance and the target
     * increased by all linear combination of (w,0) and (h,0) for 0,1,-1
     */
    Vec2d toricVector(ToricPosition const& that);

    Vec2d const& toVec2d() const;

private :

    Vec2d coordonnees;
    Vec2d worldSize;

    /*!
     * @brief Project the coordonates in the Toric world
     *
     * @note If the world dimension is 0, project on (0,0)
     */
    void clamp();
};

std::ostream& operator<<(std::ostream& sortie,ToricPosition const& objet);
ToricPosition operator+(ToricPosition a, ToricPosition const& b);

/*!
 * @brief using toricVector to find the smallest path and return the distance
 *
 */
double toricDistance(ToricPosition const& from, ToricPosition const& to);
