#ifndef __CMD_CP_H__
#define __CMD_CP_H__

#include "cmd_handle.h"
#define SZ_PATH 64
enum file_type{
    FT_DIR = 0,
    FT_FILE = 1,
    FT_ERROR = 2,
    FT_UNKNOWN = 3,
};

typedef struct cp_file_info{
    enum file_type src_type;
    char src_path[SZ_PATH];
    char dest_path[SZ_PATH];
}cp_file_info_t;


int cmd_cp_execute(cmd_t *cmd);
int cmd_cp_parse_path(cp_file_info_t *pfileinfo,cmd_t *cmd);
enum file_type get_file_type(const char *path);
int cmd_cp_parse_type(cp_file_info_t *pfileinfo);

int cmd_cp_dispatch(cp_file_info_t *pfileinfo);
int cmd_cp_file(const char *src,const char *dest);
int cmd_cp_dirtory(const char *src,const char *dest);
int make_path(cp_file_info_t *pfileinfo,const char *spath,const char *dpath,const char *filename);


#endif