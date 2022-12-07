/**********************************
 PROGRAMAÇÃO IMPERATIVA
 Pedro Roldan, a21406840
 João Oliveira, a21406839
 Trabalho: PGM image processor
***********************************/
#ifndef _FILELIB_
    #define _FILELIB_

    #define P2_MAX_LINE 70
    #define COMMENT_MAX_LINE 1024

#endif
#ifndef _IMGLIB_
    #define _IMGLIB_

    typedef struct s_imagem *IMAGEM;
#endif

/*
DESCRIÇÃO: carrega ficheiro pgm existente no formato P2/P5
PRÉ: filename != NULL
PÓS: Retorna imagem
EXCEÇÃO: aborta caso não haja memória
*/
IMAGEM PGMopen(const char *filename);

/*
DESCRIÇÃO: grava ficheiro pgm no formato P2/P5
PRÉ: filename && img != NULL
PÓS:
EXCEÇÃO: aborta caso não seja possivel gravar em ficheiro
*/
void PGMsave(const char *filename, IMAGEM img);

/*
DESCRIÇÃO: devolve ficheiro com extensão PGM
PRÉ: filename != NULL
PÓS: retorna ficheiro com extensão .pgm
EXCEÇÃO:
*/
char *PGMsetFilenameExtension(char *filename);

