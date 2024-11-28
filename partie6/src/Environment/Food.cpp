#include "Food.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"

Food::Food(Positionable foodPosition, Quantity quantity): Positionable(foodPosition), quantity(quantity)
{
    getAppEnv().incrementCounters(food);
}

Food::Food(Vec2d position, double quantity):Positionable(position.x(),position.y()),quantity(quantity)
{
    getAppEnv().incrementCounters(food);
}

Food::~Food()
{
    getAppEnv().decrementCounters(food);
}

Quantity Food::takeQuantity (Quantity const toTake)
{

    Quantity quantityTaken;

    if (quantity >= toTake) {
        quantity -= toTake;
        quantityTaken = toTake;

    }
    if (quantity < toTake) {
        quantityTaken = quantity;
        quantity = 0;
    }

    return quantityTaken;
}

void Food::drawOn(sf::RenderTarget& target) const
{
    auto const foodSprite = buildSprite(getPosition().toVec2d(), this->quantity*1/2, getAppTexture(getAppConfig().food_texture));
    target.draw(foodSprite);

    if (isDebugOn()) {
        auto const text = buildText( to_nice_string(this->quantity), getPosition().toVec2d(), getAppFont(), 15, sf::Color::Black);
        target.draw(text);
    }
}

bool Food::isEmpty() const
{
    return quantity == 0;
}

Quantity Food::getQuantity() const
{
    return quantity;
}