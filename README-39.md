=========================================================================================================================
La simulation informatique des colonies de fourmis vise a modéliser la vie de plusieurs colonies, en prenant en compte leurs intercactions entre les différentes entités composant la faune de notre simulation.

L'environnement est composé d'un ensemble de sources de nourriture générées aléatoirement, un ensemble d'animaux et un ensemble de fourmilières.

Toutes les fourmis libèrent des phéromones et se déplacent selon la densité de pheromones les entourant.
Les fourmis sont spécialisés en 2 classes : Worker et Soldier, l'une récolte de la nourriture et la ramène a sa fourmilière, l'autre combat les ennemis (fourmis venant d'une autre fourmilière et termites).

Les termites composent les prédateurs des fourmis et se déplacent aléatoirement et chassent les fourmies.

## Compilation et Execution

Ce projet utilise [Cmake](https://cmake.org/) pour compiler.

*en ligne de commande :
    - dans le dossier build : cmake ../src
    - make "nom cible" pour générer la cible

*dans QTCreator
    - mise en place du projet : ouvrir le fichier src/CMakeLists.txt
    - choisir la cible à executer

## Cibles Principales

*application -> correspond a l'application finale
*enemytest -> vérifie les relations ami/ennemie entre entités
*anthilltest -> vérifie la génération des fourmilières 
*...

## Commandes

Les différentes commandes sont données dans le panneau d'aide à droite de la simulation.

### Modifications de conception

Le codage du projet à été réalisé en adéquation avec l'énnoncé.

### Extensions

Nous avons créé une classe termitière (Termite_mound) pouvant générer automatiquement des termites afin d'avoir un environement plus complet.