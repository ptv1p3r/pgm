/**********************************
 PROGRAMAÇÃO IMPERATIVA
 Pedro Roldan, a21406840
 João Oliveira, a21406839
 Trabalho: PGM image processor
***********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "filelib.h"
#include "imglib.h"

#ifndef _DATA_TYPE_
    #define _DATA_TYPE_

    #define HI(num) (((num) & 0x0000FF00) >> 8) /* high byte */
    #define LO(num) ((num) & 0x000000FF)        /* low byte */

#endif

/* Protótipos de funções estáticas (INTERNAS) */
static void PGMsetHeader(IMAGEM img, FILE *pgmFile);
static void PGMsetP2P5(IMAGEM img, FILE *pgmFile);
static void PGMsaveMultibyteP5(IMAGEM img, FILE *pgmFile);
static void PGMload(IMAGEM img, FILE *pgmFile);
static void PGMloadMultibyteP5(IMAGEM img, FILE *pgmFile);
static void PGMjumpComments(FILE *pgmFile);
char *PGMsetFilenameExtension(char *chrFileName);

/*
DESCRIÇÃO: carrega ficheiro pgm existente no formato P2/P5
*/
IMAGEM PGMopen(const char *chrFileName){
    int colunas, linhas, maxGray;
    FILE *pgmFile;
    IMAGEM img;
    char magicNumber[3];

    /* abertura de ficheiro */
    pgmFile = fopen(chrFileName, "rb");
    if (!pgmFile) {
        perror("Erro impossivel abrir ficheiro para leitura!");
        exit(EXIT_FAILURE);
    }

    /*Leitura de formato de PGM do header do ficheiro*/
    fgets(magicNumber, sizeof(magicNumber), pgmFile);

    /* valida formato do ficheiro p2/p5? */
    if (!(strcmp(magicNumber, "P2")==0 || strcmp(magicNumber, "P5")==0)) {
        perror("Erro impossivel abrir ficheiro para leitura!");
        exit(EXIT_FAILURE);
    }

    /* ignora comentarios caso exista*/
    PGMjumpComments(pgmFile);

    /* retorna colunas e linhas do header do ficheiro */
    fscanf(pgmFile, "%d %d", &colunas, &linhas);

    img = IMAGEMnew(colunas, linhas); /* Inicializa nova imagem */
    IMAGEMsetFormat(img,magicNumber); /* Define formato da nova imagem */

    PGMjumpComments(pgmFile);  /* ignora comentarios */
    fscanf(pgmFile,"%d", &maxGray); /* retorna max gray intensidade */

    IMAGEMsetMaxIntensity(img, maxGray); /* Define intensidade máxima*/

    /* se valor maxgray >255 = 2bytes
       se valor maxgray <255 = 1byte
    */
    if (IMAGEMgetMaxIntensity(img) > 255){

        /* formato P5 multibyte*/
        if(strcmp(IMAGEMgetFormat(img), "P5")==0){
            PGMloadMultibyteP5(img,pgmFile);
        } else {
            perror("Erro: ficheiro PGM não suportado com profundidade de 16 bits");
            IMAGEMdestroy(img);
            fclose(pgmFile);
            exit(EXIT_FAILURE);
        }

    } else {
        /* formato P2/P5 */
        PGMload(img,pgmFile);
    }

    fclose(pgmFile);
    return img;
}

/*
DESCRIÇÃO: grava ficheiro pgm P2/P5
*/
void PGMsave(const char *chrFileName, IMAGEM img){
    FILE *pgmFile;

    /* abertura de ficheiro para escrita mediante formato P2/P5 */
    if(strcmp(IMAGEMgetFormat(img), "P2")==0){
        pgmFile = fopen(chrFileName, "w"); /* formato p2 ascii */
    } else {
        pgmFile = fopen(chrFileName, "wb"); /* formato p5 binario */
    }

    if (!pgmFile) {
        perror("Erro impossivel criar ficheiro!\n");
        exit(EXIT_FAILURE);
    }

    /* escreve header do ficheiro */
    PGMsetHeader(img,pgmFile);

    /* se valor maxgray >255 = 2bytes
       se valor maxgray <255 = 1byte
    */
    if (IMAGEMgetMaxIntensity(img) > 255) {

        /* formato P5 multibyte*/
        if(strcmp(IMAGEMgetFormat(img), "P5")==0){
                PGMsaveMultibyteP5(img,pgmFile);
        } else {
            perror("Erro: formato PGM não suportado com profundidade de 16 bits");
            IMAGEMdestroy(img);
            fclose(pgmFile);
            exit(EXIT_FAILURE);
        }

    } else {
        /* formato P2/P5 */
        PGMsetP2P5(img,pgmFile);
    }

    fclose(pgmFile);
}

/*
DESCRIÇÃO: escreve header para o ficheiro pgm P2/P5
*/
static void PGMsetHeader(IMAGEM img, FILE *pgmFile){
    fprintf(pgmFile, "%s \n",IMAGEMgetFormat(img));
    fprintf(pgmFile, "#Processado por: Pedro Roldan & Joao Oliveira pgm image processor ISMAT PI 2015\n");
    fprintf(pgmFile, "%d %d \n", IMAGEMgetColumns(img), IMAGEMgetRows(img));
    fprintf(pgmFile, "%d \n", IMAGEMgetMaxIntensity(img));
}

