#include "cmd_handle.h"
#include "cmd_cp.h"
#include "cmd_ls.h"
#define DEBUG

int cmd_execute(char *cmd_str){
    if(cmd_str == NULL){
        return -1;
    }
    cmd_t command;
    cmd_command_init(&command);

    int ret = cmd_parse(cmd_str,&command);
    if(ret < 0){
        return -1;
    }
#ifdef DEBUG
    //cmd_command_print(&command);
#endif
    cmd_dispatch(&command);
    return 0;
}

void cmd_command_init(cmd_t *cmd){
    memset(cmd->cmd_name,0,SZ_NAME);
    int i;
    for(i = 0;i<SZ_COUNT;i++){
        memset(cmd->cmd_arg_list[i],0,SZ_ARG);
    }

    cmd->cmd_arg_count = 0;
}

void cmd_command_print(cmd_t *cmd){
    printf("---------------------------\n");
    printf("[DEBUG] cmd name : < %s >\n",cmd->cmd_name);
    printf("[DEBUG] cmd count : < %d >\n",cmd->cmd_arg_count); 
    printf("[DEBUG] cmd arg list :");
    for(int i = 0;i<SZ_COUNT;i++){
        printf(" %s ",cmd->cmd_arg_list[i]);
    }
    printf("\n---------------------------\n");
}

int cmd_parse(char *cmd_str,cmd_t *cmd){
    if(cmd_str == NULL || cmd == NULL){
        return -1;
    }
    int index = 0;
    char *p_cmd_name = NULL;
    char *p_cmd_arg = NULL;
    p_cmd_name = strtok(cmd_str," ");

    strcpy(cmd->cmd_name,p_cmd_name);

    for(;;){
        p_cmd_arg = strtok(NULL," ");

        if(p_cmd_arg == NULL){
            break;
        }
        strcpy(cmd->cmd_arg_list[index++],p_cmd_arg);
    }
    cmd->cmd_arg_count = index;

    return 0;
}

int cmd_dispatch(cmd_t *cmd){
    if(cmd == NULL){
        return -1;
    }

    if(strcmp(cmd->cmd_name,"ls") == 0){
        printf("ls command handle\n");
        cmd_ls_execute(cmd);
    }else if(strcmp(cmd->cmd_name,"cp") == 0){
        printf("cp command handle\n");
        cmd_cp_execute(cmd);
    }
}