#include <iostream>
#include <fstream>
#include "Loader.hpp"
#include "../Application.hpp"
#include "Food.hpp"
#include "Termite.hpp"
#include "Anthill.hpp"

void loadMap(std::string const& filepath)
{
    std::string line;
    std::ifstream myfile(filepath);

    if(myfile.is_open()) {
        while(std::getline(myfile,line)) {
            std::stringstream view(line) ;
            std::string entity("no entity");
            double x(0);
            double y(0);
            double quantity(0);

            switch (line.front()) {
            case '#' :
                break;
            case 'a' : {
                view >> entity >> x >> y ;
                ToricPosition position(x,y);
                getAppEnv().addAnthill(new Anthill(position));
                break;
            }
            case 'f' : {
                view >> entity >> x >> y >> quantity;
                ToricPosition position(x,y);
                getAppEnv().addFood(new Food(position,quantity));
                break;
            }
            case 't' : {
                view >> entity >> x >> y ;
                ToricPosition position(x,y);
                getAppEnv().addAnimal(new Termite(position));
                break;
            }

            default:
                break;
            }
        }
        myfile.close();
    }
}