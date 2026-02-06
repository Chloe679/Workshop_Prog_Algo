# 🐣 S1 | Prog: Workshop

## Workshop prog algo - Chloé CHABAUD

### Exercice n°1 : Ne garder que le vert

Mettre le bleu et le rouge à 0.

![](./output/greenImage.png)

---

### Exercice n°2 : Échanger les canaux

Avec swap.

![](./output/swichCanal.png)

---

### Exercice n°3 : Noir et blanc

Grâce à la formule de luminance (rouge _ 0.3 + vert _ 0.59 + bleu \* 0.11)

![](./output/BlackAndWhite.png)

---

### Exercice n°4 : Négatif

Calcul : 1 - couleur, pour avoir l’inverse.

![](./output/Negatif.png)

---

### Exercice n°5 : Dégradé

Équivalent de map en Processing puis (gris, gris, gris) pour les couleurs.

![](./output/Gradient.png)

---

### Exercice n°6 : Miroir

Avec la fonction swap et la formule :
pixel = image.width() - (1 + x)

![](./output/Miror.png)

![](./output/inverse.png)

---

## Exercice n°7 : Bruit

Nombre de pixels bruités aléatoires (entre 1 et la moitié du nombre total de pixels).  
Pixels choisis aléatoirement et nouvelle couleur aléatoire.

![](./output/Bruit.png)

---

## Exercice n°8 : Rotation 90°

J’ai eu du mal à comprendre quelle formule utiliser.  
Mais j’avais compris qu’il fallait inverser les axes x et y.  
Puis j’ai remarqué qu’il fallait faire un "miroir" sur le nouvel axe des x.

Ainsi, j’ai obtenu le résultat suivant :

![](./images/Rotation.jpg)

---

## Exercice n°9 : RGB Split

Grâce aux indications, j’ai évité le piège et créé une nouvelle image.

J’ai d’abord mis un décalage de 1 px, mais le résultat ne se voyait pas.  
J’ai alors augmenté à 50 px.

J’ai ensuite eu du mal à gérer les débordements.  
J’ai donc calculé en amont la somme des pixels avec décalage, puis, en fonction du débordement ou non, changé les affectations au nouveau pixel.

![](./output/Split.png)

---

## Exercice n°10 : Luminosité

Puissance 3 pour assombrir et puissance 0.2 pour éclairer.

![](./output/Sombre.png)  
![](./output/Clair.png)

---

## Exercice n°11 : Disque

On a un cercle qui a pour centre le point [width/2, height/2] et pour rayon R.  
L’équation caractéristique du cercle est :

(x − cx)² + (y − cy)² ≤ R²

Si (x − cx)² + (y − cy)² < R² alors le point est à l’intérieur du disque.  
Si (x − cx)² + (y − cy)² = R² alors le point est sur le contour.  
Si (x − cx)² + (y − cy)² > R² alors le point est à l’extérieur.

![](./output/Disque.png)

---

### Partie 2 : Cercle

Pour le cercle, j’ai simplement ajouté une condition :  
le point doit être à l’extérieur du cercle de rayon R - épaisseur  
(avec R le rayon du disque précédent).

![](./output/Cercle.png)

---

### Partie 2 : Animation

J’ai créé 2 images pour faire ce GIF.

![](./GIF.gif)

---

### Partie 3 : Rosace

Transformation des coordonnées cartésiennes en polaires avec cos et sin.  
Puis j’ai divisé mon cercle (2 \* pi) par le nombre de cercles que l’on veut.  
Puis, pour chaque itération, je me balade sur le cercle trigonométrique.

Au début, j’avais mis mon angle theta en int au lieu de float, donc cela a créé ce léger décalage :

![](./Echec_rosace.png)

Avec rectification :

![](./output/Rosace.png)

---

## Exercice n°12 : Mosaïque

J’ai utilisé le modulo pour "me balader" sur l’image de base.  
Ainsi, toutes les longueurs de l’image, je reviens au début et je répète le pixel sur la nouvelle image.

J’ai fait un premier test où la fenêtre n’était pas assez grande, donc je ne voyais pas les répétitions.  
Après avoir (enfin) compris, j’ai augmenté la taille.

![](./output/Mosaique.png)

---

### Partie 2 : Mosaïque inversée

J’ai commencé par définir les 4 formes possibles de l’image  
(inversée selon x ou non ET/OU inversée selon l’axe y).

Il m’a ensuite suffi de le retranscrire en code pour obtenir le résultat :

![](./output/MosaiqueMiroir.png)

---

## Exercice n°13 : Glitch

Le seul problème que j’ai rencontré est qu’en laissant une longueur et une largeur aléatoires aux rectangles, j’avais parfois un dépassement.

J’ai donc ajouté des conditions au moment des choix aléatoires :  
choisir le minimum entre le nombre aléatoire et l’espace qu’il reste avant de dépasser pour l’un des deux rectangles.

![](./output/Glitch.png)

---

## Exercice n°14 : Tri de pixels

J’ai vraiment galéré à trouver la logique.  
Mais grâce à l’aide de mes camarades (Agathe en fait), j’ai pu avancer.

