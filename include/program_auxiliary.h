/*
 * @Author: Yarin Avisidris 
 * @Date: 2020-10-29 00:29:43 
 * @Last Modified by: Yarin Avisidris
 * @Last Modified time: 2020-10-29 01:22:42
 */

#include <stdlib.h>		// malloc(), free()
#ifndef __PROGRAM_AUX__H__
#define __PROGRAM_AUX__H__

enum ErrorCode {
	//no error
	ERROR_SUCCESS = 0,
	// network errors
	ERROR_NET_SOCKET_API,
	ERROR_NET_BIND_API,
	ERROR_NET_LISTEN_API,
	ERROR_NET_WRITE_API,
	ERROR_NET_ACCEPT_API,
	ERROR_NET_READ_API,
	// heap memory allocation errors
	ERROR_MEM_MALLOC_NULL,
	// arguments error
	ERROR_NULL_ARGUMENT,
	ERROR_BAD_ARGUMENTS,
};
void free_and_null(void **ptr) {
    free((*ptr));
    (*ptr) = NULL;
}

#endif