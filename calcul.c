#include <stdio.h>
#include <stdlib.h>

#include "calcul.h"
#include "displayMatrix.h"

void MultMatrices (int **M1,int **M2, int size){
	int **R = (int **)malloc(size * sizeof(int *));
	for (int i = 0; i < size; i++)
		R[i] = (int *)malloc(size * sizeof(int));
	for(int i = 0; i < size; ++i)
		for(int j = 0; j < size; ++j){
			R[i][j] = 0;
			for(int k = 0; k < size; ++k)
				R[i][j] += M1[i][k] * M2[k][j];
		}
	printMatrix(R,size);
}
