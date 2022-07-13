#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct pgm{
	int tipo;
	int colulas;
	int linhas;
	int maxValor;
	unsigned char *pPGM;
};

void ler_imagem_PGM(struct pgm *);
void test_ler_imagem_PGM(struct pgm *);

int main(){

	struct pgm img;
	int *pLBP;

    ler_imagem_PGM(&img);
	test_ler_imagem_PGM(&img);
	free(img.pPGM);

	return 0;
}

void ler_imagem_PGM(struct pgm *pio){

	FILE *fp;
	char ch;

	if (!(fp = fopen("img01_ORIGINAL.pgm", "r"))){
		perror("Erro ao ler o arquivo.");
		exit(1);
	}

	if ( (ch = getc(fp)) != 'P'){
		puts("A imagem fornecida não está no formato pgm");
		exit(2);
	}
	
	pio->tipo = getc(fp)-48; // transformando o caracter em inteiro
	
	fseek(fp, 1, SEEK_CUR);

	while((ch=getc(fp)) == '#'){
		while( !(ch=getc(fp) == '\n'));
	}

	fseek(fp, -2, SEEK_CUR);

	fscanf(fp, "%d %d", &pio->colulas, &pio->linhas);
	if (ferror(fp)){ 
		perror(NULL);
		exit(3);
	}	
	fscanf(fp, "%d", &pio->maxValor);
	fseek(fp, 1, SEEK_CUR);

	pio->pPGM = (unsigned char*) malloc(pio->linhas * pio->colulas * sizeof(unsigned char));

	switch(pio->tipo){
		case 2:
			puts("Lendo imagem PGM (dados em texto)");
			for (int k=0; k < (pio->linhas * pio->colulas); k++){
				fscanf(fp, "%hhu", pio->pPGM+k);
			}
		break;	
		case 5:
			puts("Lendo imagem PGM (dados em binário)");
			fread(pio->pPGM,sizeof(unsigned char), pio->linhas * pio->colulas, fp);
		break;
		default:
			puts("Não está implementado");
	}
	
	fclose(fp);
}

void test_ler_imagem_PGM(struct pgm *pio){
	// printa os valores dos campos da estrutura pgm e do ponteiro para a imagem em modo texto pgm
	printf("Tipo: %d\n", pio->tipo);
	printf("Colunas: %d\n", pio->colulas);
	printf("Linhas: %d\n", pio->linhas);
	printf("MaxValor: %d\n", pio->maxValor);
	printf("\n");
	for (int k=0; k < (pio->linhas * pio->colulas); k++){
		if (!(k % pio->colulas)) printf("\n");
		printf("%hhu ", *(pio->pPGM+k));
	}
	printf("\n");
}