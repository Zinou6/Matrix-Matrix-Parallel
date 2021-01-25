/*
 * displayMatrix.c
 *
 *  Created on: 5 janv. 2021
 *      Author: laloukil
 */

#include <stdio.h>

#include "displayMatrix.h"

void printMatrix(int** matrix, int n){
	int i, j;
	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}
}
