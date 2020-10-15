/*
 * @Author: Yarin Avisidris 
 * @Date: 2020-10-15 01:05:03 
 * @Last Modified by: Yarin Avisidris
 * @Last Modified time: 2020-10-15 17:15:37
 */

#include "server_rbi_4b.h"
#include <stdio.h>



int main(int argc, char **argv) {

struct rb_pi_network rb_net;


enum ErrorCode program_error;

program_error = rb_pi_network_init(&rb_net,3);


if(program_error != ERROR_SUCCESS)  goto SERVER_END;

char write_buff[1024] = {0};
char read_buff[1024] = {0};

printf("Waiting for connections..\n");
rb_pi_network_accept(&rb_net);
printf("Client connected successfully.\n");
while(1) {
    //fgets(write_buff,1024,stdin);
//if(rb_pi_network_write(&rb_net,(const void *)write_buff,strlen(write_buff)) !=ERROR_SUCCESS) goto SERVER_END;
if(rb_pi_network_read(&rb_net,(void*)read_buff,1024) != ERROR_SUCCESS) goto SERVER_END;
printf("server is reading :%s",&read_buff[0]);
}


SERVER_END:
    return program_error;
}