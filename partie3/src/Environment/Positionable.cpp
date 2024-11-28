/*
 * POOSV 2020-21
 * @author:
 */

#include "Positionable.hpp"

ToricPosition const& Positionable::getPosition() const
{
    return position;
}

void Positionable::setPosition(const ToricPosition& position)
{
    this-> position = position;
}

std::ostream& operator<<(std::ostream& out,Positionable p)
{
    return p.display(out);												//on se sert de la methode display pour éviter les répétitions + bonne encapsulation
}

std::ostream& Positionable::display(std::ostream& out) const
{
    out << position ;
    return out;
}