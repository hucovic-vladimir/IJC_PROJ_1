/**
 * @file steg-decode.c
 * @name IJC - Domácí úkol 1, příklad b), 16.3.2022
 * @author Vladimír Hucovič, FIT
 * Přeloženo pomocí GCC verze 10.3.0
 */

#include "ppm.h"
#include "bitset.h"
#include <string.h>
#include <limits.h>

extern void Eratosthenes(bitset_t *pole);

#ifdef USE_INLINE
extern inline void bitset_free(bitset_t *jmeno_pole);

extern inline int bitset_getbit(bitset_t jmeno_pole, bitset_index_t index);

extern inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, int vyraz);

extern inline unsigned long int bitset_size(bitset_t jmeno_pole);
#endif
// nastavít nejvyšší bit charu c na hodnotu 0 nebo 1
char char_set_msbit(unsigned char c, int value){
    c >>= 1;
    if(value == 0){
        unsigned char mask = (unsigned char) ~0 >> 1;
        c &= mask;
        return c;
    }
    unsigned char mask = ~((unsigned char) ~0 >> 1);
    c |= mask;
    return c;
}
// vrací nejnižší bit charu c
int char_get_lsbit(unsigned char c){
    return c % 2;
}

// dekóduje zprávu v obrázku image, zakódovanou v prvočíselných bytech obrázku
void steg_decode(struct ppm *image){
    bitset_alloc(bitset, image->ysize * image->xsize * 3 * CHAR_BIT);
    Eratosthenes(bitset);
    int count = 0;
    char c = '\0';
    for (bitset_index_t i = 29; i < bitset_size(*bitset); ++i) {
        if(count >= 8){
            if(c == '\0'){
                printf("\n");
                bitset_free(bitset);
                return;
            }
            printf("%c", c);
            count = 0;
            c = '\0';
        }
        if(!(bitset_getbit(*bitset, i))){
            int lsbit = char_get_lsbit(image->data[i]);
            c = char_set_msbit(c, lsbit);
            count++;
        }
    }
    error_exit("Ve zprávě chybí ukončovací nulový byte! Konec programu.\n");
    bitset_free(bitset);
}


int main(int argc, char *argv[]){
    if(argc != 2){
        error_exit("Špatný počet argumentů! Použití: steg-decode <filename>\n");
    }
    struct ppm *data = ppm_read(argv[1]);
    if(!data){
        error_exit("Obrázek se nepodařilo načíst, konec programu.\n");
    }
    steg_decode(data);
    ppm_free(data);
    return 0;
}

