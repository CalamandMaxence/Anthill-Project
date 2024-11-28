/*
 * POOSV 2020-21
 * @author:
 */

#include "ToricPosition.hpp"
#include <cmath>

void ToricPosition::clamp()
{

    double x;
    double y;

    if (dimensions_monde.x() == 0) {
        std::cout << "Erreur : division par 0" ;
        x=0;
    } else {
        if (fmod(coordonnees.x(),dimensions_monde.x())<0) {
            x = fmod(coordonnees.x(),dimensions_monde.x())+ dimensions_monde.x();
        } else {
            x = fmod(coordonnees.x(),dimensions_monde.x()) ;
        }
    }

    if (dimensions_monde.y() == 0) {
        std::cout << "Erreur : division par 0" ;
        y = 0;
    } else {
        if (fmod(coordonnees.y(),dimensions_monde.y())<0) {
            y = fmod(coordonnees.y(),dimensions_monde.y())+dimensions_monde.y();
        } else {
            y = fmod(coordonnees.y(),dimensions_monde.y()) ;
        }
    }

    Vec2d tmp(x,y);
    coordonnees = tmp;
}

bool ToricPosition::operator==(ToricPosition const& autre)
{
    if(coordonnees == autre.coordonnees ) return true;
    else return false;
}

void ToricPosition::operator=(ToricPosition const& autre)
{
    coordonnees = autre.coordonnees;
    dimensions_monde = autre.dimensions_monde;
}

Vec2d const& ToricPosition::toVec2d()
{
    return coordonnees;
}

double ToricPosition::x() const
{
    return coordonnees.x() ;
}

double ToricPosition::y() const
{
    return coordonnees.y() ;
}

void ToricPosition::operator+= (Vec2d const& autre)
{
    coordonnees += autre;
}

ToricPosition operator+(ToricPosition a, ToricPosition const& b)
{
    ToricPosition v = b;
    a += v.toVec2d();
    return a;
}

std::ostream& operator<< (std::ostream& sortie,ToricPosition const& objet)
{
    sortie << "[" << objet.x() << ", " << objet.y() << "]";
    return sortie;
}

double ToricPosition::operator[] (int index) const
{
    if (index==0) {
        return coordonnees.x();
    } else if (index==1) {
        return coordonnees.y() ;
    } else {
        std::cout << "Erreur : index différent de 1 ou 0" ;
        return 1;
    }
}

Vec2d ToricPosition::toricVector(ToricPosition const& that)
{

    Vec2d min = that.coordonnees;
    Vec2d cible = that.coordonnees;
    Vec2d w(that.dimensions_monde.x(),0);
    Vec2d h(0,that.dimensions_monde.y());

    double dist = distance(coordonnees,min);
    double count1(-1);

    for(int i(1); i<=3; ++i) {
        double count2(-1);

        for(int j(1); j<=3; ++j) {
            Vec2d tmp =  count2*w + count1*h + cible;
            if( distance(tmp,coordonnees) < dist ) {

                dist = distance(coordonnees,tmp);
                min = tmp;                                                          // attention commenter ?
            }
            count2 += 1;
        }
        count1 += 1;
    }
    min = min + -1*coordonnees;
    return min;
}

double toricDistance(ToricPosition const& from, ToricPosition const& to)
{
    Vec2d tmp(0,0);
    ToricPosition tmp2 = from;

    return distance(tmp2.toricVector(to), tmp);                            // attention commenter ?
}



