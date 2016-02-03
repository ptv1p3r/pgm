/**********************************
 PROGRAMAÇÃO IMPERATIVA
 Pedro Roldan, a21406840
 João Oliveira, a21406839
 Trabalho: PGM image processor
***********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imglib.h"

#define MAX_VIZINHANCA 9
#define DEFAULT_MAX_GRAY 255


struct s_imagem {
    char magicNumber[3];
    int intCol;
    int intRow;
    unsigned int intMaxGray;
    unsigned int **arrMatrix;
};


/* Protótipos de funções estáticas (INTERNAS) */
static unsigned int *getVizinhanca(IMAGEM, int, int);
static void swap(unsigned int *array, int pos1, int pos2);
static void selectionSort(unsigned int *array, int n);



/* Implementação de funções estáticas (INTERNAS) */
static unsigned int *getVizinhanca(IMAGEM img, int x, int y) {
    unsigned int *vizinhanca = (unsigned int *)malloc(sizeof(unsigned int) * MAX_VIZINHANCA);

    if (!vizinhanca) {
        perror("Erro na alocação de memória!\n");
        exit(EXIT_FAILURE);
    }

    vizinhanca[0] = IMAGEMgetPixelIntensity(img, x, y);
    vizinhanca[1] = IMAGEMgetPixelIntensity(img, x-1, y);
    vizinhanca[2] = IMAGEMgetPixelIntensity(img, x-1, y-1);
    vizinhanca[3] = IMAGEMgetPixelIntensity(img, x, y-1);
    vizinhanca[4] = IMAGEMgetPixelIntensity(img, x+1, y-1);
    vizinhanca[5] = IMAGEMgetPixelIntensity(img, x+1, y);
    vizinhanca[6] = IMAGEMgetPixelIntensity(img, x+1, y+1);
    vizinhanca[7] = IMAGEMgetPixelIntensity(img, x, y+1);
    vizinhanca[8] = IMAGEMgetPixelIntensity(img, x-1, y+1);

    return vizinhanca;
}

static void swap(unsigned int *array, int pos1, int pos2) {
    unsigned int temp = array[pos1];
    array[pos1] = array[pos2];
    array[pos2] = temp;
}


static void selectionSort(unsigned int *array, int n) {
    int i, j, minIdx;

    for (i=0; i<n-1; i++) {
        minIdx = i;

        for (j=i+1; j<n; j++) {
            if (array[j] < array[minIdx]) {
                minIdx = j;
            }
        }

        if (i != minIdx) {
            swap(array, i, minIdx);
        }
    }
}



/* Implementação de funções (EXTERNAS) */
/*
 DESCRIÇÃO: Deverá permitir a obtenção de uma nova instância de uma imagem preta.
*/
IMAGEM IMAGEMnew(int intCol, int intRow) {
    IMAGEM newImg;
    int linha;

    /* Aloca memória para a estrutura da Imagem */
    newImg = (IMAGEM)malloc(sizeof(struct s_imagem));
    if (!newImg) {
        perror("Erro na alocação de memória!\n");
        exit(EXIT_FAILURE);
    }

    /* Aloca memória para a Matriz da Imagem */
    newImg->arrMatrix = (unsigned int **)malloc(sizeof(unsigned int *) * intRow);
    if (!newImg->arrMatrix) {
        free(newImg);
        perror("Erro na alocação de memória!\n");
        exit(EXIT_FAILURE);
    }

    /* Aloca memória para cada linha da Matriz da Imagem */
    for (linha=0; linha<intRow; linha++) {
        newImg->arrMatrix[linha] = (unsigned int *)malloc(sizeof(unsigned int) * intCol);
        if (!newImg->arrMatrix[linha]) {
            /* Liberta memória alocada anteriormente */
            while (linha >= 0) {
                free(newImg->arrMatrix[--linha]);
            }
            free(newImg->arrMatrix);
            free(newImg);

            perror("Erro na alocação de memória");
            exit(EXIT_FAILURE);
        }

        /* Define os pixels da linha da imagem a preto */
        memset(newImg->arrMatrix[linha], 0, intCol);
    }



    /* Define o Magic Number do formato */
    IMAGEMsetFormat(newImg, "P2");

    /* Define as dimensões da Imagem */
    newImg->intCol = intCol;
    newImg->intRow = intRow;

    /* Define a intensidade máxima para a Imagem */
    IMAGEMsetMaxIntensity(newImg, DEFAULT_MAX_GRAY);


    return newImg;
}

