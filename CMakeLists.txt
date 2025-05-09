cmake_minimum_required(VERSION 4.0)
project(Student_Manage_System_0507 C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

add_executable(Student_Manage_System_0507
        src/main.c
        src/linked_list.c
        src/csv_file_utils.c
        src/hans_utils.c
)

target_compile_options(Student_Manage_System_0507 PRIVATE -finput-charset=UTF-8 -fexec-charset=GBK)

