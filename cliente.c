**********************************
 PROGRAMAÇÃO IMPERATIVA
 Pedro Roldan, a21406840
 João Oliveira, a21406839
 Trabalho: PGM image processor
***********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imglib.h"

void printHelp() {
    printf("Uso: pgm -i filename [-o filename [OPCOES]] [-info [maxcol][maxlin][maxgray][format]]\n\n");
    printf("Opção           Descrição\n");
    printf(" -h,--help      Lista completa de comandos\n");
    printf(" -i filename    Carrega ficheiro de imagem PGM\n");
    printf(" -info maxcol   Indica número de colunas(width) do ficheiro PGM\n");
    printf(" -info maxlin   Indica número de linhas(height) do ficheiro PGM\n");
    printf(" -info maxgray  Indica valor de grayscale (intensidade) do ficheiro PGM\n");
    printf(" -info format   Indica formato do ficheiro PGM\n");
    printf(" -rodar 90      Roda a imagem em 90º (sentido ponteiros do relogio) PGM\n");
    printf(" -rodar 180     Roda a imagem em 180º (sentido ponteiros do relogio) PGM\n");
    printf(" -rodar 270     Roda a imagem em 270º (sentido ponteiros do relogio) PGM\n");
    printf(" -op negativo   Negativo da imagem PGM\n");
    printf(" -op convert    Converte imagem PGM entre formatos P2<=>P5\n");
    printf(" -op maximo     Máximo da imagem PGM\n");
    printf(" -op minimo     Minimo da imagem PGM\n");
    printf(" -op media      Media da imagem PGM\n");
    printf(" -op mediana    Mediana da imagem PGM\n");
    printf(" -op ident      Devolve duplicado da imagem PGM\n");
    printf(" -op fliph      Transforma horizontalmente a imagem PGM\n");
    printf(" -op flipv      Transforma verticalmente a imagem PGM\n");
    printf(" -o filename    Cria ficheiro de imagem PGM\n");
}