/*
 DESCRIÇÃO: Permite a obtenção de uma nova instância de uma imagem, a partir de um ficheiro no formato PGM P2.
*/
IMAGEM IMAGEMnewFromFile(const char *chrFilename) {
    IMAGEM img = PGMopen(chrFilename);

    return img;
}


/*
 DESCRIÇÃO: Liberta os recursos relativos à imagem.
*/
void IMAGEMdestroy(IMAGEM img) {
    int linha;

    for (linha=0; linha<img->intRow; linha++) {
        free(img->arrMatrix[linha]);
    }

    free(img->arrMatrix);
    free(img);
}

/*
 DESCRIÇÃO: Define o formato da Imagem.
*/
void IMAGEMsetFormat(IMAGEM img, char *chrMagicNumber) {
    strcpy(img->magicNumber, chrMagicNumber);
}

/*
 DESCRIÇÃO: Obtém o formato da Imagem.
*/
char *IMAGEMgetFormat(IMAGEM img) {
    return img->magicNumber;
}

/*
 DESCRIÇÃO: Obtém a intensidade máxima possível permitida pela imagem.
*/
unsigned int IMAGEMgetMaxIntensity(IMAGEM img) {
    return img->intMaxGray;
}

/*
 DESCRIÇÃO: Define a intensidade máxima possível permitida pela imagem.
*/
void IMAGEMsetMaxIntensity(IMAGEM img, unsigned int intMaxGray) {
    img->intMaxGray = intMaxGray;
}

/*
 DESCRIÇÃO: Obtém número de linhas da imagem
*/
int IMAGEMgetRows(IMAGEM img) {
    return img->intRow;
}

/*
 DESCRIÇÃO: Obtém número de colunas da imagem
*/
int IMAGEMgetColumns(IMAGEM img) {
    return img->intCol;
}

/*
 DESCRIÇÃO: Define o valor da intensidade de um determinado pixel na imagem.
*/
void IMAGEMsetPixelIntensity(IMAGEM img, int coluna, int linha, unsigned int intensidade) {
    img->arrMatrix[linha][coluna] = intensidade;
}

/*
 DESCRIÇÃO: Obtém o valor da intensidade de um determinado pixel na imagem.
*/
unsigned int IMAGEMgetPixelIntensity(IMAGEM img, int coluna, int linha) {
    /* Verifica limites de colunas */
    if (coluna < 0) {
        coluna = img->intCol - 1;
    }
    else if (coluna >= img->intCol) {
        coluna = 0;
    }

    /* Verifica limites de linhas */
    if (linha < 0) {
        linha = img->intRow - 1;
    }
    else if (linha >= img->intRow) {
        linha = 0;
    }

    return img->arrMatrix[linha][coluna];
}


/*
 DESCRIÇÃO: Retorna a identidade de uma imagem, numa nova instância.
*/
IMAGEM IMAGEMgetIdentity(IMAGEM img) {
    int linha;
    IMAGEM newImg = IMAGEMnew(img->intCol, img->intRow);

    /* Define o Magic Number do formato */
    IMAGEMsetFormat(newImg, IMAGEMgetFormat(img));

    /* Define a intensidade máxima para a imagem */
    IMAGEMsetMaxIntensity(newImg, IMAGEMgetMaxIntensity(img));

    for (linha=0; linha<img->intRow; linha++) {
        /* Efectua a cópia da linha da imagem original para a de destino */
        memcpy(newImg->arrMatrix[linha], img->arrMatrix[linha], sizeof(unsigned int) * img->intCol);
    }

    return newImg;
}


