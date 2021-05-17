#ifndef __SERVER_H__
#define __SERVER_H__
#include "../include/program_auxiliary.h"
#include "../include/network.h"
#include "../include/commands.h"


struct server {
    network net;
    struct cmd_tree_node root_commands;
};
/*
*this will set the server network to SOCK_STREAM, Provides sequenced, reliable, two-way, connection-
                       		based byte streams.  An out-of-band data transmission mechanism may be supported.
*this function should ONLY be called on uninitialized server structure.
@param server_ptr pointer to network struct.
@param clients_amount how many clients this server's connection can accept.
@param write_buffer_size - the size in bytes of the write buffer.
@param read_buffer_size  - the size in bytes of the read buffer.
@param port - the port number for the server,0-2^16, uint16_t.
@return enum ErrorCode, returns ERROR_SUCCESS if successfully initialized.
*/
enum ErrorCode server_init(struct server *server_ptr,uint8_t clients_amount,size_t write_buffer_size,size_t read_buffer_size,in_port_t port);
/*
*this function should only be called to clear the server heap allocations, 
*this function will clear all dynamic memory allocated from the given server struct.
@param server_ptr pointer to server struct.
*/
void server_free_heap(struct server *server_ptr);
/*
*this function should only be called to clear the entire server struct, 
*this will close all its file descriptors and clear alll the heap allocations aswell.
@param server_ptr pointer to server struct.
@return enum ErrorCode, returns ERROR_SUCCESS if cleanup succeeded.
*/
enum ErrorCode server_cleanup(struct server *server_ptr);














#endif