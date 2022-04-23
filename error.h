/**
 * @file error.h
 * @name IJC - Domácí úkol 1, příklad b), 16.3.2022
 * @author Vladimír Hucovič, FIT
 * Přeloženo pomocí GCC verze 10.3.0
 */

#ifndef IJC_ERROR_H
#define IJC_ERROR_H
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

void warning_msg(const char *fmt, ...);

void error_exit(const char *fmt, ...);

#endif
