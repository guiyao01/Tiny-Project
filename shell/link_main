#include <stdio.h>
#include <string.h>
#include "cmd_handle.h"

#define SZ_CMD 50
int main(int argc, char const *argv[])
{
    char command[SZ_CMD] = {0};
    
    for(;;){
        printf("tinyshell >");
        fgets(command,SZ_CMD,stdin);

        command[strlen(command) - 1] = '\0';

        if(strncmp(command,"quit",4) == 0){
            printf("bye.\n");
            break;
        }
        cmd_execute(command);
    }
    return 0;
}
