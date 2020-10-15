/*
 * @Author: Yarin Avisidris 
 * @Date: 2020-10-15 01:04:56 
 * @Last Modified by: Yarin Avisidris
 * @Last Modified time: 2020-10-15 15:16:56
 */
#ifndef __SERVER_RBI_4B_H__
#define __SERVER_RBI_4B_H__
#include<sys/socket.h>
#include <stdio.h> // perror errno
#include <errno.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write
#include<string.h>



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
	// arguments error
	ERROR_NULL_ARGUMENT,
	ERROR_BAD_ARGUMENTS,
};

struct rb_pi_network {
		struct sockaddr_in server_socket,
					   	   write_socket;
		int server_fd,
			server_write_fd,
			sizeof_sockaddr_in;
};
/*
@param server_ptr pointer to rb_pi_network struct.
@param clients_amount how many clients this connection can accept.
*/
enum ErrorCode rb_pi_network_init(struct rb_pi_network *server_ptr,u_int8_t clients_amount) {
	// get socket descriptor from os.
	server_ptr->server_fd = socket(AF_INET,SOCK_STREAM,0);
	if(server_ptr->server_fd == -1) {
		perror("Error failed to create socket");
		return ERROR_NET_SOCKET_API;
	}
	server_ptr->server_socket.sin_family = AF_INET;// use IPv4
	server_ptr->server_socket.sin_addr.s_addr = INADDR_ANY; // any IP address of this machine
	server_ptr->server_socket.sin_port = htons(3333); // server port
	server_ptr->sizeof_sockaddr_in = sizeof(struct sockaddr_in);
	// bind socket to IP and port
	if(bind(server_ptr->server_fd,(struct sockaddr *)&server_ptr->server_socket,sizeof(server_ptr->server_socket)) <0) {
		perror("Error binding server");
		return ERROR_NET_BIND_API;
	}
	if(listen(server_ptr->server_fd,clients_amount) == -1) {
		perror("Error listening");
		return ERROR_NET_LISTEN_API;
	}

	return ERROR_SUCCESS;
}
/*
*@param server_ptr pointer to rb_pi_network struct.
*/
enum ErrorCode rb_pi_network_accept(struct rb_pi_network *server_ptr) {
	server_ptr->server_write_fd = accept(server_ptr->server_fd,(struct sockaddr*)&server_ptr->write_socket,(socklen_t*)&server_ptr->sizeof_sockaddr_in);
	if(server_ptr->server_write_fd == -1) {
		perror("Error accepting connection:");
		return ERROR_NET_ACCEPT_API;
	}
	return ERROR_SUCCESS;
}
/*
*@param server_ptr pointer to rb_pi_network struct.
*@param buffer pointer to buffer.
*@param size_in_bytes the size in bytes to send.
*/
enum ErrorCode rb_pi_network_write(struct rb_pi_network *server_ptr,const void *buffer,size_t size_in_bytes) {
	if(write(server_ptr->server_write_fd,buffer,size_in_bytes) == -1 ) {
		perror("Error writing to client:");
		return ERROR_NET_WRITE_API;
	}
	return ERROR_SUCCESS;
}
/*
*@param server_ptr pointer to rb_pi_network struct.
*@param buffer pointer to buffer.
*@param size_in_bytes the size in bytes to read.
*/
enum ErrorCode rb_pi_network_read(struct rb_pi_network *server_ptr,void *buffer,size_t size_in_bytes) {

if(read(server_ptr->server_write_fd,buffer,size_in_bytes) == -1) {
	perror("Error reading from client");
	return ERROR_NET_READ_API;
}


return ERROR_SUCCESS;
}


#endif