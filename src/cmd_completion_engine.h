#ifndef __COMMAND_COMPLETION_H__
#define __COMMAND_COMPLETION_H__
#include <string.h>
#include <unistd.h>


struct cmd_tree_node {
    struct cmd_tree_node **sub_cmds;
    char *cmd;
    size_t cmd_size;
    
};























#endif