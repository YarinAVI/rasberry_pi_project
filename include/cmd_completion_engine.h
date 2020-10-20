#ifndef __COMMAND_COMPLETION_H__
#define __COMMAND_COMPLETION_H__
#include <string.h>
#include <unistd.h>


typedef unsigned char byte;

struct cmd_tree_node {
    struct cmd_tree_node **sub_cmds;
    char *cmd;
    char *description;

    size_t sizeof_commands; // amount of commands in this node.
    byte id;
};























#endif