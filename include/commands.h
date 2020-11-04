/*
 * @Author: Yarin Avisidris 
 * @Date: 2020-10-24 20:39:42 
 * @Last Modified by: Yarin Avisidris
 * @Last Modified time: 2020-10-29 01:53:30
 */
#ifndef __COMMAND_COMPLETION_H__
#define __COMMAND_COMPLETION_H__
#include "program_auxiliary.h"
#include <string.h>
#include <stdio.h>
#include <errno.h>

struct cmd {
    char *cmd;
    char *description;
    byte cmd_length;
    byte description_length;
};
/*
*the first node is the root node, the root node will include all the program sub commands under
*cmd_tree_node ** sub_nodes structure pointer list,the root node dosn't have any commands and its pointer
* **commands should point to NULL, and commands_size set to 0,
*/
struct cmd_tree_node {
    struct cmd **commands;            // list of commands.
    struct cmd_tree_node **sub_nodes; // list of sub_nodes.
    byte commands_size; // amount of commands in this node.
    byte sub_nodes_size;// amount of sub nodes in this node.
    byte id;
};
/*
reads commands from commands file and builds a command tree.
the commands are stored in memory in tree like structure.
@param file file pointer.
@param file_name name of the file to read, it will look for the file under rb_env folder.
@return poitner to a new cmd_tree_node structure, returns NULL if it fails.
*/
struct cmd_tree_node * read_commands(FILE *file,char *file_name);
/*
recursivly frees the memory pointed by *rm.
@param rm pointer to cmd_tree_node structure.
*/
void commands_free_memory(struct cmd_tree_node*rm);
















#endif