/*
 * POOSV 2020-21
 * @author: Calamand Maxence & Verdillon Marie
 */

#include "ToricPosition.hpp"
#include <cmath>
#include "../Application.hpp"

ToricPosition::ToricPosition ( const Vec2d& coordonates, const Vec2d& dimensions_monde)
    : coordonates(coordonates),
      worldSize (dimensions_monde)
{
    clamp();
}

ToricPosition::ToricPosition (double x, double y)
    : coordonates(x,y),
      worldSize(getAppConfig().simulation_size,getAppConfig().simulation_size)
{
    clamp();
}

ToricPosition::ToricPosition(const Vec2d& coordonates)
    : coordonates(coordonates),
      worldSize(getAppConfig().simulation_size,getAppConfig().simulation_size)
{
    clamp();
}

ToricPosition::ToricPosition(ToricPosition const& autre)
    : coordonates(autre.coordonates),
      worldSize(autre.worldSize)
{
    clamp();
}

static double myfmod(double x, double y)
{
    x = fmod(x, y);
    if (x < 0.0) x += y;
    return x;
}

void ToricPosition::clamp()
{
    // Clamp the position inside the toric world

    auto const width  = worldSize.x();
    auto const height = worldSize.y();
    coordonates = Vec2d(myfmod(coordonates.x(), width),
                        myfmod(coordonates.y(), height));
    while (coordonates.x() < 0)          coordonates += {width,0};
    while (coordonates.x() >= width)     coordonates -= {width,0};
    while (coordonates.y() < 0)          coordonates += {0,height};
    while (coordonates.y() >= height)    coordonates -= {0,height};
}

bool ToricPosition::operator==(ToricPosition const& other) const
{
    return coordonates == other.coordonates ;
}

void ToricPosition::operator=(ToricPosition const& other)
{
    coordonates = other.coordonates;
    worldSize = other.worldSize;
}

Vec2d const& ToricPosition::toVec2d() const
{
    return coordonates;
}

double ToricPosition::x() const
{
    return coordonates.x() ;
}

double ToricPosition::y() const
{
    return coordonates.y() ;
}

void ToricPosition::operator+= (Vec2d const& other)
{
    coordonates += other;
}

ToricPosition operator+(ToricPosition a, ToricPosition const& b)
{
    ToricPosition v = b;
    a += v.toVec2d();
    return a;
}

std::ostream& operator<< (std::ostream& out,ToricPosition const& object)
{
    out << "[" << object.x() << ", " << object.y() << "]";
    return out;
}

double ToricPosition::operator[] (int index) const
{
    if (index==0) {
        return coordonates.x();
    } else if (index==1) {
        return coordonates.y() ;
    } else {
        std::cout << "Error : index is 0 for x, 1 for y" ;
        return 1;
    }
}

Vec2d ToricPosition::toricVector(ToricPosition const& that)
{

    Vec2d min = that.coordonates;
    Vec2d target = that.coordonates;
    Vec2d w(that.worldSize.x(),0);
    Vec2d h(0,that.worldSize.y());

    double dist = distance(coordonates,min);
    double count1(-1);

    for(int i(1); i<=3; ++i) {
        double count2(-1);

        for(int j(1); j<=3; ++j) {
            Vec2d tmp =  count2*w + count1*h + target;
            if( distance(tmp,coordonates) < dist ) {

                dist = distance(coordonates,tmp);
                min = tmp;
            }
            count2 += 1;
        }
        count1 += 1;
    }
    min = min + -1*coordonates;
    return min;
}

double toricDistance(ToricPosition const& from, ToricPosition const& to)
{
    Vec2d tmp(0,0);
    ToricPosition tmp2 = from;

    return distance(tmp2.toricVector(to), tmp);
}

