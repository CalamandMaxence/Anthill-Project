#include "Anthill.hpp"
#include "Random/Random.hpp"
#include "../Application.hpp"

Anthill::Anthill (ToricPosition positionFourmiliere )
    : Positionable (positionFourmiliere),stockNourriture (0.0),identifiant (createUid()),compteurFourmiliere(sf::Time::Zero)
{
    generateAnt();
}

void Anthill::drawOn(sf::RenderTarget& target) const
{
    auto const anthillSprite = buildSprite(getPosition().toVec2d(), 75,getAppTexture(getAppConfig().anthill_texture));
    target.draw(anthillSprite);

    if(isDebugOn()) {
        Vec2d d1 = {0,50};
        Vec2d d2 = {0,70};
        auto const text1 = buildText( to_nice_string(this->stockNourriture), getPosition().toVec2d() + d1, getAppFont(), 15, sf::Color::Black);
        target.draw(text1);
        auto const text2 = buildText( to_nice_string(this->identifiant), getPosition().toVec2d() + d2, getAppFont(), 15, sf::Color::Magenta);
        target.draw(text2);
    }
}

void Anthill::update(sf::Time dt)
{

    compteurFourmiliere+=dt;
    if (sf::seconds(getAppConfig().anthill_spawn_delay) < compteurFourmiliere)  {
        compteurFourmiliere = sf::Time::Zero;
        generateAnt();
    }
}


//Getters
Quantity Anthill::getStockNourriture() const
{
    return stockNourriture ;
}

Uid Anthill::getIdentifiant() const
{
    return identifiant;
}

double Anthill:: getProbabiliteSortieOuvriere () const
{
    return getAppConfig().anthill_worker_prob_default ;
}

void Anthill::addStockNourriture (Quantity quantite)
{
    stockNourriture += quantite;
}

Anthill* getAnthillfromUid(Uid identifiant)
{
    for ( auto fourmiliere : getAppEnv().getEnsembleFourmilieres()) {
        if (identifiant== fourmiliere->getIdentifiant()) {
            return fourmiliere;
        }
    }
    return nullptr ;
}

void Anthill::generateAnt()const
{
    double probabilite = uniform(0,1);

    if (probabilite<=getProbabiliteSortieOuvriere()) {
        AntWorker* nouvelleOuvriere = new AntWorker(getPosition(),getIdentifiant());
        getAppEnv().addAnimal(nouvelleOuvriere);
    } else {
        AntSoldier* nouvelleSoldate = new AntSoldier(getPosition(),getIdentifiant());
        getAppEnv().addAnimal(nouvelleSoldate);
    }
}
