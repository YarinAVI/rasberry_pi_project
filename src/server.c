#include "../include/server.h"





enum ErrorCode server_init(struct server *server_ptr,uint8_t clients_amount,size_t write_buffer_size,size_t read_buffer_size,in_port_t port) {
    enum ErrorCode error;
    // initialize networking for the server structure.
    if(error = network_init(&server_ptr->net,clients_amount,write_buffer_size,read_buffer_size,port)!=ERROR_SUCCESS) {
        return error;
    }
}