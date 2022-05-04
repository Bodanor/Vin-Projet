#ifndef __UTIL_VIN_H
#define __UTIL_VIN_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/**
 * @brief   Function that can be used to safely write data from the stdin file.
 *
 * @param str   char pointer to a valid memory location
 * @param size_str  maximum size in bytes of the first valid parameter.
 * @return  0 : if user has interrupted the input by hitting Enter at the beginning.
 * @return  1 : if the input has successfully been written to destination memory location.
 */
short secureInput(char* str, int size_str);

short verifyInt(char *str, int str_length);

int openDatabase(FILE**srcFile, char *filename);
int verifyDate(char *buffer);
#endif
