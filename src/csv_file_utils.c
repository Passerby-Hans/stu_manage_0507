//
// Created by Hans on 25-4-27.
//
#include "csv_file_utils.h"


const char *get_file_mode_string(FileMode mode) {
    switch (mode) {
        case FILE_MODE_R:
            return "r";
        case FILE_MODE_W:
            return "w";
        case FILE_MODE_A:
            return "a";
        case FILE_MODE_R_PLUS:
            return "r+";
        case FILE_MODE_W_PLUS:
            return "w+";
        case FILE_MODE_A_PLUS:
            return "a+";
        default:
            return NULL;
    }
}

void open_file(CSV_File *file) {
    if (file == NULL) {
        fprintf(stderr, "错误：文件指针为空！\n");
        return;
    }
    if (file->file_path == NULL || file->mode == NULL) {
        fprintf(stderr, "错误：文件路径或模式为空！\n");
        exit(EXIT_FAILURE);
    }
    if (!((file->file = fopen(file->file_path, file->mode)))) {
        fprintf(stderr, "错误：无法打开文件 '%s'，模式 '%s'\n原因：%s\n", file->file_path, file->mode, strerror(errno));
        exit(EXIT_FAILURE);
    }
    file->last_op = FILE_STATE_UNKNOWN;
}


void* close_file(CSV_File *file) {
    if (file == NULL) {
        fprintf(stderr, "错误：文件指针为空！\n");
        exit(EXIT_FAILURE);
    }
    if (file->file_path == NULL || file->mode == NULL) {
        fprintf(stderr, "错误：文件路径或模式为空！\n");
        exit(EXIT_FAILURE);
    }
    if (file->file != NULL) {
        fclose(file->file);
        file->file = NULL;
    }
    file->mode = NULL;
    if (file->file_path != NULL) {
        free(file->file_path);
        file->file_path = NULL;
    }
    file->cell_size = 0;
    file->columns_number = 0;
    free(file);
    return NULL;
}

void read_row(CSV_File* file, char** row) {

    if (file == NULL || row == NULL || file->file == NULL) {
        fprintf(stderr, "错误：文件或行缓冲指针为空！\n");
        exit(EXIT_FAILURE);
    }
    if (file->cell_size == 0 || file->columns_number == 0) {
        fprintf(stderr, "错误：列数或单元格大小为空！\n");
        exit(EXIT_FAILURE);
    }
    change_status(file, FILE_STATE_READ);
    // 接受字符串 + \n + \0
    int size = file->cell_size * file->columns_number + 1 + 1;
    char* row_string = calloc(size, sizeof(char));
    if (row_string == NULL) {
        fprintf(stderr, "错误：calloc失败！\n");
        exit(EXIT_FAILURE);
    }
    if (fgets(row_string, size, file->file) == NULL) {
        if (feof(file->file)) {
            printf("提示：读到文件末尾了。\n");
        } else if (ferror(file->file)) {
            fprintf(stderr,"错误：读取文件时发生错误！\n");
            free(row_string);
            exit(EXIT_FAILURE);
        }
    }
    row_string[size - 1 - 1] = '\0';
    *row = row_string;
    file->last_op = FILE_STATE_READ;
}

