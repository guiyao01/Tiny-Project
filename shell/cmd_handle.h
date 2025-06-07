#ifndef __CMD_HANDLE_H__
#define __CMD_HANDLE_H__

#include <stdio.h>
#include <string.h>
#define SZ_NAME 8
#define SZ_ARG 32
#define SZ_COUNT 2

typedef struct command{
    char cmd_name[SZ_NAME];
    char cmd_arg_list[SZ_COUNT][SZ_ARG];
    int cmd_arg_count;
}cmd_t;

extern int cmd_execute(char *cmd);
void cmd_command_init(cmd_t *cmd);
void cmd_command_print(cmd_t *cmd);
int cmd_parse(char *cmd_str,cmd_t *cmd);
int cmd_dispatch(cmd_t *cmd);
#endif