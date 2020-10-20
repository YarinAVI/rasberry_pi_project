/*
 * @Author: Yarin Avisidris 
 * @Date: 2020-10-17 20:43:01 
 * @Last Modified by: Yarin Avisidris
 * @Last Modified time: 2020-10-20 02:06:33
 */
/*
 * @TO DO:
 * @need to fix writing and reading all kind of bugs and stuff
 * @need to start working on cmd_completion_engine
 * @
 */
#include "server_rbi_4b.h"
#include <stdio.h>


int main(int argc, char **argv) {

struct rb_pi_network rb_net;


enum ErrorCode program_error;

program_error = rb_pi_network_init(&rb_net,3,10,10);


if(program_error != ERROR_SUCCESS)  goto SERVER_END;


printf("Waiting for connections..\n");
rb_pi_network_accept(&rb_net);
printf("Client connected successfully.\n");
while(1) {
    //fgets(rb_net.write_buffer,rb_net.write_buffer_size,stdin);
    //fgets(write_buff,1024,stdin);
//if(rb_pi_network_write(&rb_net,(const void *)write_buff,strlen(write_buff)) !=ERROR_SUCCESS) goto SERVER_END;
     //if(rb_pi_network_write(&rb_net) != ERROR_SUCCESS) goto SERVER_END;
if( rb_pi_network_read(&rb_net) != ERROR_SUCCESS) goto SERVER_END;
printf("server is reading :%s",rb_net.read_buffer);
//memset(&read_buff[0],0,24);
}

SERVER_END:
    return program_error;


}