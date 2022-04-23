/**
 * @file primes.c
 * @name IJC - Domácí úkol 1, příklad a), 16.3.2022
 * @author Vladimír Hucovič, FIT
 * Přeloženo pomocí GCC verze 10.3.0
 */

#include <time.h>
#include "bitset.h"
#include <stdio.h>
#define velikost 300000001

extern void Eratosthenes(bitset_t *pole);

#ifdef USE_INLINE
extern inline void bitset_free(bitset_t *jmeno_pole);

extern inline int bitset_getbit(bitset_t jmeno_pole, bitset_index_t index);

extern inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, int vyraz);

extern inline unsigned long int bitset_size(bitset_t jmeno_pole);

#endif


// tiskne (vzestupně) prvočísla, uložená v bitsetu
void print_primes(bitset_t *bitset){
    unsigned long int size = bitset_size(*bitset);
    unsigned long int primes[10] = {0};
    int primeCount = 0;
    for(bitset_index_t i = size; i > 0; --i){
        if(primeCount >= 10){
            break;
        }
        if(!(bitset_getbit(*bitset, (i - 1)))){
            primes[primeCount] = (i-1);
            primeCount++;
        }
    }
    for (int i = 9; i >= 0 ; --i) {
        if(primes[i]){
            printf("%ld\n", primes[i]);
        }
    }
}

int main(){
    bitset_create(set, velikost);
    Eratosthenes(&set);
    print_primes(&set);
    fprintf(stderr, "Time=%.3g\n", (double)(clock()) / CLOCKS_PER_SEC);
}