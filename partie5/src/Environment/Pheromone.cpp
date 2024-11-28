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
    quantity -= dt.asSeconds()*getAppConfig().pheromone_evaporation_rate;
}

bool Pheromone::isNegligible()const
{
    return quantity < getAppConfig().pheromone_threshold;
}

double Pheromone::getQuantity() const
{
    return quantity;
}