int main(int argc, char *argv[]) {
    IMAGEM PGMImagemOrigem, PGMImagemDestino;
    char *chrFilename;
    char *chrFilenameSave;
    int FileLoad=0,FileLoadFilename=0,FileSave=0,FileSaveFilename=0,FileInfo=0,FileInfoOpcoes=0;
    int FileImage=0,FileImageOpcoes=0,FileImageRotate=0,FileImageRotateOpcoes=0;
    int count;


    if (argc > 1) { /* Valida número de argumentos */

        for (count=1; count<argc; count++) {

            /* Valida opção --help */
            if ((strcmp(argv[count], "--help") == 0) || (strcmp(argv[count], "-h") == 0)) {
                printHelp();
                exit(EXIT_SUCCESS);
            }
            else if (strcmp(argv[count], "-i") == 0) {   /* Valida opção -i load file */
                FileLoad = 1;   /* carrega a flag de -i com true */

                if (count+1 < argc) {
                    chrFilename = argv[count+1];
                    FileLoadFilename = 1;   /* carrega flag de nome de ficheiro com true */
                }
                else {
                    printf("Uso: -i [filename]\n");
                    exit(EXIT_SUCCESS);
                }
            }
            else if (strcmp(argv[count], "-o") == 0) {  /* Valida opção -o save file*/
                FileSave = 1;   /* carrega a flag de -o com true */

                if (count+1 < argc) {
                    chrFilenameSave = PGMsetFilenameExtension(argv[count+1]);
                    FileSaveFilename = 1;   /* carrega flag de nome de ficheiro com true */
                }
                else {
                    printf("Uso: -o [filename]\n");
                    exit(EXIT_SUCCESS);
                }
            }
            else if (strcmp(argv[count], "-info") == 0) {   /* Valida opção -info file information*/
                FileInfo = 1;

                if (count+1 < argc) {
                    if (strcmp(argv[count+1], "maxcol") == 0) {
                        FileInfoOpcoes = 1;
                    }
                    else if (strcmp(argv[count+1], "maxlin") == 0) {
                        FileInfoOpcoes = 2;
                    }
                    else if (strcmp(argv[count+1], "maxgray") == 0) {
                        FileInfoOpcoes = 3;
                    }
                    else if (strcmp(argv[count+1], "format") == 0) {
                        FileInfoOpcoes = 4;
                    }
                    else {
                        printf("Uso: -info [maxcol][maxlin][maxgray][format]\n");
                        exit(EXIT_SUCCESS);
                    }
                }
                else {
                    printf("Uso: -info [maxcol][maxlin][maxgray][format]\n");
                    exit(EXIT_SUCCESS);
                }
            }
            else if (strcmp(argv[count], "-op") == 0) { /* Valida opção -op  image options */
                FileImage = 1;

                if (count+1 < argc) {
                    if (strcmp(argv[count+1], "negativo") == 0) {
                        FileImageOpcoes = 1;
                    }
                    else if (strcmp(argv[count+1], "maximo") == 0) {
                        FileImageOpcoes = 2;
                    }
                    else if (strcmp(argv[count+1], "minimo") == 0) {
                        FileImageOpcoes = 3;
                    }
                    else if (strcmp(argv[count+1], "media") == 0) {
                        FileImageOpcoes = 4;
                    }
                    else if (strcmp(argv[count+1], "mediana") == 0) {
                        FileImageOpcoes = 5;
                    }
                    else if (strcmp(argv[count+1], "fliph") == 0) {
                        FileImageOpcoes = 6;
                    }
                    else if (strcmp(argv[count+1], "flipv") == 0) {
                        FileImageOpcoes = 7;
                    }
                    else if (strcmp(argv[count+1], "convert") == 0) {
                        FileImageOpcoes = 8;
                    }
                    else if (strcmp(argv[count+1], "ident") == 0) {
                        FileImageOpcoes = 9;
                    }
                    else {
                        printf("Uso: -op [negativo][maximo][minimo][media][mediana][fliph][flipv][convert][ident]\n");
                        exit(EXIT_SUCCESS);
                    }
                }
                else {
                    printf("Uso: -op [negativo][maximo][minimo][media][mediana][fliph][flipv][convert][ident]\n");
                    exit(EXIT_SUCCESS);
                }
            }
            else if (strcmp(argv[count], "-rodar") == 0) {  /* Valida opção -rodar image rotation */
                FileImageRotate = 1;

                if (count+1 < argc) {
                    if (strcmp(argv[count+1], "90") == 0) {
                        FileImageRotateOpcoes = 1;
                    }
                    else if (strcmp(argv[count+1], "180") == 0) {
                        FileImageRotateOpcoes = 2;
                    }
                    else if (strcmp(argv[count+1], "270") == 0) {
                        FileImageRotateOpcoes = 3;
                    }
                    else {
                        printf("Uso: -rodar [90][180][270]\n");
                        exit(EXIT_SUCCESS);
                    }
                }
                else {
                    printf("Uso: -rodar [90][180][270]\n");
                    exit(EXIT_SUCCESS);
                }
            }
        }



        /* Valida conjunto de opções escolhidas */
        if (
            (!FileLoad && !FileLoadFilename) /* Obrigatório ficheiro de entrada */
            || (!FileSave && !FileSaveFilename && !(FileInfo && (FileInfoOpcoes >= 1) && (FileInfoOpcoes <= 4))) /* Obrigatório ficheiro de saída, com excepção do comando -info */

            || ( /* Obrigatório ter uma operação de processamento de imagem */
                FileLoad && FileLoadFilename && FileSave && FileSaveFilename
                && !(
                    (FileImage && (FileImageOpcoes >= 1) && (FileImageOpcoes <=9))
                    || (FileImageRotate && (FileImageRotateOpcoes >= 1) && (FileImageRotateOpcoes <= 3))
                )
            )

            || (    /* Obrigatório comando de operações de imagem (Info, Transformação, Rotação) */
                ((!FileInfo) && (FileInfoOpcoes < 1) && (FileInfoOpcoes > 4))
                && ((!FileImage) && (FileImageOpcoes < 1) && (FileImageOpcoes > 9))
                && ((!FileImageRotate) && (FileImageRotateOpcoes < 1) && (FileImageRotateOpcoes > 3))
            )

            || ( /* Proibido todos os tipos de comandos de operações de imagem ao mesmo tempo */
                (FileInfo && (FileInfoOpcoes >= 1) && (FileInfoOpcoes <= 4))
                && (FileImage && (FileImageOpcoes >= 1) && (FileImageOpcoes <=9))
                && (FileImageRotate && (FileImageRotateOpcoes >= 1) && (FileImageRotateOpcoes <= 3))
            )

            || ( /* Proibido ter mais de um tipo de comandos de operações de imagem ao mesmo tempo */
                (FileInfo && (FileInfoOpcoes >= 1) && (FileInfoOpcoes <= 4))
                && (FileImage && (FileImageOpcoes >= 1) && (FileImageOpcoes <= 9))
            )

            || ( /* Proibido ter mais de um tipo de comandos de operações de imagem ao mesmo tempo */
                (FileInfo && (FileInfoOpcoes >= 1) && (FileInfoOpcoes <= 4))
                && (FileImageRotate && (FileImageRotateOpcoes >= 1) && (FileImageRotateOpcoes <= 3))
            )

            || ( /* Proibido ter mais de um tipo de comandos de operações de imagem ao mesmo tempo */
                (FileImage && (FileImageOpcoes >= 1) && (FileImageOpcoes <= 9))
                && (FileImageRotate && (FileImageRotateOpcoes >= 1) && (FileImageRotateOpcoes <= 3))
            )
        ) {
            printHelp();
            exit(EXIT_SUCCESS);
        }

    }
    else {
        printf("Uso: --help para uma lista completa de comandos.\n");
        exit(EXIT_SUCCESS);
    }





    if (FileLoad && FileLoadFilename) { /* flag -i file load */
        PGMImagemOrigem = IMAGEMnewFromFile(chrFilename);

        if (FileInfo) { /* flag -info file information*/
            switch(FileInfoOpcoes) {
                case 1: /* maxcol */
                    printf("A imagem tem colunas(width)=%d\n", IMAGEMgetColumns(PGMImagemOrigem));
                    break;
                case 2: /* maxlin */
                    printf("A imagem tem linhas(height)=%d\n", IMAGEMgetRows(PGMImagemOrigem));
                    break;
                case 3: /* maxgray */
                    printf("A imagem tem grayscale(intensidade)=%d\n", IMAGEMgetMaxIntensity(PGMImagemOrigem));
                    break;
                case 4: /* format */
                    printf("A imagem tem o formato=%s\n", IMAGEMgetFormat(PGMImagemOrigem));
                    break;
            }
        }

        if ( (FileSave) && (FileSaveFilename) ) { /* flag -o file save */

            if (FileImage) { /* flag -op image options */
                switch(FileImageOpcoes) {
                    case 1: /* negativo */
                        PGMImagemDestino = IMAGEMgetNegative(PGMImagemOrigem);
                        break;
                    case 2: /* maximo */
                        PGMImagemDestino = IMAGEMgetMax(PGMImagemOrigem);
                        break;
                    case 3: /* minimo */
                        PGMImagemDestino = IMAGEMgetMin(PGMImagemOrigem);
                        break;
                    case 4: /* media */
                        PGMImagemDestino = IMAGEMgetMedia(PGMImagemOrigem);
                        break;
                    case 5: /* mediana */
                        PGMImagemDestino = IMAGEMgetMediana(PGMImagemOrigem);
                        break;
                    case 6: /* fliph */
                        PGMImagemDestino = IMAGEMflipHorizontal(PGMImagemOrigem);
                        break;
                    case 7: /* flipv */
                        PGMImagemDestino = IMAGEMflipVertical(PGMImagemOrigem);
                        break;
                    case 8: /* convert */
                        PGMImagemDestino = IMAGEMconvert(PGMImagemOrigem);
                        break;
                    case 9: /* ident */
                        PGMImagemDestino = IMAGEMgetIdentity(PGMImagemOrigem);
                        break;
                }
            }

            if (FileImageRotate) { /* flag -rodar image rotate */
                switch(FileImageRotateOpcoes) {
                    case 1: /* rotacao imagem 90º */
                        PGMImagemDestino = IMAGEMrotate90(PGMImagemOrigem);
                        break;
                    case 2: /* rotacao imagem 180º */
                        PGMImagemDestino = IMAGEMrotate180(PGMImagemOrigem);
                        break;
                    case 3: /* rotacao imagem 270º */
                        PGMImagemDestino = IMAGEMrotate270(PGMImagemOrigem);
                        break;
                }
            }

            PGMsave(chrFilenameSave, PGMImagemDestino); /* efetua gravacao da nova instacia da imagem */
            IMAGEMdestroy(PGMImagemDestino); /* destroi imagem destino */

            printf("\nProcessado por: Pedro Roldan & João Oliveira pgm image processor ISMAT PI 2015\n");
        }

        IMAGEMdestroy(PGMImagemOrigem); /* destroi imagem original */
    }
    else {
        printHelp();
    }

   return 0;
}
