#include "../include/commands.h"

// still WIP
cmd_tree_node * read_commands(FILE *file,char *file_name) {
    cmd_tree_node *out_put = (cmd_tree_node*)calloc(1,sizeof(cmd_tree_node));
    if(file = fopen(file_name,"r") == NULL) {
        perror("ERROR: Opening file, reason:");
        printf("ERROR: number:%d\n",errno);
        printf("ERROR opening file:%s\n",file_name);
        return NULL;
    }
}


//done but needs testing
void commands_free_memory(cmd_tree_node*rm) {
    for(int i=0;i<rm->sizeof_commands;i++) {
        commands_free_memory(rm->sub_cmds[i]);
    }
    free(rm->sub_cmds);
    free(rm);
}