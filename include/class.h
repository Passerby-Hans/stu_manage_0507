//
// Created by Hans on 25-5-12.
//

#ifndef CLASS_H
#define CLASS_H

#include "hans_utils.h"
#include "manager.h"
#include "csv_file_utils.h"
#include "linked_list.h"
#include "student.h"
#include <tchar.h>
#include <direct.h>
#include <windows.h>

#define DEFAULT_CELL_SIZE 25

//tested
CSV_File *open_class(char* file_name);

//tested
char* list_choose_classes();

//tested
void save_class(node_ptr head, char* file_name);

void close_class(CSV_File *class);

//tested
void delete_class(char* file_name);

#endif //CLASS_H
