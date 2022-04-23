/**
 * @file eratosthenes.c
 * @name IJC - Domácí úkol 1, příklad a), 16.3.2022
 * @author Vladimír Hucovič, FIT
 * Přeloženo pomocí GCC verze 10.3.0
 */


#include "bitset.h"
#include <math.h>

// nastaví bity na neprvočíselných indexech v bitsetu "pole" na 1. Prvočíselné indexy obsahují hodnotu 0.
void Eratosthenes(bitset_t *pole){
    bitset_setbit(*pole, 0, 1);
    bitset_setbit(*pole, 1, 1);
    bitset_index_t size = bitset_size(*pole);
    bitset_index_t endIndex = sqrt(size);
    for (bitset_index_t i = 0; i <= endIndex; ++i) {
        if(bitset_getbit(*pole, i) == 0) {
            for (bitset_index_t j = i + i; j < size; j+=i) {
                bitset_setbit(*pole, j, 1);
            }
        }
    }
}