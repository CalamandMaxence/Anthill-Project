/*
 * POOSV 2020-21
 * @author: Calamand Maxence & Verdillon Marie
 */
#pragma once
#include <string>
#include <map>
#include <memory>
#include <vector>
#include "Graph.hpp"
#include "../Utility/Types.hpp"
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"

class Stats : public Drawable, public Updatable
{
public :

    Stats ();
    ~Stats()
    {
        reset();
    }

    void setActive(int id);
    std::string getCurrentTitle() ;
    void next();
    void previous();
    void reset();
    void drawOn(sf::RenderTarget& target) const;

    /*!
    * @brief Update graphs with fechData from Environment
     */
    void update(sf::Time dt);
    void addGraph(int id,const std::string &title,const std::vector<std::string> &series,double min,double max,const Vec2d &size);

private :
    std::map<int, std::unique_ptr<Graph> > setOfGraphs;
    std::map<int,std::string > setOfNames;

    unsigned int activeIDStats;
    sf::Time timerStats;
};