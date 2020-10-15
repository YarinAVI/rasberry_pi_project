#ifndef __COMMAND_COMPLETION_H__
#define __COMMAND_COMPLETION_H__
#include <string.h>



struct cmd_tree_node {
    char *cmd;
    size_t cmd_size;
    struct cmd_tree_node **sub_cmds;
};























#endif