/*
 DESCRIÇÃO: Retorna o negativo de uma imagem, numa nova instância.
*/
IMAGEM IMAGEMgetNegative(IMAGEM img) {
    int linha, coluna;
    IMAGEM newImg = IMAGEMnew(img->intCol, img->intRow);

    /* Define o Magic Number do formato */
    IMAGEMsetFormat(newImg, IMAGEMgetFormat(img));

    /* Define a intensidade máxima para a Imagem */
    IMAGEMsetMaxIntensity(newImg, IMAGEMgetMaxIntensity(img));

    for (linha=0; linha<img->intRow; linha++) {
        for (coluna=0; coluna<img->intCol; coluna++) {
            IMAGEMsetPixelIntensity(newImg, coluna, linha, IMAGEMgetMaxIntensity(img) - IMAGEMgetPixelIntensity(img, coluna, linha));
        }
    }

    return newImg;
}

/*
 DESCRIÇÃO: Retorna uma nova instância de uma imagem, com a intensidade máxima da vizinhança de cada pixel.
*/
IMAGEM IMAGEMgetMax(IMAGEM img) {
    int linha, coluna;
    int i;
    unsigned int *vizinhanca, pxTmp;
    IMAGEM newImg = IMAGEMnew(img->intCol, img->intRow);

    /* Define o Magic Number do formato */
    IMAGEMsetFormat(newImg, IMAGEMgetFormat(img));

    /* Define a intensidade máxima para a Imagem */
    IMAGEMsetMaxIntensity(newImg, IMAGEMgetMaxIntensity(img));

    for (linha=0; linha<img->intRow; linha++) {
        for (coluna=0; coluna<img->intCol; coluna++) {
            vizinhanca = getVizinhanca(img, coluna, linha);
            pxTmp = vizinhanca[0];
            for (i=1; i<MAX_VIZINHANCA; i++) {
                if (pxTmp < vizinhanca[i]) {
                    pxTmp = vizinhanca[i];
                }
            }
            IMAGEMsetPixelIntensity(newImg, coluna, linha, pxTmp);
        }
    }

    free(vizinhanca);

    return newImg;
}

/*
 DESCRIÇÃO: Retorna uma nova instância de uma imagem, com a intensidade mínima da vizinhança de cada pixel.
*/
IMAGEM IMAGEMgetMin(IMAGEM img) {
    int linha, coluna;
    int i;
    unsigned int *vizinhanca, pxTmp;
    IMAGEM newImg = IMAGEMnew(img->intCol, img->intRow);

    /* Define o Magic Number do formato */
    IMAGEMsetFormat(newImg, IMAGEMgetFormat(img));

    /* Define a intensidade máxima para a Imagem */
    IMAGEMsetMaxIntensity(newImg, IMAGEMgetMaxIntensity(img));

    for (linha=0; linha<img->intRow; linha++) {
        for (coluna=0; coluna<img->intCol; coluna++) {
            vizinhanca = getVizinhanca(img, coluna, linha);
            pxTmp = vizinhanca[0];
            for (i=1; i<MAX_VIZINHANCA; i++) {
                if (pxTmp > vizinhanca[i]) {
                    pxTmp = vizinhanca[i];
                }
            }
            IMAGEMsetPixelIntensity(newImg, coluna, linha, pxTmp);
        }
    }

    free(vizinhanca);

    return newImg;
}

/*
 DESCRIÇÃO: Retorna uma nova instância de uma imagem, com a intensidade média da vizinhança de cada pixel.
*/
IMAGEM IMAGEMgetMedia(IMAGEM img) {
    int linha, coluna;
    int i;
    unsigned int *vizinhanca, pxTmp;
    IMAGEM newImg = IMAGEMnew(img->intCol, img->intRow);

    /* Define o Magic Number do formato */
    IMAGEMsetFormat(newImg, IMAGEMgetFormat(img));

    /* Define a intensidade máxima para a Imagem */
    IMAGEMsetMaxIntensity(newImg, IMAGEMgetMaxIntensity(img));

    for (linha=0; linha<img->intRow; linha++) {
        for (coluna=0; coluna<img->intCol; coluna++) {
            vizinhanca = getVizinhanca(img, coluna, linha);

            pxTmp = 0;
            for (i=0; i<MAX_VIZINHANCA; i++) {
                pxTmp += vizinhanca[i];
            }
            pxTmp /= MAX_VIZINHANCA;
            IMAGEMsetPixelIntensity(newImg, coluna, linha, pxTmp);
        }
    }

    free(vizinhanca);

    return newImg;
}

