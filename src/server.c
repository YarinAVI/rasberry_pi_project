#include "../include/server.h"
enum ErrorCode server_init(server *server_ptr,uint8_t clients_amount,size_t write_buffer_size,size_t read_buffer_size,in_port_t port) {
    enum ErrorCode error;
    // initialize networking for the server structure.
    if(error = network_init(&server_ptr->net,clients_amount,write_buffer_size,read_buffer_size,port)!=ERROR_SUCCESS) {
        return error;
    }
}
void server_free_heap(server *server_ptr) {
    network_free_heap(&server_ptr->net);
    commands_cleanup(&server_ptr->root_commands);
}
enum ErrorCode server_cleaup(server *server_ptr) {
    network_cleanup(&server_ptr->net);
    commands_cleanup(&server_ptr->root_commands);
}