![](./output/Tri.png)

---

## Exercice n°15 : Fractale

J’ai rencontré des difficultés pour modifier les coordonnées x et y afin de les avoir dans les intervalles pertinents.

Puis, j’ai rencontré le problème des couleurs : je n’avais pas de nuances de gris, seulement du noir et du blanc.

![](./output/Fractale.png)

---

## Exercice n°16 : Dégradé couleur 1

J’ai repris le code du dégradé noir et blanc.  
J’ai ensuite utilisé la fonction qui permettait d’avoir le pourcentage de noir, afin d’avoir un pourcentage en paramètre de la fonction mix.

![](./output/DegradeColor1.png)

---

## Exercice n°16 : Dégradé couleur LAB

J’ai eu beaucoup plus de difficultés avec cette partie.  
Je mélangeais les types (image.pixel ≠ sil::vec3, image.pixel(x,y) ≠ image.pixel(x,y).r, etc.).

J’ai ensuite eu du mal à comprendre dans quel ordre appliquer les transformations, mais grâce à mes camarades j’ai réussi :  
sRGB → lin → OKLab → lin → sRGB.

Je ne connaissais pas la fonction glm::clamp, qui permet de contraindre une valeur dans un intervalle défini, ce qui m’a bloquée un moment.

Enfin, la fonction mix ne fonctionne que pour des couleurs en sRGB, donc il a fallu l’écrire à la main.

Finalement, j’ai réussi à obtenir un meilleur dégradé grâce à cette méthode :

![](./output/DegradeColor2.png)

---

## Exercice n°18 : Normalisation de l’histogramme

Mon code ne changeait pas l’image au début car je modifiais les 3 composantes r, g et b en même temps  
(je modifiais image.pixel(x,y) et non chacune de ses composantes).

Après rectification, j’obtiens, à partir de l’image à faible contraste :

AVANT  
![](./images/photo_faible_contraste.jpg)

APRÈS  
![](./output/Normalisation.png)

---

## Exercice n°19 : Vortex

Au début, je faisais les changements sur l’image actuelle.  
Une fois que j’ai compris qu’il était nécessaire d’utiliser une nouvelle image, j’ai parcouru l’image de base, calculé la distance de chaque pixel à son centre, puis calculé un angle en fonction afin d’en déduire une nouvelle position.

Je copie ensuite le pixel de base à la nouvelle position calculée sur la nouvelle image.

Pour calculer l’angle, j’ai divisé la distance par la distance maximale (la diagonale calculée avec Pythagore), puis j’ai multiplié (par essais) par un coefficient.

J’obtiens ainsi :

![](./output/Vortex.png)

---

## Exercice n°15 : Convolution

J’ai d’abord essayé de modifier l’image passée en paramètre, ce qui ne permettait pas d’obtenir le résultat souhaité.

Ensuite, j’ai eu du mal à comprendre pourquoi, quand j’affectais la nouvelle couleur au pixel après application du kernel, cela ne fonctionnait pas.

J’ai fini par comprendre que c’était un problème de valeurs.  
Je savais que je devais utiliser clamp pour limiter une valeur à une plage donnée.  
Avec l’aide de mes camarades, j’ai pu corriger cette erreur.

L’effet de flou est léger, mais je n’ai pas pu tester le changement de kernel.

J’ai mis un tableau kernel à passer en paramètre afin de faciliter la suite des exercices.

![](./output/Convo.png)

---

## Exercice n°16 : Sharpen, Emboss, Outline

Grâce au code précédent, en définissant d’autres kernels, on obtient les résultats suivants :

![](./output/Sharpen.png)  
![](./output/Emboss.png)  
![](./output/Outline.png)

---

## Exercice n°17 : Filtre séparable

J’ai repris mon code précédent, mais au lieu d’avoir un kernel 2D, j’ai créé deux listes :  
une qui passe à l’horizontale, l’autre à la verticale.

Je me suis emmêlée entre l’image de base, l’image intermédiaire et l’image finale.

Je n’avais pas fait attention, mais le kernel doit être centré sur le pixel en question, sinon on floute seulement vers la droite et le bas.

J’ai donc eu ce premier résultat :

![](./Echec_flou2.png)

Puis, j’avais un problème dans mes boucles (j’avais mis i <= 16 au lieu de i < 16).  
Il y avait un débordement et un résultat trop foncé.

Mais finalement, j’ai fini par obtenir un résultat correct (et rapide) :

![](./output/Filtre_Separable.png)

---

## Exercice n°18 : Différence de Gaussienne

J’avais oublié de passer par des références (oups…).

Je n’avais pas compris qu’il fallait une étape supplémentaire après avoir passé les pixels issus de la soustraction en niveaux de gris.

J’ai donc d’abord obtenu ce résultat :

![](./Echec_gaussienne.png)

Après avoir corrigé cela (utilisation de clamp), j’ai testé plusieurs valeurs pour choisir quels pixels mettre en blanc ou en noir.  
Le coefficient 0.15 semblait être le meilleur.

![](./output/Difference_gaussienne.png)
