#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include "pgm.h"
#include "lbp.h"

int main(int argc, char *argv[]){

	if(argc < 2){
		puts("Erro. Uso: ./main.exe <caminho do diretorio contendo as imagens pgm>");
		exit(0);
	}
	
	clock_t inicio, fim;
	double tempo_por_imagem, tempo_total=0;

	FILE *fp;

	if (!(fp = fopen("histogramas.csv","w"))){
		perror("Erro. ao abrir o arquivo histogramas.csv");
		exit(1);
	}
	fclose(fp);

    DIR *dir;
    struct dirent *larq;
	struct pgm img;

	dir = opendir(argv[1]);

	char caminho_imagem[100];

	int count = 0;
    while ((larq = readdir(dir)) != NULL){
		if (!(strstr(larq->d_name, ".pgm"))) continue;
		img.primeiro_digito = larq->d_name[0];
		sprintf(caminho_imagem, "%s/%s", argv[1], larq->d_name);
		lerImagemPGM(&img, caminho_imagem);
		inicio = clock();
		salvarHistogramaLBP(&img);
		fim = clock();
		free(img.pDados);
		printf("%03d imagens pgm\n", ++count);

		tempo_por_imagem = (double)(fim - inicio) / CLOCKS_PER_SEC;
		tempo_total += tempo_por_imagem;
    }

    closedir(dir);
	
	printf("\nTempo Medio: %lf s\n",tempo_total/count);
	printf("Tempo Total: %lf s\n\n",tempo_total);
	
	return 0;
}

