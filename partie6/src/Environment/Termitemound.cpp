#include "Termitemound.hpp"
#include "../Application.hpp"

Termite_mound::Termite_mound (ToricPosition anthillPosition )
    : Positionable (anthillPosition),termitemoundTimer(sf::Time::Zero)
{
    generateTermite();
}

Termite_mound::~Termite_mound() {}

void Termite_mound::drawOn(sf::RenderTarget& target) const
{
    Vec2d d = {-40,-60};
    auto const anthillSprite = buildSprite(getPosition().toVec2d() + d, 200,getAppTexture(getAppConfig().termitemound_texture));
    target.draw(anthillSprite);
}

void Termite_mound::update(sf::Time dt)
{
    termitemoundTimer+=dt;
    if ( getAppConfig().termitemound_spawn_delay < termitemoundTimer.asSeconds())  {
        termitemoundTimer = sf::Time::Zero;
        generateTermite();
    }
}

void Termite_mound::generateTermite()const
{
    Termite* newTermite = new Termite(getPosition());
    getAppEnv().addAnimal(newTermite);
}