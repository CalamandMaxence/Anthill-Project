#include "Stats.hpp"
#include "Application.hpp"

Stats::Stats():
    activeIDStats (0),
    timerStats (sf::Time::Zero)
{}

void Stats::setActive (int id)
{
    activeIDStats = id;
}

std::string Stats::getCurrentTitle()
{
    if (not setOfNames.empty()) {
        return setOfNames[activeIDStats] ;
    } else return "no name ";
}

void Stats::next()
{
    if (activeIDStats == (setOfNames.size()-1)) {
        activeIDStats=0;
    } else {
        ++activeIDStats;
    }
}

void Stats::previous()
{
    if (activeIDStats == 0) {
        activeIDStats = (setOfNames.size()-1) ;
    } else {
        --activeIDStats;
    }
}

void Stats::reset()
{
    for (auto& graph : setOfGraphs) {
        graph.second->reset();
    }
}

void Stats::addGraph (int id, const std::string &title, const std::vector<std::string> &series, double min, double max, const Vec2d &size)
{
    setOfNames[id] = title;
    setOfGraphs[id].reset (new Graph(series, size, min, max));

    activeIDStats = id;
}

void Stats::drawOn(sf::RenderTarget& target) const
{
    if(setOfGraphs.at(activeIDStats) != nullptr) {
        setOfGraphs.at(activeIDStats)->drawOn(target);
    }
}

void Stats::update(sf::Time dt)
{
    timerStats += dt;

    if (getAppConfig().stats_refresh_rate < timerStats.asSeconds() ) {
        for(size_t i(0); i < setOfGraphs.size(); ++i) {
            setOfGraphs[i]->updateData(sf::seconds(getAppConfig().stats_refresh_rate),getAppEnv().fetchData(setOfNames[i]));

        }
        timerStats = sf::Time::Zero;
    }
}

