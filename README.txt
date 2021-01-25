                                                                   
                                                      PARALLEL DENSE MATRIX-MATRIX MULTIPLICATION 
							   BY : BENSAID Zine El Abidine
								   25/01/2021

1/ Introduction
 
 Ce programme a pour le but de calculer le produit matriciel en séquentielle classique et en parallele.
 Le code est en c en utilisant la bibliothéque pthread.

2/ Architecture

     --main.c:
     	        -Creation une structure BLOCKSIZE.
                -Appel à "initMatrix","displayMatrix","calcul","ThreadCalcul".
                -Allocation des matrices.
                -Création et affichage des matrices A et B.
                -Création des threads.
                -Affichage du resultat du calcul parallele et séquentiel.
                -Affichage et calcul du temps sequetiel et parallel en secondes.



     --initMatrix.c:
                -Génére une matrice avec des valeurs aléatoires grace à la fonction "generateRandomMatrix".


     --displayMatrix.c:
                -Affiche la matrice grace à la fonction "printMatrix".


     --calcul.c:
               -Calcule le produit matriciel en séquentiel C=A*B grace à la procedure MultMatrices.
               -Appel de "displayMatrix" pour afficher la matrice C "Resultat" grace à la fonction "printMatrix".


     --ThreadCalcul.c:
     	       -Calcule le produit matriciel en parallel grace à la procedure MultVectorielle.

3/ Execution:
                 une fichier makefile compile tous les fichier et cree un fichier executable mmm
                 ./mmm [mode de calcul p/P pour parallel ou s/S pour sequentiel] [n la dimension des matrices] [nombre des threads] 
