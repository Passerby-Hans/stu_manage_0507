//
// Created by Hans on 25-5-12.
//

#include "class.h"

CSV_File *open_class(char* file_name) {
    CSV_File *class_file = calloc(1, sizeof(CSV_File));
    if (class_file == NULL) {
        fprintf(stderr, "init_file() 错误：%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    char* file_path_buffer = calloc(MAX_FILE_STR_LEN, sizeof(char));
    snprintf(file_path_buffer, MAX_FILE_STR_LEN, "%s/%s", DIR, file_name);
    class_file->file_path = file_path_buffer;
    class_file->mode = get_file_mode_string(FILE_MODE_R_PLUS);
    class_file->cell_size = DEFAULT_CELL_SIZE;
    class_file->columns_number = 9;
    class_file->delimiter = ',';
    // 检测是否存在的临时方法
    FILE *f = fopen(class_file->file_path, "r");
    if (f) {
        fclose(f);
    } else {
        f = fopen(class_file->file_path, "w");
        fclose(f);
    }
    open_file(class_file);
    if (count_rows(class_file) == 0) {
        char** title = calloc(class_file->columns_number, sizeof(char*));
        for (int i = 0; i < class_file->columns_number; i++) {
            title[i] = calloc(class_file->cell_size + 1, sizeof(char));
        }
        strcpy(title[0], "学号");
        strcpy(title[1], "姓名");
        strcpy(title[2], "性别");
        strcpy(title[3], "班级");
        strcpy(title[4], "计算机");
        strcpy(title[5], "数学");
        strcpy(title[6], "英语");
        strcpy(title[7], "总分");
        strcpy(title[8], "平均分");

        for (int i = 0; i < class_file->columns_number; i++) {
            title[i] = fill_blanks(title[i], class_file->cell_size, class_file->delimiter);
        }
        char* result = concat_row(title, class_file->cell_size, class_file->columns_number);
        add_row(class_file, result, count_rows(class_file));
        for (int i = 0; i < class_file->columns_number; i++) {
            free(title[i]);
        }
        free(title);
        free(result);
    }
    return class_file;
}

char* list_choose_classes() {
    char* path_buffer = calloc(MAX_FILE_STR_LEN, sizeof(char));
    snprintf(path_buffer, MAX_FILE_STR_LEN, "%s/%s", DIR, "*");
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = INVALID_HANDLE_VALUE;

    // 查找当前目录下的所有文件
    hFind = FindFirstFile(_T(path_buffer), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "目录打开错误\n");
        exit(EXIT_FAILURE);
    }

    char** files = calloc(1024, sizeof(char*));

    int count = 0;
    do {
        // 跳过 "." 和 ".." 目录以及隐藏文件
        if (_tcscmp(findFileData.cFileName, _T(".")) == 0 ||
            _tcscmp(findFileData.cFileName, _T("..")) == 0 ||
            (findFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)) {
            continue;
            }

        int length = strlen(findFileData.cFileName);
        char* file = calloc(length + 1, sizeof(char));
        strcpy(file, findFileData.cFileName);
        files[count++] = file;
    } while (FindNextFile(hFind, &findFileData) != 0);

    printf("共有 %d 个 班级文件。\n", count);
    for (int i = 0; i < count; i++) {
        printf("[%d] %s\n", i, files[i]);
    }
    free(path_buffer);

    printf("按下 数字索引 选择要操作的班级文件。\n");
    printf("请输入：\n");
    int index = 0;
    scanf("%d", &index);
    char* result = calloc(strlen(files[index]) + 1, sizeof(char));
    strcpy(result, files[index]);
    for (int i = 0; i < count; i++) {
        free(files[i]);
    }
    free(files);

    press_to_exit_function();
    return result;
}

void save_class(node_ptr head, char* file_name) {
    CSV_File *class_file = calloc(1, sizeof(CSV_File));
    if (class_file == NULL) {
        fprintf(stderr, "init_file() 错误：%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    char* file_path_buffer = calloc(MAX_FILE_STR_LEN, sizeof(char));
    snprintf(file_path_buffer, MAX_FILE_STR_LEN, "%s/%s", DIR, file_name);
    class_file->file_path = file_path_buffer;
    class_file->mode = get_file_mode_string(FILE_MODE_W_PLUS);
    class_file->cell_size = DEFAULT_CELL_SIZE;
    class_file->columns_number = 9;
    class_file->delimiter = ',';
    // 检测是否存在的临时方法
    FILE *f = fopen(class_file->file_path, "r");
    if (f) {
        fclose(f);
    } else {
        f = fopen(class_file->file_path, "w");
        fclose(f);
    }
    open_file(class_file);
    if (count_rows(class_file) == 0) {
        char** title = calloc(class_file->columns_number, sizeof(char*));
        for (int i = 0; i < class_file->columns_number; i++) {
            title[i] = calloc(class_file->cell_size + 1, sizeof(char));
        }
        strcpy(title[0], "学号");
        strcpy(title[1], "姓名");
        strcpy(title[2], "性别");
        strcpy(title[3], "班级");
        strcpy(title[4], "计算机");
        strcpy(title[5], "数学");
        strcpy(title[6], "英语");
        strcpy(title[7], "总分");
        strcpy(title[8], "平均分");

        for (int i = 0; i < class_file->columns_number; i++) {
            title[i] = fill_blanks(title[i], class_file->cell_size, class_file->delimiter);
        }
        char* result = concat_row(title, class_file->cell_size, class_file->columns_number);
        add_row(class_file, result, count_rows(class_file));
        for (int i = 0; i < class_file->columns_number; i++) {
            free(title[i]);
        }
        free(title);
        free(result);
    }

    for (node_ptr p = head->next; p != head; p = p->next) {
        char** row_elements = calloc(class_file->columns_number, sizeof(char*));
        int length = class_file->cell_size + 1;
        for (int i = 0; i < class_file->columns_number; i++) {
            row_elements[i] = calloc(length, sizeof(char));
        }
        strcpy(row_elements[0], ((student*)(p->data))->number);
        strcpy(row_elements[1], ((student*)(p->data))->name);
        strcpy(row_elements[2], ((student*)(p->data))->sex);
        strcpy(row_elements[3], ((student*)(p->data))->class_no);
        snprintf(row_elements[4], length, "%.2lf", ((student*)(p->data))->score[COMPUTER_SUBJECT]);
        snprintf(row_elements[5], length, "%.2lf", ((student*)(p->data))->score[MATH_SUBJECT]);
        snprintf(row_elements[6], length, "%.2lf", ((student*)(p->data))->score[ENGLISH_SUBJECT]);
        snprintf(row_elements[7], length, "%.2lf", ((student*)(p->data))->sum);
        snprintf(row_elements[8], length, "%.2lf", ((student*)(p->data))->avg);
        for (int i = 0; i < class_file->columns_number; i++) {
            row_elements[i] = fill_blanks(row_elements[i], class_file->cell_size, class_file->delimiter);
        }
        char* result = concat_row(row_elements, class_file->cell_size, class_file->columns_number);
        add_row(class_file, result, count_rows(class_file));
        for (int i = 0; i < class_file->columns_number; i++) {
            free(row_elements[i]);
        }
        free(row_elements);
        free(result);
    }
    free_list(head);
    close_file(class_file);
}

void close_class(CSV_File *class) {
    close_file(class);
}

void delete_class(char* file_name) {
    char* file_path_buffer = calloc(MAX_FILE_STR_LEN, sizeof(char));
    snprintf(file_path_buffer, MAX_FILE_STR_LEN, "%s/%s", DIR, file_name);
    if (remove(file_path_buffer) == 0) {
        printf("文件 %s 删除成功\n", file_path_buffer);
    } else {
        fprintf(stderr, "删除文件失败!");
        exit(EXIT_FAILURE);
    }
}