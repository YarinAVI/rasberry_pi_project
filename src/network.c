/*
 * @Author: Yarin Avisidris 
 * @Date: 2020-10-24 20:39:21 
 * @Last Modified by: Yarin Avisidris
 * @Last Modified time: 2020-11-07 18:13:52
 */
#include "../include/network.h"
enum ErrorCode network_init(network *net,uint8_t clients_amount,size_t write_buffer_size,size_t read_buffer_size,in_port_t port) {
	//check if this structure's buffers are not NULL, if so then this structure could be already initialized
	// to overcome possible error we will return ERROR_MEM_MIGHT_BE_INITIALIZED in this case.
	if(net->read_buffer || net->read_buffer) {
		printf("ERROR: failed to initialized network structure because its possibly already initialized\n");
		return ERROR_MEM_MIGHT_BE_INITIALIZED;
	}
	// get socket descriptor from os.
	net->server_fd = socket(AF_INET,SOCK_STREAM,0);
	if(net->server_fd == -1) {
		perror("ERROR: failed to create socket, reason");
		printf("ERROR: number:%d ",errno);
		return ERROR_NET_SOCKET_API;
	}
	//networking initializing:
	net->server_socket.sin_family      = AF_INET;	 // use IPv4.
	net->server_socket.sin_addr.s_addr = INADDR_ANY;  // any IP address of this machine.
	net->server_socket.sin_port        = htons(port); // server port.
	net->sizeof_sockaddr_in            = sizeof(struct sockaddr_in);

	// bind socket to IP and port
	if(bind(net->server_fd,(struct sockaddr *)&net->server_socket,sizeof(net->server_socket)) <0) {
		perror("ERROR: binding server, reason");
		printf("ERROR: number:%d\n",errno);
		return ERROR_NET_BIND_API;
	}
	// set server to listen for connections.
	if(listen(net->server_fd,clients_amount) == -1) {
		perror("ERROR: listening, reason");
		printf("ERROR: number:%d\n",errno);
		return ERROR_NET_LISTEN_API;
	}
	
	//initialzing buffers size:
	net->read_buffer_size	= read_buffer_size;
	net->write_buffer_size	= write_buffer_size;

	// allocate memory for read buffer.
	net->read_buffer  = (void*)malloc(net->read_buffer_size);
	if(!net->read_buffer) {
		printf("heap allocation error malloc() returns NULL, allocation size %zu bytes\n",net->read_buffer_size);
		return ERROR_MEM_MALLOC_NULL;
	}
	// allocate memory for write buffer.
	net->write_buffer = (void*)malloc(net->write_buffer_size);
	if(!net->write_buffer) {
		printf("heap allocation error malloc() returns NULL, allocation size %zu bytes\n",net->write_buffer_size);
		return ERROR_MEM_MALLOC_NULL;
	}

	return ERROR_SUCCESS;
}
enum ErrorCode network_accept(network *net) {
	// receive start accepting client connection (this is blocking).
	net->server_data_fd = accept(net->server_fd,(struct sockaddr*)&net->write_socket,(socklen_t*)&net->sizeof_sockaddr_in);
	if(net->server_data_fd == -1) {
		perror("ERROR: accepting connection, reason");
		printf("ERROR: number:%d\n",errno);
		return ERROR_NET_ACCEPT_API;
	}
	return ERROR_SUCCESS;
}
enum ErrorCode network_write(network *net) {

	if(write(net->server_data_fd,net->write_buffer,net->write_buffer_size) == -1) {
		perror("ERROR: writing to client, reason");
		printf("ERROR: number:%d\n",errno);
		return ERROR_NET_WRITE_API;
	}
	return ERROR_SUCCESS;
}
enum ErrorCode network_write_msg(network *net,char *msg,size_t msg_size) {
	if(net->write_buffer_size < msg_size) return ERROR_BUFFER_TOO_SMALL;
	memcpy(net->write_buffer,msg,msg_size);
	memset(net->write_buffer+msg_size,0,net->write_buffer_size-msg_size);
	if(write(net->server_data_fd,net->write_buffer,net->write_buffer_size) == -1) {
		perror("ERROR: writing to client, reason");
		printf("ERROR: number:%d\n",errno);
		return ERROR_NET_WRITE_API;
	}
	return ERROR_SUCCESS;
}
enum ErrorCode network_read(network *net) {
	memset(net->read_buffer,0,net->read_buffer_size);
	if(read(net->server_data_fd,net->read_buffer,net->read_buffer_size) == -1) {
	perror("ERROR: reading from client, reason");
	printf("ERROR: number:%d\n",errno);
	return ERROR_NET_READ_API;
}
return ERROR_SUCCESS;
}
void network_free_heap(network *net) {
	free_and_null(net->read_buffer);
	free_and_null(net->read_buffer);
}
enum ErrorCode network_cleanup(network * net) {	
	if(close(net->server_fd) == -1 || close(net->server_data_fd) ==-1) {
		perror("ERROR: failed to close file discriptors:");
		printf("ERROR: number:%d\n",errno);
		return ERROR_NET_CLOSE_API;
	}
	network_free_heap(net);
	free(net);
}