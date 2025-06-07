#include "cmd_cp.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#define SZ_BUFFER 1024
int cmd_cp_execute(cmd_t *cmd){
    if(cmd == NULL){
        return -1;
    }

    cmd_command_print(cmd);

    cp_file_info_t fileinfo;
    int ret = cmd_cp_parse_path(&fileinfo,cmd);
    if(ret < 0){
        return -1;
    }

    ret = cmd_cp_parse_type(&fileinfo);
    if(ret < 0){
        return -1;
    }

    ret = cmd_cp_dispatch(&fileinfo);
    if(ret < 0){
        return -1;
    }

    return 0;
}

int cmd_cp_parse_path(cp_file_info_t *pfileinfo,cmd_t *cmd){
    if(pfileinfo == NULL || cmd == NULL){
        return -1;
    }

    strcpy(pfileinfo->dest_path,cmd->cmd_arg_list[0]);
    strcpy(pfileinfo->src_path,cmd->cmd_arg_list[1]);

    printf("[DEBUG] pfileinfo dest_path < %s >\n",pfileinfo->dest_path);
    printf("[DEBUG] pfileinfo src_path < %s >\n",pfileinfo->src_path);
    
    return 0;
}
enum file_type get_file_type(const char *path){
    struct stat statbuf;

    int ret = stat(path,&statbuf);
    if(ret == -1){
        perror("stat():");
        return FT_ERROR;
    }

    if(S_ISDIR(statbuf.st_mode)){
        return FT_DIR;
    }else if(S_ISREG(statbuf.st_mode)){
        return FT_FILE;
    }

    return FT_UNKNOWN;
}

int cmd_cp_parse_type(cp_file_info_t *pfileinfo){
    enum file_type ftype;
    ftype = get_file_type(pfileinfo->src_path);

    if(ftype == FT_ERROR || ftype == FT_UNKNOWN){
        return -1;
    }else{
        pfileinfo->src_type = ftype;
    }
    
    if(pfileinfo->src_type == FT_FILE){
        printf("File.\n");
    }else if(pfileinfo->src_type == FT_DIR){
        printf("Dir.\n");
    }
    return 0;
}
int cmd_cp_dispatch(cp_file_info_t *pfileinfo){
    if(pfileinfo->src_type == FT_FILE){
        //printf("cp file\n");
        return cmd_cp_file(pfileinfo->src_path,pfileinfo->dest_path);
    }else if(pfileinfo->src_type == FT_DIR){
        return cmd_cp_dirtory(pfileinfo->src_path,pfileinfo->dest_path);
    }
}
int cmd_cp_file(const char *src,const char *dest){
    if(src == NULL || dest == NULL){
        return -1;
    }
    
    FILE *fp_src = NULL,*fp_dest = NULL;
    size_t rbytes = 0,wbytes = 0;
    char buffer[SZ_BUFFER] = {0};

    fp_src = fopen(src,"r");
    if(fp_src == NULL){
        perror("fopen");
        return -1;
    }

    fp_dest = fopen(dest,"w+");
    if(fp_dest == NULL){
        perror("fopen");
        return -1;
    }

    for(;;){
        rbytes = fread(buffer,sizeof(char),SZ_BUFFER,fp_src);
        if(rbytes > 0){
            wbytes = fwrite(buffer,sizeof(char),rbytes,fp_dest);
            if(rbytes != wbytes){
                perror("[ERROR] fwrite()");
                return -1;
            }
        }else{
            break;
        }
    }
    
    fclose(fp_src);
    fclose(fp_dest);
    return 0;
}
int cmd_cp_dirtory(const char *src,const char *dest){
    DIR *pdir = NULL;
    struct dirent *pdirent = NULL;
    cp_file_info_t pfile;

    int ret = mkdir(dest,0777);
    if(ret == -1){
        perror("[ERROR] mkdir()");
        return -1;
    }

    pdir = opendir(src);
    if(pdir == NULL){
        perror("[ERROR] opendir()");
        return -1;
    }

    for(;;){
        pdirent = readdir(pdir);

        if(pdirent == NULL){
            break;
        }

        if(strcmp(pdirent->d_name,".") == 0 || strcmp(pdirent->d_name,"..") == 0){
            continue;
        }

        printf("[DEBUG] filename : < %s >\n",pdirent->d_name);

        make_path(&pfile,src,dest,pdirent->d_name);
        printf("[DEBUG] src : < %s >\n",pfile.src_path);
        printf("[DEBUG] dest : < %s >\n",pfile.dest_path);

        pfile.src_type = get_file_type(pfile.src_path);
        if(pfile.src_type == FT_DIR){
            cmd_cp_dirtory(pfile.src_path,pfile.dest_path);
        }else if(pfile.src_type == FT_FILE){
            cmd_cp_file(pfile.src_path,pfile.dest_path);
        }
    }

    closedir(pdir);

    return 0;
}

int make_path(cp_file_info_t *pfileinfo, const char *spath, const char *dpath, const char *filename)
{
    memset(pfileinfo->dest_path,0,sizeof(pfileinfo->dest_path));
    memset(pfileinfo->src_path,0,sizeof(pfileinfo->src_path));

    strcpy(pfileinfo->dest_path,dpath);
    strcat(pfileinfo->dest_path,"/");
    strcat(pfileinfo->dest_path,filename);

    strcpy(pfileinfo->src_path,spath);
    strcat(pfileinfo->src_path,"/");
    strcat(pfileinfo->src_path,filename);
    return 0;
}
