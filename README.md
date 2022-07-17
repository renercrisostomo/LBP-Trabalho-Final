# LBP-Trabalho-Final

Repositório do último trabalho da disciplina Laboratório de programação do 2º semestre do curso ciencias da computação

## Sobre o Trabalho

Para cada imagem pgm da pasta `datasets/oncotex_pgm`; faz a leitura, filtro lbp (local binary patterns) e salva um histograma do filtro no arquivo histogramas.csv.

- 13/07 : Apresentação do trabalho
- Histograma - vetor de 257 elementos onde cada posição (indice) tem a quantidade de vezes que o inteiro relativo a essa posição aparece -- chamado de vetor de caracteristicas -- e na posição 257 adiciona o primeiro caractere do nome do arquivo pgm.

### PGM de Exemplo

```txt
P2
5 4
9

1 2 3 4 5
1 2 3 4 5
1 2 3 4 5
1 2 3 4 5
```

### Computação LBP

```txt
0 0 0  0 0 0  0 0 0  0 0 0  0 0 0
0 1 1  0 2 1  0 3 1  0 4 1  0 5 0
0 1 1  0 1 1  0 1 1  0 1 1  0 1 0

0 1 1  0 1 1  0 1 1  0 1 1  0 1 0
0 1 1  0 2 1  0 3 1  0 4 1  0 5 0
0 1 1  0 1 1  0 1 1  0 1 1  0 1 0

0 1 1  0 1 1  0 1 1  0 1 1  0 1 0
0 1 1  0 2 1  0 3 1  0 4 1  0 5 0
0 1 1  0 1 1  0 1 1  0 1 1  0 1 0

0 1 1  0 1 1  0 1 1  0 1 1  0 1 0
0 1 1  0 2 1  0 3 1  0 4 1  0 5 0
0 0 0  0 0 0  0 0 0  0 0 0  0 0 0
```

#### LBP binário

```txt
00111000 00111000 00111000 00111000 00100000
00111110 00111110 00111110 00111110 00100010
00111110 00111110 00111110 00111110 00100010
00001110 00001110 00001110 00001110 00000010
```

#### LBP decimal

```txt
56 56 56 56 32
62 62 62 62 34
62 62 62 62 34
14 14 14 14 2
```

### Histograma

```csv
0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1ºcaracter_do_arquivo
```
