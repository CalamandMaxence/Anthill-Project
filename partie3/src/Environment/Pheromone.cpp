#include "Pheromone.hpp"
#include "../Application.hpp"
#include "Utility/Utility.hpp"

void Pheromone::drawOn(sf::RenderTarget& target) const
{
    sf::Color g = sf::Color::Green;
    g.a /= 4;
    target.draw(buildCircle(getPosition().toVec2d(), 5,g));
}

void Pheromone::update(sf::Time dt)
{
    quantite -= dt.asSeconds()*getAppConfig().pheromone_evaporation_rate;
}

bool Pheromone::isNegligible()
{
    if(quantite < getAppConfig().pheromone_threshold) return true;
    return false;
}

double Pheromone::getQuantity() const
{
    return quantite;
}

