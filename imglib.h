/**********************************
 PROGRAMAÇÃO IMPERATIVA
 Pedro Roldan, a21406840
 João Oliveira, a21406839
 Trabalho: PGM image processor
***********************************/
#include "filelib.h"

#ifndef _IMGLIB_
    #define _IMGLIB_

    typedef struct s_imagem *IMAGEM;
#endif


/*
 DESCRIÇÃO: Deverá permitir a obtenção de uma nova instância de uma imagem preta.
 PRÉ: intCol > 0, intRow > 0
 PÓS: imagem com memória alocada
 EXCEPÇÕES: Aborta caso haja falta de memória
*/
IMAGEM IMAGEMnew(int intCol, int intRow);


/*
 DESCRIÇÃO: Permite a obtenção de uma nova instância de uma imagem, a partir de um ficheiro no formato PGM P2.
 PRÉ: Nome de ficheiro de imagem existente
 PÓS: Retorna imagem inicializada e carregada em memória
 EXCEPÇÕES: Aborta no caso de formato desconhecido, ou falta de memória
*/
IMAGEM IMAGEMnewFromFile(const char *chrFilename);


/*
 DESCRIÇÃO: Liberta os recursos relativos à imagem.
 PRÉ: img != NULL, e memória alocada anteriormente
 PÓS: Memória liberta
*/
void IMAGEMdestroy(IMAGEM img);


/*
 DESCRIÇÃO: Define o formato da Imagem.
 PRÉ: img != NULL, e imagem carregada. MagicNumber == "P2" ou MagicNumber == "P5"
 PÓS: Formato de imagem alterado para o pedido
*/
void IMAGEMsetFormat(IMAGEM img, char *MagicNumber);


/*
 DESCRIÇÃO: Obtém o formato da Imagem.
 PRÉ: img != NULL, e imagem carregada
 PÓS: retorna MagicNumber ("P2" ou "P5")
*/
char *IMAGEMgetFormat(IMAGEM img);


/*
 DESCRIÇÃO: Obtém a intensidade máxima possível permitida pela imagem.
 PRÉ: img != NULL, e imagem carregada
 PÓS: retorna valor da intensidade máxima da imagem
*/
unsigned int IMAGEMgetMaxIntensity(IMAGEM img);


/*
 DESCRIÇÃO: Define a intensidade máxima possível permitida pela imagem.
 PRÉ: img != NULL, e imagem carregada. 0 <= intMaxGray <= 65535 (ou intMaxGray <= 255 no caso do formato ser "P2")
 PÓS: define valor da intensidade máxima para a imagem
*/
void IMAGEMsetMaxIntensity(IMAGEM img, unsigned int intMaxGray);


/*
 DESCRIÇÃO: Obtém número de linhas da imagem
 PRÉ: img != NULL, e imagem carregada
 PÓS: retorna número de linhas da imagem
*/
int IMAGEMgetRows(IMAGEM img);


/*
 DESCRIÇÃO: Obtém número de colunas da imagem
 PRÉ: img != NULL, e imagem carregada
 PÓS: retorna número de colunas da imagem
*/
int IMAGEMgetColumns(IMAGEM img);


/*
 DESCRIÇÃO: Define o valor da intensidade de um determinado pixel na imagem.
 PRÉ: img != NULL, e imagem carregada. coluna e linha dentro dos limites máximos da imagem, 0 <= intensidade <= intensidade máxima da imagem
 PÓS: Intensidade do pixel pretendido alterada
*/
void IMAGEMsetPixelIntensity(IMAGEM img, int coluna, int linha, unsigned int intensidade);


/*
 DESCRIÇÃO: Obtém o valor da intensidade de um determinado pixel na imagem.
 PRÉ: img != NULL, e imagem carregada. coluna e linha dentro dos limites máximos da imagem
 PÓS: retorna a intensidade do pixel pretendido
*/
unsigned int IMAGEMgetPixelIntensity(IMAGEM img, int coluna, int linha);


/*
 DESCRIÇÃO: Retorna a identidade de uma imagem, numa nova instância.
 PRÉ: img != NULL, imagem carregada
 PÓS: retorna nova instância idêntica da imagem
 EXCEPÇÕES: Aborta caso não haja memória suficiente
*/
IMAGEM IMAGEMgetIdentity(IMAGEM img);


