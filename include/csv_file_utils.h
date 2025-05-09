//
// Created by hules on 25-4-23.
//

#ifndef CSV_FILE_UTILS_H
#define CSV_FILE_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_STR_LEN 4096

typedef enum { FILE_STATE_UNKNOWN, FILE_STATE_READ, FILE_STATE_WRITE } FileState;

typedef struct CSV_File {
    FILE *file;
    const char* mode;
    int cell_size;
    int columns_number;
    char* file_path;
    char delimiter;
    FileState last_op;
} CSV_File;

typedef enum {
    FILE_MODE_R,      // "r"
    FILE_MODE_W,      // "w"
    FILE_MODE_A,      // "a"
    FILE_MODE_R_PLUS, // "r+"
    FILE_MODE_W_PLUS, // "w+"
    FILE_MODE_A_PLUS, // "a+"
} FileMode;

const char* get_file_mode_string(FileMode mode);

//
void open_file(CSV_File* file);
//
void read_row(CSV_File* file, char** row);
//
void write_row(CSV_File* file, char* row);
//
void add_row(CSV_File* file, char* string, int index_row);
//
void* close_file(CSV_File* file);
//
int count_rows(CSV_File* file);
//
void move_fp(CSV_File* file, int row, int column);
void move_fp_add_row(CSV_File* file, int row, int column);
//
void read_by_indexes(CSV_File* file, char** string, int index_row, int index_column);
//
char** split(const char* string, char delimiter, int* block_res);
//
char* remove_blanks(char* string);
//
void read_row_by_indexes(CSV_File* file, char** string, int index_row);
//
char* fill_blanks(char* string, int blank_size, char delimiter);
//
void change_status(CSV_File* file, FileState next_state);

char* concat_row(char** strings, int cell_size, int columns);

#endif //CSV_FILE_UTILS_H
