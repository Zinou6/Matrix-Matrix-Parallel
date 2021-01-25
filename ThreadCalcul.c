#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "ThreadCalcul.h"
#include "displayMatrix.h"

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

void *Mult_vectorielle(void * args){		
	blocksize * blk = (blocksize *) args;
	for(int i = blk->istart; i<=blk->iend; i++){
		for(int j=0; j<blk->n; j++)
			for(int k=0; k<blk->n; k++){
				blk->C[i][j] = blk->C[i][j] + blk->A[i][k] * blk->B[k][j];			
			}
		}
	return NULL;
}
