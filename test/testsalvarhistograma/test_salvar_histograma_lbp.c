#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

struct pgm{
	int tipo;
	int colunas;
	int linhas;
	int maxValor;
	unsigned char *pDados;
	char primeiroDigito;
};

void salvar_histograma_lbp(struct pgm *);

int main(){

	FILE *fp;

	if (!(fp = fopen("histogramabase.csv","w"))){
		perror("Erro ao abrir histogramabase.csv");
		exit(1);
	}
	fclose(fp);

	struct pgm img;

	img.colunas = 5;
	img.linhas = 4;
	img.pDados = (unsigned char*) malloc(img.linhas * img.colunas * sizeof(unsigned char));
	img.primeiroDigito = '0';

	/* adicionar dados em pDados com os valores:

	1 2 3 4 5
	1 2 3 4 5
	1 2 3 4 5
	1 2 3 4 5
	*/
	for (int i = 1; i <= 4; i++){
		for (int j = 1; j <= 5; j++){
			img.pDados[(i-1) * img.colunas + (j-1)] = j;
		}
	}

	// printar os dados em pDados
	for (int i = 0; i < img.linhas; i++){
		for (int j = 0; j < img.colunas; j++){
			if (j % 5 == 0) printf("\n");
			printf("%d ", img.pDados[i * img.colunas + j]);
		}
	}

	salvar_histograma_lbp(&img);
	free(img.pDados);
	
	return 0;
}

void salvar_histograma_lbp(struct pgm *pPGM){
	// faz a computação lbp e salva o histograma em um arquivo csv

	unsigned char histogram[258] = {0};

	FILE *fp;
	if (!(fp = fopen("histogramabase.csv","a"))){
		perror("Erro. Não foi possível abrir o arquivo histograma.csv");
		exit(1);
	}

  	for (int k=0; k < (pPGM->linhas * pPGM->colunas); k++){

		unsigned char decimal = 0;
		bool naoDireita = (k % pPGM->colunas != pPGM->colunas-1);
		bool naoEsquerda = (k % pPGM->colunas != 0);

		if (*(pPGM->pDados+k)){
			if (k >= pPGM->colunas){
				if ((naoEsquerda) && (*(pPGM->pDados+k-pPGM->colunas-1) >= *(pPGM->pDados+k))) decimal += pow(2, 0);
				if (*(pPGM->pDados+k-pPGM->colunas) >= *(pPGM->pDados+k)) decimal += pow(2, 1);
				if ((naoDireita) && (*(pPGM->pDados+k-pPGM->colunas+1) >= *(pPGM->pDados+k))) decimal += pow(2, 2);
			}

			if ((naoDireita) && (*(pPGM->pDados+k+1) >= *(pPGM->pDados+k))) decimal += pow(2, 3);

			if (k < pPGM->linhas*pPGM->colunas-pPGM->colunas){
				if ((naoDireita) && (*(pPGM->pDados+k+pPGM->colunas+1) >= *(pPGM->pDados+k))) decimal += pow(2, 4);
				if (*(pPGM->pDados+k+pPGM->colunas) >= *(pPGM->pDados+k)) decimal += pow(2, 5);
				if ((naoEsquerda) && (*(pPGM->pDados+k+pPGM->colunas-1) >= *(pPGM->pDados+k))) decimal += pow(2, 6);
			}
			
			if ((naoEsquerda) && (*(pPGM->pDados+k-1) >= *(pPGM->pDados+k))) decimal += pow(2, 7);
		} else decimal = 255;

		histogram[decimal] += 1;
	}

	histogram[257] = pPGM->primeiroDigito-48;
	for (int i=0; i < 256; i++){
		fprintf(fp, "%hhu, ", histogram[i]);
	}
	fprintf(fp, "%hhu\n", histogram[257]);
	fclose(fp);
}
