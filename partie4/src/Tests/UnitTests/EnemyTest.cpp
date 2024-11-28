/*
* POOSV 2020-21
* Marco Antognini & Jamila Sam
*/

#include <Application.hpp>
#include <Environment/Ant.hpp>
#include <Environment/AntWorker.hpp>
#include <Environment/AntSoldier.hpp>
#include <Environment/Termite.hpp>
#include <Environment/Animal.hpp>
#include <Utility/Utility.hpp>
#include <Config.hpp>
#include <catch.hpp>
#include <iostream>
#include <vector>

SCENARIO("Ant vs Ant", "[AntWorker][AntSoldier")
{

    // Create a few entities
    Uid id1 = createUid();
    Uid id2 = createUid();
    std::vector<Animal*> colony1;
    std::vector<Animal*> colony2;

    colony1.push_back(new AntSoldier({0, 0}, id1));
    colony1.push_back(new AntWorker({0, 0}, id1));
    colony2.push_back(new AntSoldier({0, 0}, id2));
    colony2.push_back(new AntWorker({0, 0}, id2));

    GIVEN("a single worker/soldier ant") {
        THEN("no self destruction") {
            CHECK_FALSE(colony1[0]->isEnemy(colony1[0]));
            CHECK_FALSE(colony1[1]->isEnemy(colony1[1]));
            CHECK_FALSE(colony2[0]->isEnemy(colony2[0]));
            CHECK_FALSE(colony2[1]->isEnemy(colony2[1]));
        }
    }

    GIVEN("two ants from the same colony") {
        THEN("no treason") {
            for (auto* animal1 : colony1) {
                for (auto* animal2 : colony1) {
                    CHECK_FALSE(animal1->isEnemy(animal2));
                    CHECK_FALSE(animal2->isEnemy(animal1));
                }
            }
        }

    }


    GIVEN("two ants from different colonies") {

        THEN("they are ennemies") {
            for (auto* animal1 : colony1) {
                for (auto* animal2 : colony2) {
                    CHECK(animal1->isEnemy(animal2));
                    CHECK(animal2->isEnemy(animal1));
                }
            }

        }

    }

    for (auto* animal : colony1) {
        delete animal;
    }
    for (auto* animal : colony2) {
        delete animal;
    }
}

SCENARIO("Ant vs Termite", "[AntWorker][AntSoldier][Termite")
{

    // Create a few entities
    Uid id1 = createUid();
    Uid id2 = createUid();
    std::vector<Animal*> colony1;
    std::vector<Animal*> colony2;
    std::vector<Animal*> termites;

    colony1.push_back(new AntSoldier({0, 0}, id1));
    colony1.push_back(new AntWorker({0, 0}, id1));
    colony2.push_back(new AntSoldier({0, 0}, id2));
    colony2.push_back(new AntWorker({0, 0}, id2));
    termites.push_back(new Termite({0,0}));
    termites.push_back(new Termite({0,0}));

    GIVEN("a single termite") {
        THEN("no self destruction") {
            for (auto* animal1 : termites) {
                for (auto* animal2 : termites) {
                    CHECK_FALSE(animal1->isEnemy(animal2));
                    CHECK_FALSE(animal2->isEnemy(animal1));
                }
            }
        }
    }

    GIVEN("two termites") {
        THEN("no treason") {
            for (auto* animal1 : termites) {
                for (auto* animal2 : termites) {
                    CHECK_FALSE(animal1->isEnemy(animal2));
                    CHECK_FALSE(animal2->isEnemy(animal1));
                }
            }
        }
    }
    GIVEN("a termite and an ant") {

        THEN("they are ennemies") {
            for (auto* animal1 : termites) {
                for (auto* animal2 : colony1) {
                    CHECK(animal1->isEnemy(animal2));
                    CHECK(animal2->isEnemy(animal1));
                }
            }
            for (auto* animal1 : termites) {
                for (auto* animal2 : colony2) {
                    CHECK(animal1->isEnemy(animal2));
                    CHECK(animal2->isEnemy(animal1));
                }
            }
        }

    }
    for (auto* animal : termites) {
        delete animal;
    }
    for (auto* animal : colony1) {
        delete animal;
    }
    for (auto* animal : colony2) {
        delete animal;
    }
}