/*
 DESCRIÇÃO: Retorna uma nova instância de uma imagem, com a intensidade mediana da vizinhança de cada pixel.
*/
IMAGEM IMAGEMgetMediana(IMAGEM img) {
    int linha, coluna;
    unsigned int *vizinhanca, pxTmp;
    IMAGEM newImg = IMAGEMnew(img->intCol, img->intRow);

    /* Define o Magic Number do formato */
    IMAGEMsetFormat(newImg, IMAGEMgetFormat(img));

    /* Define a intensidade máxima para a Imagem */
    IMAGEMsetMaxIntensity(newImg, IMAGEMgetMaxIntensity(img));

    for (linha=0; linha<img->intRow; linha++) {
        for (coluna=0; coluna<img->intCol; coluna++) {
            vizinhanca = getVizinhanca(img, coluna, linha);

            selectionSort(vizinhanca, MAX_VIZINHANCA);

            pxTmp = vizinhanca[MAX_VIZINHANCA/2];
            IMAGEMsetPixelIntensity(newImg, coluna, linha, pxTmp);
        }
    }

    free(vizinhanca);

    return newImg;
}

/*
 DESCRIÇÃO: Retorna uma imagem invertida horizontalmente, numa nova instância.
*/
IMAGEM IMAGEMflipHorizontal(IMAGEM img) {
    int linha, coluna;
    IMAGEM newImg = IMAGEMnew(img->intCol, img->intRow);

    /* Define o Magic Number do formato */
    IMAGEMsetFormat(newImg, IMAGEMgetFormat(img));

    /* Define a intensidade máxima para a Imagem */
    IMAGEMsetMaxIntensity(newImg, IMAGEMgetMaxIntensity(img));


    for (linha=0; linha<newImg->intRow; linha++) {
        memcpy(newImg->arrMatrix[linha], img->arrMatrix[linha], sizeof(unsigned int) * img->intCol);

        coluna = 0;
        while (coluna < (newImg->intCol-coluna-1)) {
            swap(newImg->arrMatrix[linha], coluna, newImg->intCol-coluna-1);
            coluna++;
        }

    }

    return newImg;
}

/*
 DESCRIÇÃO: Retorna uma imagem invertida verticalmente, numa nova instância.
*/
IMAGEM IMAGEMflipVertical(IMAGEM img) {
    int linha = 0;
    IMAGEM newImg = IMAGEMnew(img->intCol, img->intRow);

    /* Define o Magic Number do formato */
    IMAGEMsetFormat(newImg, IMAGEMgetFormat(img));

    /* Define a intensidade máxima para a Imagem */
    IMAGEMsetMaxIntensity(newImg, IMAGEMgetMaxIntensity(img));


    while (linha < (newImg->intRow-linha-1)) {
        /* Efectua uma cópia da imagem original, invertendo as posições */
        memcpy(newImg->arrMatrix[linha], img->arrMatrix[newImg->intRow - linha - 1], sizeof(unsigned int) * newImg->intCol);
        memcpy(newImg->arrMatrix[newImg->intRow - linha - 1], img->arrMatrix[linha], sizeof(unsigned int) * newImg->intCol);

        linha++;
    }

    return newImg;
}

