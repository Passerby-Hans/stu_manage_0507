#include <stdio.h>
#include "hans_utils.h"
#include "manager.h"
#include "class.h"

int main(void) {
    init_file_system();
    printf("Hello, World!\n");
    general_menu();
    return 0;
}
