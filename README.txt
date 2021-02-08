                                                                   
                                                      PARALLEL DENSE MATRIX-MATRIX MULTIPLICATION 
							   BY : BENSAID Zine El Abidine
							   		&
							   	   BOUKHIAR Naima	
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
               -Calcul le produit matriciel en séquentiel C=A*B grace à la procedure MultMatrices.
               -Appel de "displayMatrix" pour afficher la matrice C "Resultat" grace à la fonction "printMatrix".


     --ThreadCalcul.c:
     	       -Calcul le produit matriciel en parallel ou chaque thread prend un blocksize contient un nombre de lignes et il calcule la multiplication grace à la procedure MultVectorielle.
	       -Calcule le produit matriciel en parallel ou chaque thread prend un blocksize contient une saus-matrice et il calcule la multiplication grace à la procedure Mult_Matricielle.
	       
3/ Execution:
               - une fichier makefile compile tous les fichier et cree un fichier executable mmm
               -  ./mmm [mode de calcul p/P pour parallel ou s/S pour sequentiel] [n la dimension des matrices] [nombre des threads]
               
               **PS: nombre des threads doit etre un racine complet.
                                
4/ Erreur: 
		la fonction Mult_Matricielle donne des faux calcules sauf si la dimension des matrices multiples de nombre des threads. 
                 
          