/*
DESCRIÇÃO: escreve imagem no formato P2/P5 para  o ficheiro
*/
static void PGMsetP2P5(IMAGEM img, FILE *pgmFile){
    int i,j,lo,intLineCount=0;
    char chrValor[10];

    for (i = 0; i < IMAGEMgetRows(img); ++i)
        for (j = 0; j < IMAGEMgetColumns(img); ++j) {

            lo = LO(IMAGEMgetPixelIntensity(img, j, i));

            /* escrita em ficheiro pgm com formato P2 */
            if(strcmp(IMAGEMgetFormat(img), "P2")==0){
                sprintf(chrValor, "%d", IMAGEMgetPixelIntensity(img, j, i));

                /* valida tamanho maximo de linha */
                if ((intLineCount + strlen(chrValor) + 1) >= P2_MAX_LINE) {
                    /* Atingiu limite de caracteres numa linha do ficheiro */
                    intLineCount = 0;
                } else {
                    intLineCount += strlen(chrValor);
                }

                if (intLineCount > 0) {
                    intLineCount++;
                } else {
                    fprintf(pgmFile, "\n"); /* Nova linha no ficheiro */
                }

                fprintf(pgmFile, "%d ", lo);

                } else { /* escrita em ficheiro pgm com formato P5 */
                    fputc(lo, pgmFile);
                }
        }
}

/*
DESCRIÇÃO: grava ficheiro pgm P5 em multibyte
*/
static void PGMsaveMultibyteP5(IMAGEM img, FILE *pgmFile){
    int i,j,hi,lo;

    for (i = 0; i < IMAGEMgetRows(img); ++i) {
        for (j = 0; j < IMAGEMgetColumns(img); ++j) {

            hi = HI(IMAGEMgetPixelIntensity(img, j, i));
            lo = LO(IMAGEMgetPixelIntensity(img, j, i));

            fputc(hi, pgmFile);
            fputc(lo, pgmFile);
        }
    }
}

/*
DESCRIÇÃO: carrega ficheiro pgm P5 em multibyte
*/
static void PGMloadMultibyteP5(IMAGEM img, FILE *pgmFile){
    int i,j,hi,lo;

    for (i = 0; i < IMAGEMgetRows(img); ++i) {
        for (j = 0; j < IMAGEMgetColumns(img); ++j) {
            hi = fgetc(pgmFile);
            lo = fgetc(pgmFile);
            IMAGEMsetPixelIntensity(img, j, i, (hi << 8) + lo);
        }
    }
}

/*
DESCRIÇÃO: carrega ficheiro pgm existente no formato P2/P5
*/
static void PGMload(IMAGEM img, FILE *pgmFile){
    int i,j,lo;

    for (i = 0; i < IMAGEMgetRows(img); ++i){
        for (j = 0; j < IMAGEMgetColumns(img); ++j) {
                /* leitura de pgm com formato P2 */
            if(strcmp(IMAGEMgetFormat(img), "P2")==0){
                fscanf(pgmFile, "%d", &lo);
            } else { /* leitura de pgm com formato P5 */
                lo=fgetc(pgmFile);
            }
                IMAGEMsetPixelIntensity(img, j, i, lo);
        }
    }
}

/*
DESCRIÇÃO: salta linhas de comentários no ficheiro pgm
*/
static void PGMjumpComments(FILE *pgmFile){
    int intMarcador;
    char chrLinha[COMMENT_MAX_LINE]; /* 1025 bytes para acomodar a leitura do \0 e apenas le 1024 */

    while ((intMarcador = fgetc(pgmFile)) != EOF && isspace(intMarcador));
    if (intMarcador == '#') { /* identifica inicio de comentarios */
        fgets(chrLinha, sizeof(chrLinha), pgmFile);
        PGMjumpComments(pgmFile);
    } else {
        fseek(pgmFile, -1, SEEK_CUR); /* set do cursor */
    }
}

/*
DESCRIÇÃO: verifica a extencao de ficheiro PGM
*/
char *PGMsetFilenameExtension(char *chrFileName) {
    char *ponto=strrchr(chrFileName,'.');
    char *retorno;

    if ((ponto != NULL) && (strcmp(ponto, ".pgm") == 0)) {
        return "";
    }
    else if ((ponto != NULL) && (strcmp(ponto, ".") == 0)) {
        retorno = (char *)malloc(strlen(chrFileName) + 3 + 1);
        if (!retorno) {
            perror("Erro: memória insuficiente\n");
            exit(EXIT_FAILURE);
        }

        strcpy(retorno, chrFileName);
        strcat(retorno, "pgm");
    }
    else {
        /* Reserva memória com tamanho do nome do ficheiro + extensao + '\0'*/
        retorno = (char *)malloc(strlen(chrFileName) + 4 + 1);
        if (!retorno) {
            perror("Erro: memória insuficiente\n");
            exit(EXIT_FAILURE);
        }

        strcpy(retorno, chrFileName);
        strcat(retorno, ".pgm");
    }

    return retorno;
}
