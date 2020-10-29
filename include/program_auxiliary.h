/*
 * @Author: Yarin Avisidris 
 * @Date: 2020-10-29 00:29:43 
 * @Last Modified by: Yarin Avisidris
 * @Last Modified time: 2020-10-29 01:22:42
 */

#include <stdlib.h>		// malloc(), free()
#ifndef __PROGRAM_AUX__H__
#define __PROGRAM_AUX__H__

typedef unsigned char byte;

void free_and_null(void **ptr) {
    free((*ptr));
    (*ptr) = NULL;
}
#endif