//
// Created by Hans on 25-5-12.
//

#include "manager.h"
void init_file_system() {
    const char *dir_name = DIR;
    DWORD dwAttrib = GetFileAttributes(dir_name);
    if (dwAttrib == INVALID_FILE_ATTRIBUTES) {
        if (_mkdir(dir_name) == -1) {
            fprintf(stderr, "创建文件夹失败！\n");
            exit(EXIT_FAILURE);
        } else if (dwAttrib & FILE_ATTRIBUTE_DIRECTORY) {
        } else {
            fprintf(stderr, "路径已存在但不是目录\n");
            exit(EXIT_FAILURE);
        }
    }
}