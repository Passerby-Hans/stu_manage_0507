//
// Created by hules on 25-3-5.
//

#ifndef HANS_CMD_H
#define HANS_CMD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INIT_TIMESTAMP(var) \
  (var = time(NULL))

void clean_screen(int row, int column);
void press_to_exit_function();
void clean_stdin();
struct tm get_gmt8_time();
void print_about();

#endif //HANS_CMD_H
