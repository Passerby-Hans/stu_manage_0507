//
// Created by hules on 25-3-5.
//
#include "hans_utils.h"

void clean_screen(const int row, const int column) {
    printf("\033[%d;%dH", row, column);
    printf("\033[J");
}

void press_to_exit_function() {
    printf("按任意键退出或返回上一级...\n");
    getchar();
    clean_stdin();
}

void clean_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

struct tm *get_gmt8_time() {
    time_t rawtime;
    INIT_TIMESTAMP(rawtime);
    struct tm *tm_info = localtime(&rawtime);
}
void print_about() {
    struct tm *time_info = get_gmt8_time();
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", time_info);
    printf("现在时间: %s\n", buffer);
    printf("作者：Hans\n");
    printf("2025-05\n");
}
