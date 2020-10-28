/*
 * @Author: Yarin Avisidris 
 * @Date: 2020-10-15 01:04:56 
 * @Last Modified by: Yarin Avisidris
 * @Last Modified time: 2020-10-29 00:51:20
 */
#ifndef __SERVER_RBI_4B_H__
#define __SERVER_RBI_4B_H__
#include <sys/socket.h>  //socket()
#include <stdio.h> 		// perror 
#include <errno.h> 		// errno
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>		//write
#include <string.h>		//memset()
#include <program_auxiliary.h>

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
this function should ONLY be called on uninitialized rb_pi_network structure.
@param server_ptr pointer to rb_pi_network struct.
@param clients_amount how many clients this connection can accept.
@param write_buffer_size - the size in bytes of the write buffer.
@param read_buffer_size  - the size in bytes of the read buffer.
@param port - the port number for the connection,0-2^16, uint16_t.
@return enum ErrorCode, returns ERROR_SUCCESS if successfully initialized.
*/
enum ErrorCode rb_pi_server_init(struct rb_pi_network *server_ptr,uint8_t clients_amount,size_t write_buffer_size,size_t read_buffer_size,in_port_t port);
/*
*this function is blocking see accept(), it will block untill a client connects.
*@param server_ptr pointer to rb_pi_network struct.
@return enum ErrorCode, returns ERROR_SUCCESS if accept() succeeded.
*/
enum ErrorCode rb_pi_network_accept(struct rb_pi_network *server_ptr);
/*
*this function will call write() on server_ptr->write_buffer with server_ptr->wirte_buffer_size.
*@param server_ptr pointer to rb_pi_network struct.
*@return enum ErrorCode, returns ERROR_SUCCESS if write() succeeded.
*/
enum ErrorCode rb_pi_network_write(struct rb_pi_network *server_ptr);
/*
*this function will use server_ptr->read_buffer to read from socket and write into read buffer.
*@param server_ptr pointer to rb_pi_network struct.
*@return enum ErrorCode, returns ERROR_SUCCESS if read() succeeded.
*/
enum ErrorCode rb_pi_network_read(struct rb_pi_network *server_ptr);
/*
this function should only be called to clear rb_pi_network heap allocations.
this function will clear all dynamic memory allocated from the given rb_pi_network struct.
@param server_ptr pointer to rb_pi_network struct.
*/
void rb_pi_free_heap(struct rb_pi_network *server_ptr);
#endif