/*
 * @Author: Yarin Avisidris 
 * @Date: 2020-10-24 20:39:21 
 * @Last Modified by: Yarin Avisidris
 * @Last Modified time: 2020-10-24 22:11:56
 */
#include "../include/server_rbi_4b.h"
enum ErrorCode rb_pi_server_init(struct rb_pi_network *server_ptr,uint8_t clients_amount,size_t write_buffer_size,size_t read_buffer_size,in_port_t port) {
	// get socket descriptor from os.
	server_ptr->server_fd = socket(AF_INET,SOCK_STREAM,0);
	if(server_ptr->server_fd == -1) {
		perror("ERROR: failed to create socket, reason");
		printf("ERROR: number:%d ",errno);
		return ERROR_NET_SOCKET_API;
	}
	//networking initializing:
	server_ptr->server_socket.sin_family      = AF_INET;// use IPv4.
	server_ptr->server_socket.sin_addr.s_addr = INADDR_ANY; // any IP address of this machine.
	server_ptr->server_socket.sin_port        = htons(port); // server port.
	server_ptr->sizeof_sockaddr_in            = sizeof(struct sockaddr_in);

	// bind socket to IP and port
	if(bind(server_ptr->server_fd,(struct sockaddr *)&server_ptr->server_socket,sizeof(server_ptr->server_socket)) <0) {
		perror("ERROR: binding server, reason");
		printf("ERROR: number:%d\n",errno);
		return ERROR_NET_BIND_API;
	}
	// set server to listen for connections.
	if(listen(server_ptr->server_fd,clients_amount) == -1) {
		perror("ERROR: listening, reason");
		printf("ERROR: number:%d\n",errno);
		return ERROR_NET_LISTEN_API;
	}
	
	//initialzing buffers size:
	server_ptr->read_buffer_size	= read_buffer_size;
	server_ptr->write_buffer_size	= write_buffer_size;

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
enum ErrorCode rb_pi_network_accept(struct rb_pi_network *server_ptr) {
	// receive start accepting client connection (this is blocking).
	server_ptr->server_data_fd = accept(server_ptr->server_fd,(struct sockaddr*)&server_ptr->write_socket,(socklen_t*)&server_ptr->sizeof_sockaddr_in);
	if(server_ptr->server_data_fd == -1) {
		perror("ERROR: accepting connection, reason");
		printf("ERROR: number:%d\n",errno);
		return ERROR_NET_ACCEPT_API;
	}
	return ERROR_SUCCESS;
}
enum ErrorCode rb_pi_network_write(struct rb_pi_network *server_ptr) {

	if(write(server_ptr->server_data_fd,server_ptr->write_buffer,server_ptr->write_buffer_size) == -1) {
		perror("ERROR: writing to client, reason");
		printf("ERROR: number:%d\n",errno);
		return ERROR_NET_WRITE_API;
	}
	return ERROR_SUCCESS;
}
enum ErrorCode rb_pi_network_read(struct rb_pi_network *server_ptr) {
	memset(server_ptr->read_buffer,0,server_ptr->read_buffer_size);
if(read(server_ptr->server_data_fd,server_ptr->read_buffer,server_ptr->read_buffer_size) == -1) {
	perror("ERROR: reading from client, reason");
	printf("ERROR: number:%d\n",errno);
	return ERROR_NET_READ_API;
}
return ERROR_SUCCESS;
}
void rb_pi_free_heap(struct rb_pi_network *server_ptr) {
	free(server_ptr->write_buffer);
	free(server_ptr->read_buffer);
	server_ptr->write_buffer	= NULL;
	server_ptr->read_buffer		= NULL;
}