#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "initMatrix.h"
#include "displayMatrix.h"
#include "calcul.h"
#include "ThreadCalcul.h"

/*Check number is perfect square or not*/
bool isPerfectSquare(int number)
{
    int iVar;
    float fVar;
 
    fVar=sqrt((double)number);
    iVar=fVar;
 
    if(iVar==fVar)
        return true;
    else
        return false;
}

/*Creation la structure blocksize*/
typedef struct blocksize{
	int n;
	int NbrThreads;
	int taille;
	int reste;
	int istart;
	int iend;
	int **A;
	int **B;
	int **C;
}blocksize;

typedef struct blocksize_Matrix_Form{
	int n;
	int NbrThreads;
	int taille;
	int reste;
	int istart;
	int iend;
	int jstart;
	int jend;
	int **A;
	int **B;
	int **C;
}blocksize_Matrix_Form;

void *Mult_vectorielle(void * args);
void *Mult_Matricielle(void * args);

int main(int argc, char **argv){
	
	//Les Variables nécessaire
	int       i,j;
	clock_t   debut,fin;
	double    temps;
	
	char *    Mode      =  argv[1]; 	// Variable permet l'utilisateur a choisir le mode de calcul  		
	int 	  n         =  atoi (argv[2]);  //  La Dimension des matrices 
	int       NBRTHREAD =  atoi (argv[3]); //   Nombre des threads utilisés dans le mode parallel  
	
	
	if(isPerfectSquare(NBRTHREAD)) {
	
	printf("Matrix size = %d\n", n);  
	
	/*Allocation et initialisation des matrices*/
	int **A = (int **)malloc(n * sizeof(int *));
	for (i = 0; i < n; i++)
		A[i] = (int *)malloc(n * sizeof(int));
	printf("The First Matrix : \n");
	generateRandomMatrix(A, n, 0, 99); // remplir la matrice A aleatoire
	printMatrix(A,n);		  // afficher la matrice A 
	printf("\n");
	
	int **B = (int **)malloc(n * sizeof(int *));
	for (i = 0; i < n; i++)
		B[i] = (int *)malloc(n * sizeof(int));
	printf("The Second Matrix : \n");
	generateRandomMatrix(B, n, 1, 99); // remplir la matrice B aleatoire
	printMatrix(B,n);		  // afficher la matrice B
	printf("\n");
	
	
	int **C = (int **)malloc(n * sizeof(int *));
	for (i = 0; i < n; i++)
		C[i] = (int *)malloc(n * sizeof(int));
		
	int **D = (int **)malloc(n * sizeof(int *));
	for (i = 0; i < n; i++)
		D[i] = (int *)malloc(n * sizeof(int));
	
	/*Argement pour passage des paramtres*/
	blocksize Argement;
	Argement.NbrThreads = NBRTHREAD ;
	Argement.n = n;
	Argement.taille = n/NBRTHREAD;
	Argement.reste = n%NBRTHREAD;
	Argement.istart = 0;
	Argement.iend = n-1;
	Argement.A = A;
	Argement.B = B;
	Argement.C = C;
	
	blocksize_Matrix_Form smallMatrix;
	smallMatrix.NbrThreads = NBRTHREAD ;
	smallMatrix.n = n;
	smallMatrix.taille = n/(int)sqrt((NBRTHREAD));
	smallMatrix.reste = n%(int)sqrt((NBRTHREAD));
	smallMatrix.A = A;
	smallMatrix.B = B;
	smallMatrix.C = D; 
	
	if((!strcmp(Mode,"S"))||(!strcmp(Mode,"s"))){
		printf("Sequential execution : \n");
		debut = clock();
		MultMatrices(A,B,n);
		fin = clock();
		temps = ((double)fin - debut) / CLOCKS_PER_SEC; //Calcul le temps d'execution pour le mode sequential
		printf("temps d'execution : %f\n",temps);
		return 0;
	} 
	else if ((!strcmp(Mode,"P"))||(!strcmp(Mode,"p"))){ 
		printf("Parallel execution Ligne : \n");
		debut = clock();
		
		/*Creation des threads*/
		pthread_t *threads = (pthread_t*) malloc(sizeof(pthread_t) * NBRTHREAD);
		for(i=0; i<NBRTHREAD; i++){ 
			Argement.istart = i * Argement.taille;
			Argement.iend = Argement.istart + Argement.taille-1 + Argement.reste;
			debut = clock();
			if(pthread_create(&threads[i], NULL,Mult_vectorielle,&Argement)){ 
				fprintf(stderr, "Error creating thread\n");
				return 1;
			} 
			if(pthread_join(threads[i], NULL)){ 
				fprintf(stderr, "Error joining thread\n");
			return 2;
			}
			
		}
		
		printMatrix(Argement.C,Argement.n);
		fin = clock();
		temps = ((double)fin - debut) / CLOCKS_PER_SEC; //Calcul le temps d'execution pour le mode parallel Ligne
		printf("\ntemps d'execution : %f \n",temps);
		printf("\n\n\n");
				
		printf("Parallel execution small Matrix : \n");
		debut = clock();
		pthread_t *threads2 = (pthread_t*) malloc(sizeof(pthread_t) * NBRTHREAD);
		for(i=0; i<NBRTHREAD; i++){ 
			smallMatrix.istart = (i/(int)sqrt(NBRTHREAD)) * smallMatrix.taille;
			smallMatrix.iend   = smallMatrix.istart  + smallMatrix.taille -1 + smallMatrix.reste;
			if(i < sqrt(NBRTHREAD)){
				smallMatrix.jstart = i * smallMatrix.taille;
				smallMatrix.jend   = smallMatrix.jstart + smallMatrix.taille -1 + smallMatrix.reste;
			}else{
				smallMatrix.jstart = (i % (int)sqrt(NBRTHREAD)) * smallMatrix.taille;
				smallMatrix.jend   = smallMatrix.jstart + smallMatrix.taille -1 + smallMatrix.reste;
			}
			//debut = clock();
			if(pthread_create(&threads2[i], NULL,Mult_Matricielle,&smallMatrix)){ 
				fprintf(stderr, "Error creating thread\n");
				return 3;
			} 
			if(pthread_join(threads2[i], NULL)){ 
				fprintf(stderr, "Error joining thread\n");
			return 4;
			}
		} 		
	}
			printMatrix(smallMatrix.C,smallMatrix.n);
			fin = clock();
			temps = ((double)fin - debut) / CLOCKS_PER_SEC; //Calcul le temps d'execution pour le mode parallel small Matrix
			printf("\ntemps d'execution : %f \n",temps);
			printf("\n\n\n");
			
	}else 
		printf("Please choose a perfect square number for threads (like 4,9,16,25 ...) \n");
}
