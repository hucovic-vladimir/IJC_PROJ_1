/**
 * @file error.c
 * @name IJC - Domácí úkol 1, příklad b), 16.3.2022
 * @author Vladimír Hucovič, FIT
 * Přeloženo pomocí GCC verze 10.3.0
 */


#include "error.h"

void warning_msg(const char *fmt, ...){
    va_list list;
    va_start(list, fmt);
    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, list);
    va_end(list);
}

void error_exit(const char *fmt, ...){
    va_list list;
    va_start(list, fmt);
    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, list);
    va_end(list);
    exit(1);
}