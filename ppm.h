/**
 * @file ppm.h
 * @name IJC - Domácí úkol 1, příklad b), 16.3.2022
 * @author Vladimír Hucovič, FIT
 * Přeloženo pomocí GCC verze 10.3.0
 */

#ifndef IJC_PPM_H
#define IJC_PPM_H

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];
};

struct ppm *ppm_read(const char *filename);

void ppm_free(struct ppm *p);

#endif
