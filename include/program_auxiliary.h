/*
 * @Author: Yarin Avisidris 
 * @Date: 2020-10-29 00:29:43 
 * @Last Modified by: Yarin Avisidris
 * @Last Modified time: 2020-11-07 18:04:36
 */
#include <stdlib.h>		// malloc(), free()
#include <stdbool.h>
#ifndef __PROGRAM_AUX__H__
#define __PROGRAM_AUX__H__
typedef unsigned char byte;
//this is struct for string, no need null byte for terminating, instead we save the size of it.
struct string {
	char *s;
	byte size;
};
enum ErrorCode {
	//no error:
	ERROR_SUCCESS = 0,
	// network errors:
	ERROR_NET_SOCKET_API,
	ERROR_NET_BIND_API,
	ERROR_NET_LISTEN_API,
	ERROR_NET_WRITE_API,
	ERROR_NET_ACCEPT_API,
	ERROR_NET_READ_API,
	ERROR_NET_CLOSE_API,
	// heap memory allocation errors:
	ERROR_MEM_MALLOC_NULL,
    // logic memory errors:
    ERROR_MEM_MIGHT_BE_INITIALIZED,
	// arguments error:
	ERROR_NULL_ARGUMENT,
	ERROR_BAD_ARGUMENTS,
	// commands errors:
	ERROR_BAD_SYNTAX,
};
#endif