/*
 * POOSV 2020-21
 * @author: Calamand Maxence & Verdillon Marie
 */

#include "ToricPosition.hpp"
#include <cmath>
#include "../Application.hpp"

ToricPosition::ToricPosition ( const Vec2d& coordonnees, const Vec2d& dimensions_monde)
    : coordonnees(coordonnees),
      worldSize (dimensions_monde)
{
    clamp();
}

ToricPosition::ToricPosition (double x, double y)
    : coordonnees(x,y),
      worldSize(getAppConfig().simulation_size,getAppConfig().simulation_size)
{
    clamp();
}

ToricPosition::ToricPosition(const Vec2d& coordonnees)
    : coordonnees(coordonnees),
      worldSize(getAppConfig().simulation_size,getAppConfig().simulation_size)
{
    clamp();
}

ToricPosition::ToricPosition(ToricPosition const& autre)
    : coordonnees(autre.coordonnees),
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
    coordonnees = Vec2d(myfmod(coordonnees.x(), width),
                        myfmod(coordonnees.y(), height));
    while (coordonnees.x() < 0)          coordonnees += {width,0};
    while (coordonnees.x() >= width)     coordonnees -= {width,0};
    while (coordonnees.y() < 0)          coordonnees += {0,height};
    while (coordonnees.y() >= height)    coordonnees -= {0,height};
}

bool ToricPosition::operator==(ToricPosition const& autre) const
{
    return coordonnees == autre.coordonnees ;
}

void ToricPosition::operator=(ToricPosition const& autre)
{
    coordonnees = autre.coordonnees;
    worldSize = autre.worldSize;
}

Vec2d const& ToricPosition::toVec2d() const
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
    Vec2d w(that.worldSize.x(),0);
    Vec2d h(0,that.worldSize.y());

    double dist = distance(coordonnees,min);
    double count1(-1);

    for(int i(1); i<=3; ++i) {
        double count2(-1);

        for(int j(1); j<=3; ++j) {
            Vec2d tmp =  count2*w + count1*h + cible;               //combinaisons linéaires de (w,0) et (0,h) pour les valeurs 0,1,-1 ajoutés a la cible
            if( distance(tmp,coordonnees) < dist ) {

                dist = distance(coordonnees,tmp);
                min = tmp;
            }
            count2 += 1;
        }
        count1 += 1;
    }
    min = min + -1*coordonnees;                                     //retourne le vecteur depuis le point de départ
    return min;
}

double toricDistance(ToricPosition const& from, ToricPosition const& to)
{
    Vec2d tmp(0,0);
    ToricPosition tmp2 = from;

    return distance(tmp2.toricVector(to), tmp);                       //retourne la distance entre le vecteur déjà décrémenté et l'origine
}

