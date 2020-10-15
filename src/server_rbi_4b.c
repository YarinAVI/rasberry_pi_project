/*
 * @Author: Yarin Avisidris 
 * @Date: 2020-10-15 01:05:03 
 * @Last Modified by: Yarin Avisidris
 * @Last Modified time: 2020-10-15 14:23:37
 */

#include "server_rbi_4b.h"
#include <stdio.h>


int main(int argc, char **argv) {

struct rb_pi_network rb_net;


enum ErrorCode init_error;

init_error = rb_pi_network_init(&rb_net,3);



if(init_error != ERROR_SUCCESS)  goto SERVER_END;
	


printf("Waiting for connections..\n");
rb_pi_network_accept(&rb_net);
char *msg = "this is a test\n";
rb_pi_network_write(&rb_net,msg,strlen(msg));






SERVER_END:
    return init_error;
}