#include "Food.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"


Quantity Food::takeQuantity (Quantity const aPrelever)
{

    Quantity Quantiteprelevee;

    if (quantite >= aPrelever) {
        quantite -= aPrelever;
        Quantiteprelevee = aPrelever;

    }
    if (quantite < aPrelever) {
        Quantiteprelevee = quantite;
        quantite = 0;
    }

    return Quantiteprelevee;
}

void Food::drawOn(sf::RenderTarget& target) const
{
    auto const foodSprite = buildSprite(getPosition().toVec2d(), this->quantite*1/2, getAppTexture(getAppConfig().food_texture));
    target.draw(foodSprite);

    if (isDebugOn()) {
        auto const text = buildText( to_nice_string(this->quantite), getPosition().toVec2d(), getAppFont(), 15, sf::Color::Black);
        target.draw(text);
    }
}

bool Food::isEmpty() const
{
    if(quantite == 0) return true;

    return false;
}