#include "../include/program_auxiliary.h"
#include <errno.h> 		// errno
void error_msg_handle(enum ErrorCode err,void *info) {
    switch(err) {	
	case ERROR_SUCCESS:
    break;
	case ERROR_NET_SOCKET_API:
    	perror("ERROR: failed to create socket, reason;");
		printf("ERROR: number:%d ",errno);
    break;
	case ERROR_NET_BIND_API:
    	perror("ERROR: binding server, reason:");
		printf("ERROR: number:%d\n",errno);
    break;
	case ERROR_NET_LISTEN_API:
    	perror("ERROR: listening, reason:");
		printf("ERROR: number:%d\n",errno);
    break;
	case ERROR_NET_WRITE_API:
    	perror("ERROR: writing to client, reason");
		printf("ERROR: number:%d\n",errno);
    break;
	case ERROR_NET_ACCEPT_API:
    	perror("ERROR: accepting connection, reason");
		printf("ERROR: number:%d\n",errno);
    break;
	case ERROR_NET_READ_API:
    	perror("ERROR: reading from client, reason");
	    printf("ERROR: number:%d\n",errno);
    break;
	case ERROR_NET_CLOSE_API:
    	perror("ERROR: failed to close file discriptors:");
		printf("ERROR: number:%d\n",errno);
    break;
	case ERROR_MEM_MALLOC_NULL:
        perror("heap allocation error malloc() returns NULL, allocation size %zu bytes\n , error reason:",*(size_t *)info);
        printf("ERROR: number:%d\n",errno);
    break;
    case ERROR_MEM_MIGHT_BE_INITIALIZED:
        printf("ERROR: failed to initialized network structure because its possibly already initialized\n");
    break;
	case ERROR_BUFFER_TOO_SMALL:
	break;
	case ERROR_NULL_ARGUMENT:
    break;
	case ERROR_BAD_ARGUMENTS:
	break;
	case ERROR_BAD_SYNTAX:
    break;
	case ERROR_OPEN_FILE:
    break;
	case ERROR_FILE_BAD_NAME:
    break;
    }
}