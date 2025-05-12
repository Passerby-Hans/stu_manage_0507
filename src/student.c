//
// Created by Hans on 25-5-12.
//

#include "student.h"

node_ptr read_from_class(CSV_File* class) {
    node_ptr head = init_list();

    for (int i = 0; i < count_rows(class); i++) {
        char* row = NULL;
        read_row_by_indexes(class, &row, i);
        int length = 0;
        char** cells = split(row, ',', &length);
        for (int j = 0; j < length; j++) {
            cells[j] = remove_blanks(cells[j]);
            // printf("%s ", cells[j]);
        }
        student* stu = calloc(1, sizeof(student));
        strcpy(stu->number, cells[0]);
        strcpy(stu->name, cells[1]);
        strcpy(stu->sex, cells[2]);
        strcpy(stu->class_no, cells[3]);
        double d1 = strtod(cells[4], NULL);
        double d2 = strtod(cells[5], NULL);
        double d3 = strtod(cells[6], NULL);
        stu->score[COMPUTER_SUBJECT] = d1;
        stu->score[MATH_SUBJECT] = d2;
        stu->score[ENGLISH_SUBJECT] = d3;

        double d4 = strtod(cells[7], NULL);
        double d5 = strtod(cells[8], NULL);
        stu->sum = d4;
        stu->avg = d5;
        // putchar('\n');
    }
}