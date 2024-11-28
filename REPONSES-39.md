==========================================================================================================================
## Projet 2020-21 « Fourmis : simulation d’un système auto-organisé »

## Réponses aux questions

* Partie 1
Q1.1 : Le constructeur par défaut est inclus dans celui qui prend deux paramètres double.
Q1.2 : Nous avons choisi une surcharge externe pour l’opérateur + car il est moins proche de la classe ToricPosition que l’opérateur +=, qui est lui en surcharge interne.
Q1.3 : Nous avons choisi une surcharge externe pour l’opérateur << car il modifie le flot et a besoin d’un objet en paramètre : c’est une surcharge de type operateurOp (argument1, argument2).
Q1.5 : C’est une combinaison linéaire des vecteurs (0,h) et (w,0) pour les valeurs, -1,0,1, additionnés au vecteur that : une double boucle for nous évite de dupliquer du code.
Q1.6 : La surcharge de l’opérateur << se fait à l’aide de la méthode display.

* Partie 2
Q2.1 : Il parait judicieux de déclarer la méthode drawOn comme const, parce qu’elle affiche sans modifier.
Q2.2 : Il faut enlever le constructeur de copie.
Q2.3 : Il faut détruire tout ce que l’environnement contient avant de le détruire, ce qui est fait par la méthode reset, appelée dans le destructeur. 
Q2.4 : La classe Food hérite de la classe Positionnable.
Q2.5 : C’est pour bien modéliser les liens sémantiques associés à cette quantité. 
Q2.6 : Il faut coder la méthode update et drawOn de la classe Environment. 
Q2.7 : A ce moment, nous avons une méthode publique getSpeed et les attributs : pv, angle de direction et espérance de vie.
La classe hérite aussi de toutes les caractéristiques de la classe Positionnable.

Q2.8 : SetDirection. de par ses contraintes, est une méthode protégée. Cela améliore l’encapsulation car uniquement les classes filles peuvent y accéder. 
Q2.9 : Il faut modifier la méthode drawOn de la classe Environment. 
Q2.10 : Il faut modifier la méthode update de la classe Environment.
Q2.11 : Il faut modifier la méthode update de la classe Environment.

* Partie 3
Q3.1 :	Animal, Pheromone et Anthill hérite de Updatable et Drawable, Food hérite de Drawable, Foodgenerator hérite de Updatable. Cela permet de ne pas redéfinir la même fonction si elle est utilisée de la même manière dans plusieurs classes.  
Q3.2 : Nous avons déclaré la fonction getSpeed comme virtuelle pure dans la classe Animal.
Q3.3 : Nous avons déplacé la méthode drawOn dans la classe Ant et on y fait appel dans les classes AntWorker et AntSoldier,
Q3.4 :	Non.
Q3.5 : C’est important pour pouvoir utiliser le polymorphisme.
Q3.6 : Nous avons redéfini les méthodes drawOn et update, codé la fonction addStockNouriture, et ajouté les deux attributs demandés de type Quantity et Uid.
Q3.7 : Les méthodes drawOn, update et reset doivent subir des modifications.
Q3.8 : La génération automatique est implémentée dans la fonction update de la classe Anthill.
Q3.9 : Nous avons choisi de traiter le comportement des fourmis ouvrières dans leur fonction update.
Q3.10 : Nous avons utilisé les méthodes getAnthillForAnt et getClosestFoodForAnt dans la fonction update de AntWorker.
Q3.11 : A ce stade nous avons une classe Pheromone ayant hérité d’une position et des méthodes drawOn et update redéfinies pour un affichage personnalisé. De plus, cette classe possède un attribut Quantity et une méthode de type bool indiquant si cette quantité est négligeable.
Q3.12 : Nous avons décidé d’ajouter un attribut de type pointeur sur la dernière instance de phéromone créée. 
Q3.13 : Suite à l’ajout des phéromones, il faut modifier les méthodes update, drawOn et reset de la classe Environment. 

* Partie 4
Q4.1 : Cette vitesse est utilisée par la méthode getSpeed qui est une méthode virtuelle.
Q4.2 : Elle hérite de la classe Animal, a un constructeur qui prend un ToricPosition en paramètre, deux fonctions utiles pour l’affichage et une méthode getSpeed, ainsi qu’une méthode update.
Q4.3 : Lors de l’exécution, on ne sait pas si le type va varier et donc potentiellement causer des erreurs.
Q4.4 : Nous avons choisi de modéliser l’attitude des animaux en utilisant un type énuméré.  
Q4.5 : Nous avons défini les méthodes qui feront des dégâts dans la classe Animal et ayant comme paramètre la force de l’animal en question. 
Q4.6 : On se sert du polymorphisme de la méthode update afin de gérer les différents « attack_delay ».
Q4.7 : Nous avons ajouté la méthode getClosestEnnemy à la classe Environment afin de pouvoir itérer sur tous les animaux présents de manière efficace. 
Q4.8 : On augmente le timer lorsque le mode attack est activé et une fois un certain temps dépassé, on repasse en mode Idle et le mode Attack s’active seulement lorsque le timer a dépassé « l’ant attack delay ».
 
* Partie 5
Q5.1 : Nous avons choisi d’utiliser une map pour lier un int avec un graphe et une autre map pour lier un int et une string, pour le nom du graphe.
Q5.2 : Pour compter les instances d’une classe, nous avons décidé de créer un vector de int dans la classe Environment, chaque case du vector représentant le compteur d’une classe (une case pour les soldats, une pour les ouvrières, une pour les food et une pour les termites). Nous avons également créé deux méthodes pour incrémenter et décrémenter les compteurs, qui sont appelées dans les constructeurs et destructeurs des classes.



