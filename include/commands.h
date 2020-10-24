#ifndef __COMMAND_COMPLETION_H__
#define __COMMAND_COMPLETION_H__
#include <string.h>
#include <stdio.h>
#include <stdlib.h> // calloc,malloc
#include <errno.h>


typedef unsigned char byte;
struct cmd {
    char *cmd;
    char *description;
    byte cmd_length;
    byte description_length;
};
struct cmd_tree_node {
    struct cmd_tree_node **sub_cmds;
    struct cmd;
    byte sizeof_commands; // amount of commands in this node.
    byte id;
}typedef cmd_tree_node;

/*
recursivly reads commands from commands file and builds a command tree.
the commands are stored in memory in tree like structure.
returns a poitner to a new cmd_tree_node structure.
@param file file pointer.
@param file_name name of the file to read, it will look for the file under rb_env folder.
*/
cmd_tree_node * read_commands(FILE *file,char *file_name);
/*
recursivly frees the memory pointed by *rm.
@param rm pointer to cmd_tree_node structure.
*/
void commands_free_memory(cmd_tree_node*rm);
















#endif