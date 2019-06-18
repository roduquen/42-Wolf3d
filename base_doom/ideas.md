## Projet Doom

*Debut : 23 avril*

*Au 4 mai :*

	- Architecture mise en place (design pattern : states machines)
	- Minilibx mise en place
	- Switch entre rendu et parsing

*4 mai :*

	- Choix format jeux de donnees

Header d'un element du jeu : [--[ TEXTURE ]--]
Taille de l'element : un entier suivant le header (nb d'octets)
Quand le parsing lis tout l'element, il doit s'attendre a parser un autre header.

### SECTEURS & MURS

1 point = 1 vertex (x, y)
 -> extraire les points independemment des secteurs.

format parser :

x : float y : float (ecrire les valeurs tel qu'ils seront dans la memoire)

## Liste headers :

[--[ MAP ]--]

(les vertices se succedent les un a la suite des autres)
x y -1 // mur secteur 0
x y -1
x y -1
x y -1
x y 1 // portail secteur 0 -> 1
x y -1
x y -1
x y 0 // portail secteur 1 -> 0

[--[ TEXTURE ]--]

largeur hauteur index_sector
r g b a r g b a r g b a r g b a r g b a
r g b a r g b a ...

Tous les murs d'un secteur auront la meme texture.

Si 1 couple de points connecte est commun a deux secteurs alors c'est un portail
entre les deux secteurs.

Dans l'editeur, on ne pourra apposer un point qu'a l'intersection des traits du quadrillage de la map.
Le trace est fini quand on boucle le tracé (les murs crees en une seule fois font un seul secteur).

**6 mai** : separation controller/fonctionnalites liees aux events.

**Souhait pour la semaine du 6 mai :**

- quadrillage avec zoom
- tracé de ligne dans l'editeur.
- save -> ecriture dans fichier avec murs/secteurs.

## Tracé de ligne :

state 0 : cursor
state 1 : start_point, save start point [click left mouse]
state 2 : move_line, trace line from start point to cursor [image 2]
state 3 : cursor become start point of a new line [on click]
				[old lines saved in image 1]

Dans state 1 :
	si le point sur lequel on lache la souris existe deja
	le tracé se termine, secteur cree avec les points

Dans state 2 :
	effacer image 2 et redessiner line sur image 2
	superposer images 1 et 2

Dans state 3 :
	image 1 = image 1 | image 2

On boucle sur state 3 pendant le tracé.
On revient a state 0 quand le tracé est fini. (new point == start point)

Si le cursor est tres près du start_point, un cercle bleu apparait autour du start point. Cercle rouge si different du start point.

# Scenario :

Click souris, le point se cree, cercle visible.
Deplacement souris, tracé de ligne
Click souris, 2eme point cree, la premiere ligne dessinée save dans image 1
Deplacement souris, tracé de ligne [ligne save dans image 2]
...
Creation point sur start point, fin tracé. state 1 -> state 0