/*
 DESCRIÇÃO: Retorna uma imagem rodada 90 graus no sentido do ponteiro do relógio, numa nova instância.
*/
IMAGEM IMAGEMrotate90(IMAGEM img) {
    /* Ao rodar 90º, reservar correctamente memória para as dimensões da matrix */
    IMAGEM newImg = IMAGEMnew(img->intRow, img->intCol);
    int coluna, linha;

    /* Define o Magic Number do formato */
    IMAGEMsetFormat(newImg, IMAGEMgetFormat(img));

    /* Define a intensidade máxima para a Imagem */
    IMAGEMsetMaxIntensity(newImg, IMAGEMgetMaxIntensity(img));

    /* Efectua a rotação de 90º da imagem no sentido do ponteiro do relógio */
    for (linha=0; linha<img->intCol; linha++) {
        for (coluna=0; coluna<img->intRow; coluna++) {
            IMAGEMsetPixelIntensity(newImg, coluna, linha, IMAGEMgetPixelIntensity(img, linha, img->intRow-1-coluna));
        }
    }

    return newImg;
}

/*
 DESCRIÇÃO: Retorna uma imagem rodada 180 graus no sentido do ponteiro do relógio, numa nova instância.
*/
IMAGEM IMAGEMrotate180(IMAGEM img) {
    IMAGEM newImg = IMAGEMnew(img->intCol, img->intRow);
    int coluna, linha;

    /* Define o Magic Number do formato */
    IMAGEMsetFormat(newImg, IMAGEMgetFormat(img));

    /* Define a intensidade máxima para a Imagem */
    IMAGEMsetMaxIntensity(newImg, IMAGEMgetMaxIntensity(img));

    /* Efectua a rotação de 180º da imagem no sentido do ponteiro do relógio */
    for (linha=0; linha<img->intRow; linha++) {
        for (coluna=0; coluna<img->intCol; coluna++) {
            IMAGEMsetPixelIntensity(newImg, coluna, linha, IMAGEMgetPixelIntensity(img, img->intCol-1-coluna, img->intRow-1-linha));
        }
    }

    return newImg;
}

/*
 DESCRIÇÃO: Retorna uma imagem rodada 270 graus no sentido do ponteiro do relógio, numa nova instância.
*/
IMAGEM IMAGEMrotate270(IMAGEM img) {
    /* Ao rodar 270º, reservar correctamente memória para as dimensões da matrix */
    IMAGEM newImg = IMAGEMnew(img->intRow, img->intCol);
    int coluna, linha;

    /* Define o Magic Number do formato */
    IMAGEMsetFormat(newImg, IMAGEMgetFormat(img));

    /* Define a intensidade máxima para a Imagem */
    IMAGEMsetMaxIntensity(newImg, IMAGEMgetMaxIntensity(img));

    /* Efectua a rotação de 270º da imagem no sentido do ponteiro do relógio */
    for (linha=0; linha<img->intCol; linha++) {
        for (coluna=0; coluna<img->intRow; coluna++) {
            IMAGEMsetPixelIntensity(newImg, coluna, linha, IMAGEMgetPixelIntensity(img, img->intCol-1-linha, coluna));
        }
    }

    return newImg;
}

/*
 DESCRIÇÃO: Retorna uma imagem convertida no formato oposto, numa nova instância.
*/
IMAGEM IMAGEMconvert(IMAGEM img) {
    IMAGEM newImg;

    /* Verifica se é possível converter */

    if (
        (strcmp(IMAGEMgetFormat(img), "P2") == 0) ||
        (((strcmp(IMAGEMgetFormat(img), "P5")==0) && (IMAGEMgetMaxIntensity(img) <= 255)))
    ) {
        /* Continua a conversão */
        newImg = IMAGEMgetIdentity(img);

        if (strcmp(IMAGEMgetFormat(img), "P2") == 0) {
            /* Converte P2 em P5 */
            IMAGEMsetFormat(newImg, "P5");
        }
        else {
            /* Converte P5 em P2 */
            IMAGEMsetFormat(newImg, "P2");
        }
    }
    else {
        /* Aborta a conversão */
        perror("Não é possível converter este formato.\n");

        /* Liberta a memória alocada pela imagem original */
        IMAGEMdestroy(img);

        exit(EXIT_FAILURE);
    }


    return newImg;
}
