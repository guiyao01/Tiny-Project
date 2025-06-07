#ifndef __CMD_LS_H__
#define __CMD_LS_H__

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "cmd_handle.h"


#define SZ_LS_NAME 64
#define SZ_LS_PERMISSION 10
#define SZ_LS_TIME 32
#define SZ_LS_LINK_CONTENT 64

typedef struct file_attribute{
    struct stat f_attr_stat_info;

    char f_attr_type;              // file type
    char f_attr_uname[SZ_LS_NAME]; // user name
    char f_attr_gname[SZ_LS_NAME]; // group name
    char f_attr_mtime[SZ_LS_TIME]; // last mod time
    char f_attr_permission[SZ_LS_PERMISSION]; // permissioon
    char f_attr_name[SZ_LS_NAME];
    char f_attr_link_content[SZ_LS_LINK_CONTENT];
}file_attr_t;

extern int cmd_ls_execute(cmd_t *pcmd);
int cmd_list_dirtory(const char *dirpath);
int get_file_attr(struct file_attribute *pattr,const char *path,const char *filename,bool islink);
void show_file_attributes(struct file_attribute *pattr);
void make_path_ls(char *path,const char *dirpath,const char *filename);
int get_file_type_ls(struct file_attribute *pattr);
int get_file_permission(struct file_attribute *pattr);
void get_file_uname(struct file_attribute *pattr);
void get_file_gname(struct file_attribute *pattr);
void get_file_last_modify_time(struct file_attribute *pattr);
#endif
