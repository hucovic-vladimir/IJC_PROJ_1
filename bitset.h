/**
 * @file bitset.h
 * @name IJC - Domácí úkol 1, příklad a), 16.3.2022
 * @author Vladimír Hucovič, FIT
 * Přeloženo pomocí GCC verze 10.3.0
 */

#ifndef IJC_BITSET_H
#define IJC_BITSET_H

#include <stdlib.h>
#include <stdbool.h>
#include "error.h"
#include <assert.h>
#include <stdio.h>
#include <limits.h>

#define LONG_INT_BITS_SIZE (sizeof(unsigned long int)*CHAR_BIT)

typedef unsigned long int bitset_t[];

typedef unsigned long int bitset_index_t;

void Eratosthenes(bitset_t *jmeno_pole);

extern void error_exit(const char *fmt, ...);

// vytvoří proměnnou bitset_t s názvem prvního argumentu o velikosti druhého argumentu, pole vynuluje a uloží jeho velikost
// na první index
#define bitset_create(jmeno_pole, velikost)\
         static_assert(velikost > 0, "Velikost pole musí být vyšší než 0!"); \
         unsigned long int jmeno_pole[velikost / LONG_INT_BITS_SIZE + ((velikost % LONG_INT_BITS_SIZE ? 2 : 1))] = {0}; \
         jmeno_pole[0] = velikost;            \

// vytvoří proměnnou bitset_t s názvem prvního argumentu o velikosti druhého argumentu, ale dynamicky a pole vynuluje a uloží jeho velikost
// na první index
#define bitset_alloc(jmeno_pole, velikost) \
        assert(velikost > 0);\
        bitset_t *jmeno_pole = calloc((velikost / LONG_INT_BITS_SIZE) + (velikost % LONG_INT_BITS_SIZE ? 2 : 1), sizeof(unsigned long int)); \
        (*jmeno_pole)[0] = velikost;       \
        if(jmeno_pole == NULL){            \
            fprintf(stderr, "bitset_alloc: Chyba alokace paměti");\
        }

// pokud je definován symbol USE_INLINE, místo maker jsou použity inline funkce
#ifdef USE_INLINE
inline void bitset_free(bitset_t *jmeno_pole){
    free(jmeno_pole);
}

inline unsigned long int bitset_size(bitset_t jmeno_pole){
    return *jmeno_pole;
}

inline int bitset_getbit(bitset_t jmeno_pole, bitset_index_t index){
    if(index >= bitset_size(jmeno_pole)){
        error_exit("Index %lu mimo rozsah 0..%lu !\n", (unsigned long) index, (unsigned long) bitset_size(jmeno_pole)-1);
    }
    int real_index;
    real_index = (index / LONG_INT_BITS_SIZE) + 1;
    return ~((unsigned int) ~0 << 1) & (jmeno_pole[real_index] >> (LONG_INT_BITS_SIZE - (index % LONG_INT_BITS_SIZE) - 1));
}

inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, int vyraz){
    if(index >= bitset_size(jmeno_pole)){
        error_exit("Index %lu mimo rozsah 0..%lu !\n", (unsigned long) index, (unsigned long) bitset_size(jmeno_pole) - 1);
    }
    if(vyraz != 0){
        vyraz = 1;
    }
    int real_index;
    real_index = (index / LONG_INT_BITS_SIZE) + 1;
    jmeno_pole[real_index] &= ~(1ul << (LONG_INT_BITS_SIZE - (index % LONG_INT_BITS_SIZE) - 1));
    jmeno_pole[real_index] = jmeno_pole[real_index] | ((unsigned long int) vyraz << (LONG_INT_BITS_SIZE - (index % LONG_INT_BITS_SIZE) - 1));
}

#else
// vrací velikost bitsetu "jmeno_pole"
#define bitset_size(jmeno_pole) *jmeno_pole

// uvolní dynamicky alokovaný bitset
#define bitset_free(jmeno_pole) free(jmeno_pole)

// získá z bitsetu "jmeno_pole" bit na indexu "index"
#define bitset_getbit(jmeno_pole, index) \
        index >= bitset_size(jmeno_pole) ? error_exit("Index %lu mimo rozsah 0..%lu !\n", \
            (unsigned long) index, (unsigned long) (bitset_size(jmeno_pole)-1)), -1ul : \
        (~((unsigned long int) ~0 << 1) & (((jmeno_pole)[(index / LONG_INT_BITS_SIZE) + 1] >> (LONG_INT_BITS_SIZE - (index % LONG_INT_BITS_SIZE) - 1)))) \

// nastaví bit v bitsetu "jmeno_pole" na indexu "index" na hodnotu "vyraz"
#define bitset_setbit(jmeno_pole, index, vyraz) do { \
        if(index >= bitset_size(jmeno_pole)){ \
            error_exit("Index %lu mimo rozsah 0..%lu !\n", \
            (unsigned long) index, (unsigned long) (bitset_size(jmeno_pole)-1)); \
        } \
        int real_index; \
        real_index = (index / LONG_INT_BITS_SIZE) + 1;     \
        (jmeno_pole)[real_index] &= ~(1ul << (LONG_INT_BITS_SIZE - (index % LONG_INT_BITS_SIZE) - 1)); \
        if((vyraz) != 0){                            \
           (jmeno_pole)[real_index] |= (1ul << (LONG_INT_BITS_SIZE - (index % LONG_INT_BITS_SIZE) - 1)); \
        }                                             \
         \
} while (0)

#endif
#endif