void write_row(CSV_File* file, char* row) {

    if (file == NULL || row == NULL || file->file == NULL) {
        fprintf(stderr, "错误：文件或行缓冲指针为空！\n");
        exit(EXIT_FAILURE);
    }
    if (file->cell_size == 0 || file->columns_number == 0) {
        fprintf(stderr, "错误：列数或单元格大小为空！\n");
        exit(EXIT_FAILURE);
    }
    change_status(file, FILE_STATE_WRITE);
    unsigned long long length = strlen(row);
    if (length != file->cell_size * file->columns_number) {
        fprintf(stderr, "错误：写入格式错误！\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file->file, "%s", row);
    file->last_op = FILE_STATE_WRITE;
}

int count_rows(CSV_File* file) {
    change_status(file, FILE_STATE_READ);
    if (file == NULL || file->file == NULL) {
        fprintf(stderr, "错误：文件为空！\n");
        exit(EXIT_FAILURE);
    }
    int length = 0;
    int ch;
    fseek(file->file, 0, SEEK_SET);
    while ((ch = fgetc(file->file)) != EOF) {
        if (ch == '\n') {
            length++;
        }
    }
    file->last_op = FILE_STATE_READ;
    return length;
}

void move_fp(CSV_File* file, int row, int column) {

    if (file == NULL || file->file == NULL) {
        fprintf(stderr, "错误：文件为空！\n");
        exit(EXIT_FAILURE);
    }
    if (file->cell_size <= 0) {
        fprintf(stderr, "错误：错误的单元格大小！\n");
        exit(EXIT_FAILURE);
    }
    // printf("start p:%ld\n", ftell(file->file));
    if (row < 0 || row > count_rows(file) || column < 0 || column >= file->columns_number) {
        fprintf(stderr, "错误：错误的行数/列数！\n");
        exit(EXIT_FAILURE);
    }
    fseek(file->file, 0, SEEK_SET);
    // printf("start2 p:%ld\n", ftell(file->file));
    int offset = (row) * (file->columns_number * file->cell_size + 2) + column * file->cell_size;
    int result = fseek(file->file, offset, SEEK_SET);
    // printf("end p:%ld\n", ftell(file->file));
    if (result != 0) {
        fprintf(stderr, "错误：移动指针失败！\n");
        exit(EXIT_FAILURE);
    }
}

void add_row(CSV_File* file, char* string, int index_row) {
    if (file == NULL || string == NULL || file->file == NULL) {
        fprintf(stderr, "错误：文件或行缓冲指针为空！\n");
        exit(EXIT_FAILURE);
    }
    if (strcmp(file->mode, get_file_mode_string(FILE_MODE_R)) == 0) {
        fprintf(stderr, "错误：只读模式不可写！\n");
        exit(EXIT_FAILURE);
    }
    if (strcmp(file->mode, get_file_mode_string(FILE_MODE_A)) == 0 ||
        strcmp(file->mode, get_file_mode_string(FILE_MODE_A_PLUS)) == 0) {
        if (fseek(file->file, 0, SEEK_END) != 0) {
            fprintf(stderr, "错误：移动指针失败！\n");
            exit(EXIT_FAILURE);
        }
        write_row(file, string);
    } else {
        move_fp(file, index_row, 0);
        write_row(file, string);
        fputc('\n', file->file);
    }
}

char** split(const char* string, char delimiter, int* block_res) {
    int size = strlen(string);
    int blocks = 0;
    for (int i = 0; i < size; i++) {
        if (string[i] == delimiter) {
            blocks++;
        }
    }
    // 鉴于都以逗号结尾……
    //blocks++;
    char** result = calloc(blocks, sizeof(char*));
    if (!result) {
        fprintf(stderr, "错误：开辟内存失败！\n");
        exit(EXIT_FAILURE);
    }
    int index = 0;
    int offset = 0;
    int res_index = 0;
    while (index < size) {
        while (index + offset < size && string[index + offset] != delimiter) {
            offset++;
        }
        char* sub_str = calloc(offset + 1, sizeof(char));
        if (!sub_str) {
            fprintf(stderr, "错误：开辟内存失败！\n");
            exit(EXIT_FAILURE);
        }
        for (int i = index; i < index + offset; i++) {
            sub_str[i - index] = string[i];
        }
        sub_str[offset] = '\0';
        result[res_index] = sub_str;
        res_index++;
        index += offset + 1;
        offset = 0;
    }
    *block_res = blocks;
    return result;
}

char* remove_blanks(char* string) {
    if (string == NULL) {
        return NULL;
    }
    int length = strlen(string);
    int begin = 0;
    while (begin < length && string[begin] == ' ') {
        begin++;
    }
    char* new_string = calloc(length - begin + 1, sizeof(char));
    if (!new_string) {
        fprintf(stderr, "错误：开辟内存失败！\n");
        exit(EXIT_FAILURE);
    }
    strcpy(new_string, string + begin);
    free(string);
    return new_string;
}

void read_by_indexes(CSV_File* file, char** string, int index_row, int index_column) {
    if (file == NULL || string == NULL || file->file == NULL) {
        fprintf(stderr, "错误：文件或行缓冲指针为空！\n");
        exit(EXIT_FAILURE);
    }
    if (file->cell_size == 0 || file->columns_number == 0) {
        fprintf(stderr, "错误：列数或单元格大小为空！\n");
        exit(EXIT_FAILURE);
    }
    change_status(file, FILE_STATE_READ);
    int size = file->cell_size + 1;
    char* index_string = calloc(size, sizeof(char));
    if (index_string == NULL) {
        fprintf(stderr, "错误：calloc失败！\n");
        exit(EXIT_FAILURE);
    }

    move_fp(file, index_row, index_column);

    int end = fread(index_string, sizeof(char), size, file->file);
    index_string[end] = '\0';

    index_string[size - 1 - 1] = '\0';
    *string = index_string;
    file->last_op = FILE_STATE_READ;
}

void read_row_by_indexes(CSV_File* file, char** string, int index_row) {
    if (file == NULL || string == NULL || file->file == NULL) {
        fprintf(stderr, "错误：文件或行缓冲指针为空！\n");
        exit(EXIT_FAILURE);
    }
    if (file->cell_size == 0 || file->columns_number == 0) {
        fprintf(stderr, "错误：列数或单元格大小为空！\n");
        exit(EXIT_FAILURE);
    }
    move_fp(file, index_row, 0);
    read_row(file, string);
}

char* fill_blanks(char* string, int blank_size, char delimiter) {
    if (string == NULL) {
        return NULL;
    }
    int str_length = strlen(string);
    if (string[str_length - 1] != delimiter) {
        char* deli_str = calloc(str_length + 1 + 1, sizeof(char));
        int i = 0;
        for (; i < str_length; i++) {
            deli_str[i] = string[i];
        }
        deli_str[i] = delimiter;
        deli_str[i + 1] = '\0';
        string = deli_str;
        str_length = strlen(deli_str);
    }
    if (blank_size < str_length) {
        return NULL;
    }
    if (blank_size == str_length) {
        return string;
    } else {
        char* new_string = calloc(blank_size + 1, sizeof(char));
        int blanks = blank_size - str_length;
        for (int i = 0; i < blank_size + 1; i++) {
            if (i < blanks) {
                new_string[i] = ' ';
            } else {
                new_string[i] = string[i - blanks];
            }
        }
        free(string);
        return new_string;
    }
}

void change_status(CSV_File* file, FileState next_state) {
    if (file == NULL || file->file == NULL) {
        return;
    }
    if (file->last_op == next_state) {
        return;
    }
    if (file->last_op == FILE_STATE_UNKNOWN) {
        return;
    }
    if (file->last_op == FILE_STATE_READ && next_state == FILE_STATE_WRITE) {
        fseek(file->file, 0, SEEK_CUR);  // 也可以其他位置
        clearerr(file->file);
    }
    if (file->last_op == FILE_STATE_WRITE && next_state == FILE_STATE_READ) {
        fflush(file->file);
        fseek(file->file, 0, SEEK_CUR);
        clearerr(file->file);
    }
}

char* concat_row(char** strings, int cell_size, int columns) {
    int length = cell_size * columns + 1;
    char* result = calloc(length, sizeof(char));
    int offset = 0;
    for (int i = 0; i < columns; i++) {
        int written = snprintf(result + offset, length - offset, "%s", strings[i]);
        if (written < 0 || written >= length - offset) {
            fprintf(stderr, "concat_row() 错误\n");
            exit(EXIT_FAILURE);
        }
        offset += written;
    }
    return result;
}