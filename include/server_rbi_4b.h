/*
 * @Author: Yarin Avisidris 
 * @Date: 2020-10-15 01:04:56 
 * @Last Modified by: Yarin Avisidris
 * @Last Modified time: 2020-10-20 01:30:30
 */
#ifndef __SERVER_RBI_4B_H__
#define __SERVER_RBI_4B_H__
#include <sys/socket.h>  //socket()
#include <stdio.h> 		// perror 
#include <errno.h> 		// errno
#include <stdlib.h>		// malloc(), free()
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>		//write
#include <string.h>		//memset()

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

struct rb_pi_network {
	    //  buffer's sizes
		size_t read_buffer_size;
		size_t write_buffer_size;
		struct sockaddr_in server_socket,
					   	   write_socket;

		//buffers					  
		void *write_buffer;
		void *read_buffer;

        // server file discriptors for networking.
		int server_fd,
			server_data_fd;


		int	sizeof_sockaddr_in;
		

};
/*
this will set the server to SOCK_STREAM, Provides sequenced, reliable, two-way, connection-
                       		based byte streams.  An out-of-band data transmission mechanism may be supported.
@param server_ptr pointer to rb_pi_network struct.
@param clients_amount how many clients this connection can accept.
@param write_buffer_size - the size in bytes of the write buffer.
@param read_buffer_size  - the size in bytes of the read buffer.
*/
enum ErrorCode rb_pi_network_init(struct rb_pi_network *server_ptr,uint8_t clients_amount,size_t write_buffer_size,size_t read_buffer_size);
/*
*this function is blocking see accept(), it will block untill a client connects.
*@param server_ptr pointer to rb_pi_network struct.
*/
enum ErrorCode rb_pi_network_accept(struct rb_pi_network *server_ptr);
/*
*this function will call write() on server_ptr->write_buffer with server_ptr->wirte_buffer_size.
*@param server_ptr pointer to rb_pi_network struct.
*/
enum ErrorCode rb_pi_network_write(struct rb_pi_network *server_ptr);
/*
*this function will use server_ptr->read_buffer to read from socket and write into read buffer.
*@param server_ptr pointer to rb_pi_network struct.
*/
enum ErrorCode rb_pi_network_read(struct rb_pi_network *server_ptr);
/*
this function should only be called to clear rb_pi_network heap allocations.
this function will clear all dynamic memory allocated from the given rb_pi_network struct.
@param server_ptr pointer to rb_pi_network struct.
*/
void rb_pi_free_heap(struct rb_pi_network *server_ptr);


#endif