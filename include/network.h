/*
 * @Author: Yarin Avisidris 
 * @Date: 2020-10-15 01:04:56 
 * @Last Modified by: Yarin Avisidris
 * @Last Modified time: 2020-10-29 00:51:20
 */
#ifndef __NETWORK_H__
#define __NETWORK_H__
#include <sys/socket.h>  //socket()
#include <stdio.h> 		// perror 
#include <errno.h> 		// errno
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>		//write
#include <string.h>		//memset()
#include "../include/program_auxiliary.h"
typedef struct network {
	    //  buffer's sizes
		size_t read_buffer_size;
		size_t write_buffer_size;
		//buffers					  
		void *write_buffer;
		void *read_buffer;
		struct sockaddr_in server_socket,
					   	   write_socket;
        // server file discriptors for networking.
		int server_fd,
			server_data_fd;
		int	sizeof_sockaddr_in;
}network;
/*
*this will set the server to SOCK_STREAM, Provides sequenced, reliable, two-way, connection-
                       		based byte streams.  An out-of-band data transmission mechanism may be supported,
*this function should ONLY be called on uninitialized network structure.
@param net pointer to network struct.
@param clients_amount how many clients this connection can accept.
@param write_buffer_size - the size in bytes of the write buffer.
@param read_buffer_size  - the size in bytes of the read buffer.
@param port - the port number for the connection,0-2^16, uint16_t.
@return enum ErrorCode, returns ERROR_SUCCESS if successfully initialized.
*/
enum ErrorCode network_init(network *net,uint8_t clients_amount,size_t write_buffer_size,size_t read_buffer_size,in_port_t port);
/*
*this function is blocking see accept(), it will block untill a client connects.
*@param net pointer to network struct.
@return enum ErrorCode, returns ERROR_SUCCESS if accept() succeeded.
*/
enum ErrorCode network_accept(network *net);
/*
*this function will call write() on server->write_buffer with server->wirte_buffer_size.
*this function will write whats ever inside the server->write_buffer into the socket.
*@param net pointer to network struct.
*@return enum ErrorCode, returns ERROR_SUCCESS if write() succeeded.
*/
enum ErrorCode network_write(network *net);
/*
*this function will call write() on server->write_buffer with server->wirte_buffer_size.
*this function will copy the msg into net->write_buffer if the msg fits the size of the buffer.
*and then will write this into the socket.
*@param net pointer to network structure.
*@param msg pointer to message string.
*@param msg_size the size of the message string in bytes.
*@return returns ERROR_SUCCESS if no error, otherwise returns the appropiate error.
*/
enum ErrorCode network_write_msg(network *net,char *msg,size_t msg_size)
/*
*this function will use server->read_buffer to read from socket and write into read buffer.
*@param net pointer to network struct.
*@return enum ErrorCode, returns ERROR_SUCCESS if read() succeeded.
*/
enum ErrorCode network_read(network *net);
/*
*this function should only be called to clear network heap allocations, 
*this function will clear all dynamic memory allocated from the given network struct.
@param net pointer to network struct.
*/
void network_free_heap(network *net);
/*
*this function should only be called to clear the entire network struct, 
*this will close all its file descriptors and clear alll the heap allocations aswell.
@param net pointer to network struct.
@return enum ErrorCode, returns ERROR_SUCCESS if cleanup succeeded, returns ERROR_NET_CLOSE_API if closing
the file descriptors wasn't successful, if it didn't succeed then it won't free heap allocations aswell.
*/
enum ErrorCode network_cleanup(network * net);

#endif