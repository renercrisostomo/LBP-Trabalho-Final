# LBP-Trabalho-Final

Repositório do último trabalho da disciplina Laboratório de Programação do 2º semestre do curso Ciências da Computação

## Sobre o Trabalho

O objetivo deste trabalho é realizar a extração de características de imagens médicas usando o método LBP (Local Binary Patterns). O método LBP consiste em comparar cada pixel de uma imagem com os seus vizinhos e gerar um código binário que representa a sua textura local. Esse código pode ser convertido em um valor decimal e usado para construir um histograma que representa a distribuição das texturas na imagem.

O trabalho utiliza imagens PGM da pasta `datasets/oncotex_pgm`, que são imagens de tecidos tumorais. Para cada imagem, o programa faz a leitura, aplica o filtro LBP e salva o histograma resultante no arquivo `histogramas.csv`. Cada histograma é um vetor de 257 elementos, onde cada posição (índice) tem a quantidade de vezes que o valor decimal correspondente aparece na imagem. A posição 257 contém o primeiro caractere do nome do arquivo PGM, que indica a classe da imagem (normal ou anormal).

A apresentação do trabalho foi no dia 13/07/2022.

### Exemplo de Imagem PGM

Uma imagem PGM é um formato de imagem em tons de cinza que contém um cabeçalho com as informações básicas da imagem (tipo, largura, altura e valor máximo) e uma matriz com os valores dos pixels. Um exemplo de imagem PGM é:

```txt
P2
5 4
9

1 2 3 4 5
1 2 3 4 5
1 2 3 4 5
1 2 3 4 5
```

### Exemplo de Filtro LBP

O filtro LBP é aplicado em uma janela de 3x3 pixels, comparando o pixel central com os seus oito vizinhos. Se o valor do vizinho for maior ou igual ao do pixel central, ele recebe um bit 1, caso contrário, recebe um bit 0. O resultado é um código binário de oito bits que pode ser convertido em um valor decimal. Por exemplo, para a imagem acima, o filtro LBP produziria a seguinte matriz:

```txt
56 56 56 56 32
62 62 62 62 34
62 62 62 62 34
14 14 14 14 2
```

Onde cada valor decimal é obtido pela conversão do código binário gerado pelo filtro LBP. Por exemplo, para o pixel (1,1) da imagem original, que tem valor 1, o filtro LBP gera o código binário `00111000`, que equivale ao valor decimal `56`.

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

### Exemplo de Histograma

O histograma é obtido pela contagem da frequência de cada valor decimal na matriz resultante do filtro LBP. O histograma é um vetor de 257 elementos, onde cada posição (índice) tem a quantidade de vezes que o valor decimal correspondente aparece na matriz. A posição 257 contém o primeiro caractere do nome do arquivo PGM, que indica a classe da imagem (normal ou anormal). Por exemplo, para a matriz acima, o histograma seria:

```csv
0,0,1,0,...,0,0,4,...,0,0,8,...,0,N
```

Onde N é o primeiro caractere do nome do arquivo PGM indicando a classe da imagem.
