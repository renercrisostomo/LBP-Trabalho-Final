#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"


void lerImagemPGM(struct pgm *pio, char *filename){

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
	fscanf(fp, "%d", &pio->max_valor);
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
