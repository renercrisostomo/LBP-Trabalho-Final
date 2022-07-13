#ifndef PGM_H
#define PGM_H

struct pgm{
	int tipo;
	int colunas;
	int linhas;
	int max_valor;
	unsigned char *pDados;
	char primeiro_digito;
};

void lerImagemPGM(struct pgm *, char *);


#endif // PGM_H


