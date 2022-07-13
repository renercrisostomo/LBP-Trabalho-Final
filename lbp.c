#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "pgm.h"
#include "lbp.h"

void salvarHistogramaLBP(struct pgm *pPGM){
  // faz a computação lbp e salva o histograma em um arquivo csv

	unsigned char histogram[258] = {0};

	FILE *fp;
	if (!(fp = fopen("histogramas.csv","a"))){
		perror("Erro. Não foi possível abrir o arquivo histograma.csv");
		exit(1);
	}

  	for (int k=0; k < (pPGM->linhas * pPGM->colunas); k++){

		unsigned char decimal = 0;
		bool direita = (k % pPGM->colunas == pPGM->colunas-1);
		bool esquerda = (k % pPGM->colunas == 0);

		if (*(pPGM->pDados+k)){
			if (k >= pPGM->colunas){
				if ((!esquerda) && (*(pPGM->pDados+k-pPGM->colunas-1) >= *(pPGM->pDados+k))) decimal += pow(2, 0);
				if (*(pPGM->pDados+k-pPGM->colunas) >= *(pPGM->pDados+k)) decimal += pow(2, 1);
				if ((!direita) && (*(pPGM->pDados+k-pPGM->colunas+1) >= *(pPGM->pDados+k))) decimal += pow(2, 2);
			}

			if ((!direita) && (*(pPGM->pDados+k+1) >= *(pPGM->pDados+k))) decimal += pow(2, 3);

			if (k < pPGM->linhas*pPGM->colunas-pPGM->colunas){
				if ((!direita) && (*(pPGM->pDados+k+pPGM->colunas+1) >= *(pPGM->pDados+k))) decimal += pow(2, 4);
				if (*(pPGM->pDados+k+pPGM->colunas) >= *(pPGM->pDados+k)) decimal += pow(2, 5);
				if ((!esquerda) && (*(pPGM->pDados+k+pPGM->colunas-1) >= *(pPGM->pDados+k))) decimal += pow(2, 6);
			}
			
			if ((!esquerda) && (*(pPGM->pDados+k-1) >= *(pPGM->pDados+k))) decimal += pow(2, 7);
		} else decimal = 255;

		histogram[decimal] += 1;
	}

	histogram[257] = pPGM->primeiro_digito-48;
	for (int i=0; i < 256; i++){
		fprintf(fp, "%hhu, ", histogram[i]);
	}
	fprintf(fp, "%hhu\n", histogram[257]);
	fclose(fp);
}