/*
 DESCRIÇÃO: Retorna o negativo de uma imagem, numa nova instância.
 PRÉ: img != NULL, imagem carregada
 PÓS: retorna nova instância com o negativo da imagem
 EXCEPÇÕES: Aborta caso não haja memória suficiente
*/
IMAGEM IMAGEMgetNegative(IMAGEM img);


/*
 DESCRIÇÃO: Retorna uma nova instância de uma imagem, com a intensidade máxima da vizinhança de cada pixel.
 PRÉ: img != NULL, imagem carregada
 PÓS: Retorna nova instância com intensidade máxima da vizinhança de cada pixel da imagem
 EXCEPÇÕES: Aborta caso não haja memória suficiente
*/
IMAGEM IMAGEMgetMax(IMAGEM img);


/*
 DESCRIÇÃO: Retorna uma nova instância de uma imagem, com a intensidade mínima da vizinhança de cada pixel.
 PRÉ: img != NULL, imagem carregada
 PÓS: Retorna nova instância com intensidade mínima da vizinhança de cada pixel da imagem
 EXCEPÇÕES: Aborta caso não haja memória suficiente
*/
IMAGEM IMAGEMgetMin(IMAGEM img);


/*
 DESCRIÇÃO: Retorna uma nova instância de uma imagem, com a intensidade média da vizinhança de cada pixel.
 PRÉ: img != NULL, imagem carregada
 PÓS: Retorna nova instância com a intensidade média da vizinhança de cada pixel da imagem
 EXCEPÇÕES: Aborta caso não haja memória suficiente
*/
IMAGEM IMAGEMgetMedia(IMAGEM img);


/*
 DESCRIÇÃO: Retorna uma nova instância de uma imagem, com a intensidade mediana da vizinhança de cada pixel.
 PRÉ: img != NULL, imagem carregada
 PÓS: Retorna nova instância com a intensidade mediana da vizinhança de cada pixel da imagem
 EXCEPÇÕES: Aborta caso não haja memória suficiente
*/
IMAGEM IMAGEMgetMediana(IMAGEM img);


/*
 DESCRIÇÃO: Retorna uma imagem invertida horizontalmente, numa nova instância.
 PRÉ: img != NULL, imagem carregada
 PÓS: Retorna nova instância da imagem invertida horizontalmente
 EXCEPÇÕES: Aborta caso não haja memória suficiente
*/
IMAGEM IMAGEMflipHorizontal(IMAGEM img);


/*
 DESCRIÇÃO: Retorna uma imagem invertida verticalmente, numa nova instância.
 PRÉ: img != NULL, imagem carregada
 PÓS: Retorna nova instância da imagem invertida verticalmente
 EXCEPÇÕES: Aborta caso não haja memória suficiente
*/
IMAGEM IMAGEMflipVertical(IMAGEM img);


/*
 DESCRIÇÃO: Retorna uma imagem rodada 90 graus no sentido do ponteiro do relógio, numa nova instância.
 PRÉ: img != NULL, imagem carregada
 PÓS: Retorna nova instância da imagem rodada 90 graus no sentido do ponteiro do relógio
 EXCEPÇÕES: Aborta caso não haja memória suficiente
*/
IMAGEM IMAGEMrotate90(IMAGEM img);


/*
 DESCRIÇÃO: Retorna uma imagem rodada 180 graus no sentido do ponteiro do relógio, numa nova instância.
 PRÉ: img != NULL, imagem carregada
 PÓS: Retorna nova instância da imagem rodada 180 graus no sentido do ponteiro do relógio
 EXCEPÇÕES: Aborta caso não haja memória suficiente
*/
IMAGEM IMAGEMrotate180(IMAGEM img);


/*
 DESCRIÇÃO: Retorna uma imagem rodada 270 graus no sentido do ponteiro do relógio, numa nova instância.
 PRÉ: img != NULL, imagem carregada
 PÓS: Retorna nova instância da imagem rodada 270 graus no sentido do ponteiro do relógio
 EXCEPÇÕES: Aborta caso não haja memória suficiente
*/
IMAGEM IMAGEMrotate270(IMAGEM img);


/*
 DESCRIÇÃO: Retorna uma imagem convertida no formato oposto, numa nova instância.
 PRÉ: img != NULL, imagem carregada
 PÓS: Retorna nova instância da imagem convertida de P2 para P5, ou de P5 (8-bits) para P2
 EXCEPÇÕES: Aborta caso não haja memória suficiente, ou caso seja um formato diferente de P2, ou P5 de 8-bits
*/
IMAGEM IMAGEMconvert(IMAGEM img);
