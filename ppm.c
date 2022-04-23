/**
 * @file ppm.c
 * @name IJC - Domácí úkol 1, příklad b), 16.3.2022
 * @author Vladimír Hucovič, FIT
 * Přeloženo pomocí GCC verze 10.3.0
 */

#include <stdlib.h>
#include "error.h"
#include "ppm.h"
#include <stdio.h>
#include <string.h>

#define IMAGE_SIZE_LIMIT 8000*8000*3

// přečte obsah souboru filename a v případě úspěchu vrací strukturu ppm s daty načtenými z obrázku
struct ppm *ppm_read(const char *filename){
    struct ppm *content = calloc(1, sizeof(struct ppm));
    FILE *f = fopen(filename, "rb");
    if(!f){
        warning_msg("Soubor neexistuje / nemohl být načten!\n");
        goto error;
    }
    if(fscanf(f, "P6 %u %u 255 ", &(content->xsize), &(content->ysize)) != 2){
        warning_msg("Neplatný formát souboru! Je podporován pouze soubor PPM typu P6 s 0-255 barvami.\n");
        goto error;
    }
    if(content->xsize * content->ysize * 3 > IMAGE_SIZE_LIMIT){
        warning_msg("Maximální velikost obrázku je %d bytů!\n", IMAGE_SIZE_LIMIT);
        goto error;
    }
    struct ppm *new_content = realloc(content, sizeof(struct ppm) + (content->xsize * content->ysize * 3));
    if(new_content != NULL){
        content = new_content;
    }
    else{
        warning_msg("Nepodařilo se alokovat paměť!\n");
        goto error;
    }

    unsigned long bytesRead = fread(content->data, 1, content->xsize * content->ysize * 3,f);
    if(bytesRead != content->xsize * content->ysize * 3){
        warning_msg("Velikost v hlavičce obrázku nesedí se skutečnou velikostí dat v obrázku!\n");
        goto error;
    }

    return content;

    error:
        if(f){
            fclose(f);
        }
        if(content){
            ppm_free(content);
        }
        return NULL;
}

// uvolní ppm strukturu "p"
void ppm_free(struct ppm *p){
    free(p);
}


