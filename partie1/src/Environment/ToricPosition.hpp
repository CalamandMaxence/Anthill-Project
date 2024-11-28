/*
 * POOSV 2020-21
 * @author:
 */

#pragma once
#include <utility>
#include <iostream>
#include "../Utility/Vec2d.hpp"
#include "../Application.hpp"

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
    ToricPosition ( const Vec2d& coordonnees, const Vec2d& dimensions_monde)
        : coordonnees(coordonnees),
          dimensions_monde (dimensions_monde)
    {
        clamp();
    }

    ToricPosition (double x = 0, double y = 0)
        : coordonnees(x,y),
          dimensions_monde(getAppConfig().simulation_size,getAppConfig().simulation_size)
    {
        clamp();
    }

    ToricPosition(const Vec2d& coordonnees)
        : coordonnees(coordonnees),
          dimensions_monde(getAppConfig().simulation_size,getAppConfig().simulation_size)
    {
        clamp();
    }

    ToricPosition(ToricPosition const& autre)
        : coordonnees(autre.coordonnees),
          dimensions_monde(autre.dimensions_monde)
    {}

    //Getters
    double x() const;
    double y() const;

    //Operators
    bool operator==(ToricPosition const& autre);
    void operator+= (Vec2d const& autre)  ;
    void operator=(ToricPosition const& b);
    double operator[](int index) const;

    //Méthodes
    Vec2d toricVector(ToricPosition const& that);
    Vec2d const& toVec2d();

private :

    Vec2d coordonnees;
    Vec2d dimensions_monde;
    void clamp();
};

std::ostream& operator<<(std::ostream& sortie,ToricPosition const& objet);
ToricPosition operator+(ToricPosition a, ToricPosition const& b);

double toricDistance(ToricPosition const& from, ToricPosition const& to);
