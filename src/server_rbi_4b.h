/*
 * @Author: Yarin Avisidris 
 * @Date: 2020-10-15 01:04:56 
 * @Last Modified by: Yarin Avisidris
 * @Last Modified time: 2020-10-17 20:48:44
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
enum ErrorCode rb_pi_network_init(struct rb_pi_network *server_ptr,uint8_t clients_amount,size_t write_buffer_size,size_t read_buffer_size) {
	// get socket descriptor from os.
	server_ptr->server_fd = socket(AF_INET,SOCK_STREAM,0);

	if(server_ptr->server_fd == -1) {
		printf("Error number:%d ",errno);
		perror("Error : failed to create socket, reason");
		return ERROR_NET_SOCKET_API;
	}
	//networking initializing:
	server_ptr->server_socket.sin_family      = AF_INET;// use IPv4.
	server_ptr->server_socket.sin_addr.s_addr = INADDR_ANY; // any IP address of this machine.
	server_ptr->server_socket.sin_port        = htons(3333); // server port.
	server_ptr->sizeof_sockaddr_in            = sizeof(struct sockaddr_in);

	// bind socket to IP and port
	if(bind(server_ptr->server_fd,(struct sockaddr *)&server_ptr->server_socket,sizeof(server_ptr->server_socket)) <0) {
		
		perror("Error : binding server, reason");
		printf("Error number:%d\n",errno);
		return ERROR_NET_BIND_API;
	}
	// set server to listen for connections.
	if(listen(server_ptr->server_fd,clients_amount) == -1) {
		perror("Error : listening, reason");
		printf("Error number:%d\n",errno);
		return ERROR_NET_LISTEN_API;
	}

	//initialzing buffers size:
	server_ptr->read_buffer_size			= read_buffer_size;
	server_ptr->write_buffer_size			= write_buffer_size;

	// allocate memory for read buffer.
	server_ptr->read_buffer  = (void*)malloc(server_ptr->read_buffer_size);
	if(!server_ptr->read_buffer) {
		printf("heap allocation error malloc() returns NULL, allocation size %zu bytes\n",server_ptr->read_buffer_size);
		return ERROR_MEM_MALLOC_NULL;
	}
	// allocate memory for write buffer.
	server_ptr->write_buffer = (void*)malloc(server_ptr->write_buffer_size);
	if(!server_ptr->write_buffer) {
		printf("heap allocation error malloc() returns NULL, allocation size %zu bytes\n",server_ptr->write_buffer_size);
		return ERROR_MEM_MALLOC_NULL;
	}

	return ERROR_SUCCESS;
}
/*
*this function is blocking see accept(), it will block untill a client connects.
*@param server_ptr pointer to rb_pi_network struct.
*/
enum ErrorCode rb_pi_network_accept(struct rb_pi_network *server_ptr) {
	// receive start accepting client connection (this is blocking).
	server_ptr->server_data_fd = accept(server_ptr->server_fd,(struct sockaddr*)&server_ptr->write_socket,(socklen_t*)&server_ptr->sizeof_sockaddr_in);
	if(server_ptr->server_data_fd == -1) {
		perror("Error : accepting connection, reason");
		printf("Error number:%d\n",errno);
		return ERROR_NET_ACCEPT_API;
	}
	return ERROR_SUCCESS;
}
/*
*this function will call write() on server_ptr->write_buffer with server_ptr->wirte_buffer_size.
*@param server_ptr pointer to rb_pi_network struct.
*/
enum ErrorCode rb_pi_network_write(struct rb_pi_network *server_ptr) {

	if(write(server_ptr->server_data_fd,server_ptr->write_buffer,server_ptr->write_buffer_size) == -1) {
		perror("Error writing to client, reason");
		printf("Error number:%d\n",errno);
		return ERROR_NET_WRITE_API;
	}
	return ERROR_SUCCESS;
}
/*
*this function will use server_ptr->read_buffer to read from socket and write into read buffer.
*@param server_ptr pointer to rb_pi_network struct.
*/
enum ErrorCode rb_pi_network_read(struct rb_pi_network *server_ptr) {
if(read(server_ptr->server_data_fd,server_ptr->read_buffer,server_ptr->read_buffer_size) == -1) {
	perror("Error reading from client, reason");
	printf("Error number:%d\n",errno);
	return ERROR_NET_READ_API;
}
return ERROR_SUCCESS;
}
/*
this function should only be called to clear rb_pi_network heap allocations.
this function will clear all dynamic memory allocated from the given rb_pi_network struct.
@param server_ptr pointer to rb_pi_network struct.
*/
void rb_pi_free_heap(struct rb_pi_network *server_ptr) {
	free(server_ptr->write_buffer);
	free(server_ptr->read_buffer);
}


#endif