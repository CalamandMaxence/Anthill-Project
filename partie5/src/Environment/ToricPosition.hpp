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

    ToricPosition (const Vec2d& coordonates, const Vec2d& worldSize);

    ToricPosition (double x = 0, double y = 0);

    ToricPosition(const Vec2d& coordonates);

    ToricPosition(ToricPosition const& other);


    double x() const;
    double y() const;

    bool operator==(ToricPosition const& other) const;
    void operator+= (Vec2d const& other);
    void operator=(ToricPosition const& other);
    double operator[](int index) const;

    /*!
    * @brief Return the smallest path to the target (argument that)
     *
     * @note Evaluate the distance between the current instance and the target
     * increased by all linear combination of (w,0) and (h,0) for 0,1,-1
     */
    Vec2d toricVector(ToricPosition const& that);

    Vec2d const& toVec2d() const;

private :

    Vec2d coordonates;
    Vec2d worldSize;

    /*!
     * @brief Project the coordonates in the Toric world
     *
     * @note If the world dimension is 0, project on (0,0)
     */
    void clamp();
};

std::ostream& operator<<(std::ostream& out,ToricPosition const& object);
ToricPosition operator+(ToricPosition a, ToricPosition const& b);

/*!
 * @brief using toricVector to find the smallest path and return the distance
 *
 */
double toricDistance(ToricPosition const& from, ToricPosition const& to);
