#include <stdio.h>
#include "hans_utils.h"
#include "manager.h"
#include "class.h"

int main(void) {
    init_file_system();
    printf("Hello, World!\n");
    print_about();
    CSV_File* test1 = open_class("test.csv");
    CSV_File* test2 = open_class("test1.csv");
    close_file(test1);
    close_file(test2);
    char* class = list_choose_classes();
    printf("%s\n", class);
    CSV_File* test3 = open_class(class);
    read_from_class(test3);
    close_file(test3);
    return 0;
}
