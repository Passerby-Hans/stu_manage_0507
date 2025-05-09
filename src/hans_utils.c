//
// Created by hules on 25-3-5.
//
#include "hans_utils.h"

void clean_screen(const int row, const int column)
{
    printf("\033[%d;%dH", row, column);
    printf("\033[J");
}

void press_to_exit_function()
{
    clean_stdin();
    printf("按任意键退出或返回上一级...\n");
    getchar();
}

void clean_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

struct tm get_gmt8_time() {
    time_t rawtime;
    INIT_TIMESTAMP(rawtime);
}
void print_about() {

}
