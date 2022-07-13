#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

struct pgm{
	int tipo;
	int colunas;
	int linhas;
	int maxValor;
	unsigned char *pDados;
	char primeiroDigito;
};

void ler_imagem_PGM(struct pgm *, char *);
void salvar_histograma_lbp(struct pgm *);

int main(){

	clock_t inicio, fim;
	double tempoPorImagem, tempoTotal=0;

	FILE *fp;

	if (!(fp = fopen("histogramas.csv","w"))){
		perror("Erro. ");
		exit(1);
	}
	fclose(fp);

    DIR *dir;
    struct dirent *larq;
	struct pgm img;

	dir = opendir("../testsalvarhistograma");

	int count = 0;
    while ((larq = readdir(dir)) != NULL){
		if (!(strstr(larq->d_name, ".pgm"))) continue;
		img.primeiroDigito = larq->d_name[0];
		ler_imagem_PGM(&img, larq->d_name);
		inicio = clock();
		salvar_histograma_lbp(&img);
		fim = clock();
		free(img.pDados);
		printf("%03d/656\n", ++count);

		tempoPorImagem = (double)(fim - inicio) / CLOCKS_PER_SEC;
		tempoTotal += tempoPorImagem;
    }

    closedir(dir);

	printf("\nTempo Médio: %lf\n",tempoTotal/count);
	printf("Tempo Total: %lf\n",tempoTotal);
	
	return 0;
}

void ler_imagem_PGM(struct pgm *pio, char *filename){

	FILE *fp;
	char ch;

	if (!(fp = fopen(filename,"r"))){
		perror("Erro ao ler o arquivo.");
		exit(1);
	}

	if ( (ch = getc(fp))!='P'){
		puts("A imagem fornecida não está no formato pgm");
		exit(2);
	}
	
	pio->tipo = getc(fp)-48;
	
	fseek(fp, 1, SEEK_CUR);

	while((ch=getc(fp))=='#'){
		while( !(ch=getc(fp) =='\n'));
	}

	fseek(fp, -2, SEEK_CUR); // substituí o -1 por -2 para resolver o problema dos comentários

	fscanf(fp, "%d %d", &pio->colunas, &pio->linhas);
	if (ferror(fp)){ 
		perror(NULL);
		exit(3);
	}	
	fscanf(fp, "%d", &pio->maxValor);
	fseek(fp, 1, SEEK_CUR);

	pio->pDados = (unsigned char*) malloc(pio->linhas * pio->colunas * sizeof(unsigned char));

	switch(pio->tipo){
		case 2:
			for (int k=0; k < (pio->linhas * pio->colunas); k++){
				fscanf(fp, "%hhu", pio->pDados+k);
			}
		break;	
		case 5:
			fread(pio->pDados, sizeof(unsigned char), pio->linhas * pio->colunas, fp);
		break;
		default:
			puts("Não está implementado");
	}
	
	fclose(fp);
}

void salvar_histograma_lbp(struct pgm *pPGM){
  // faz a computação lbp e salva o histograma em um arquivo csv

	unsigned char histogram[258] = {0};

	FILE *fp;
	if (!(fp = fopen("histogramas.csv","a"))){
		perror("Erro. Não foi possível abrir o arquivo histograma.csv");
		exit(1);
	}

  	for (int k=0; k < (pPGM->linhas * pPGM->colunas); k++){

		unsigned char decimal = 0;
		bool Direita = (k % pPGM->colunas == pPGM->colunas-1);
		bool Esquerda = (k % pPGM->colunas == 0);

		if (*(pPGM->pDados+k)){
			if (k >= pPGM->colunas){
				if ((!Esquerda) && (*(pPGM->pDados+k-pPGM->colunas-1) >= *(pPGM->pDados+k))) decimal += pow(2, 0);
				if (*(pPGM->pDados+k-pPGM->colunas) >= *(pPGM->pDados+k)) decimal += pow(2, 1);
				if ((!Direita) && (*(pPGM->pDados+k-pPGM->colunas+1) >= *(pPGM->pDados+k))) decimal += pow(2, 2);
			}

			if ((!Direita) && (*(pPGM->pDados+k+1) >= *(pPGM->pDados+k))) decimal += pow(2, 3);

			if (k < pPGM->linhas*pPGM->colunas-pPGM->colunas){
				if ((!Direita) && (*(pPGM->pDados+k+pPGM->colunas+1) >= *(pPGM->pDados+k))) decimal += pow(2, 4);
				if (*(pPGM->pDados+k+pPGM->colunas) >= *(pPGM->pDados+k)) decimal += pow(2, 5);
				if ((!Esquerda) && (*(pPGM->pDados+k+pPGM->colunas-1) >= *(pPGM->pDados+k))) decimal += pow(2, 6);
			}
			
			if ((!Esquerda) && (*(pPGM->pDados+k-1) >= *(pPGM->pDados+k))) decimal += pow(2, 7);
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
