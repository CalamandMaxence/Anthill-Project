==========================================================================================================================
## Projet 2020-21 « Fourmis : simulation d’un système auto-organisé »

## Journal

* Semaine 1 (15.03) : 
Nous avons codé la majorité de la partie 1, cependant il reste un problème avec la méthode toricVector de la classe ToricPosition. Nous observons que chaque retour de la méthode toricVector a +500 dans chaque coordonnée par rapport au résultat attendu. 
Les tests de la classe Positionnable sont tous réussis.
On ne comprend pas encore la manière attendue pour commenter le code.

* Semaine 2 (22.03) :
Le problème concernant toricVector a été résolu lors de la séance d’exercice. Finalisation de la partie 1. 
Nous avons commencé à coder la partie 2. Les bases des modules « Lieu de vie » et « Déambulations »  sont codées.

* Semaine 3 (29.03) :
Nous avons codé les méthodes des classes de la partie 2 plus en détails, l’affichage ne fonctionne pas car nous n’avions pas encore défini les méthodes drawOn et update de Environment. 

* Semaine 4 (5.04) :
Les méthodes drawOn et update de Environment sont désormais codées, comme les méthodes move et update de Animal. FoodGenerator ne marche pas et lors de l’exécution, l’affichage des fourmis ne marche pas, elles restent immobiles dans les coins, peu importe l’endroit où on les génère.  

* Semaine 5 (12.04) :
Le problème de FoodGenerator est réglé. Le problème d’affichage des fourmis est réglé et nous avons pu détecter et corriger les problèmes des fonctions move et update de Animal. La partie 2 est bientôt finalisée.

* Semaine 6 (19.04) :
La partie 2 est finalisée. Les parties 3.1 et 3.2 ont été codées en majorité. Il y a un problème avec la détection des phéromones par les fourmis, les probabilités de déplacement et la détection des sources de nourriture.

* Semaine 7 (26.04) :
Le problème de la détection des sources de nourriture et des probabilités de déplacement selon les phéromones ont été réglé lors de la séance d’exercice. La partie 3 est finalisée. On commence à coder la partie 4.

* Semaine 8 (3.05) :
La partie 4 est codée en majorité, il reste des problèmes avec la gestion des combats (Segmentation fault 11) . Nous avons aussi un problème avec une variable déclarée, et non utilisée selon le compilateur, mais une fois que nous la supprimons, l’exécution crash.

* Semaine 9 (10.05) :
Suite à la séance d’exercices, nous avons pu régler les problèmes de la semaine 8 et nous avons finalisé la partie 4. Nous avons commencé à coder la partie 5. Il y a un problème avec une nouvelle Segmentation fault due à l’utilisation d’un pointeur ou d’un vecteur.

* Semaine 10 (17.05) :
La segmentation fault ainsi qu’un problème quant à la conception des attributs de la classe Stats ont été résolus, nous sommes en train de débugger la partie 5. Il y a aussi des problèmes avec le chargement des maps et les graphes de food et anthills qui ne s’affichent pas.

* Semaine 11 (24.05) :
Les problèmes de LoadMap et d'affichage des graphs de Anthill sont résolus. Nous avons créé une classe Termite_mound générant des Termites en extension.