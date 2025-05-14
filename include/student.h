//
// Created by hules on 25-5-7.
//

#ifndef STUDENT_H
#define STUDENT_H

#include "linked_list.h"
#include "csv_file_utils.h"
#include "hans_utils.h"
#include "manager.h"
#include "class.h"

// 计算机 数学 英语
#define NUM_SUBJECT 3

#define COMPUTER_SUBJECT 0
#define MATH_SUBJECT 1
#define ENGLISH_SUBJECT 2

typedef struct student {
    char number[20];
    char name[20];
    char sex[8];
    char class_no[20];
    double score[NUM_SUBJECT];
    double sum;
    double avg;
} student;

enum compartor_num {
    NUMBER_COMPARTOR,
    NAME_COMPARTOR,
    COMPUTER_SCORE_COMPARTOR,
    MATH_SCORE_COMPARTOR,
    ENGLISH_SCORE_COMPARTOR,
    SUM_COMPARTOR,
    AVG_COMPARTOR
};

// tested
node_ptr read_from_class(CSV_File* class);

void visit_print(void* stu);
// tested
void list_students(node_ptr head, int order);
// tested
void input_student(node_ptr head);
// tested
void find_students_by_name(node_ptr head);
// tested
void find_students_by_number(node_ptr head);
// tested
void delete_student_by_name(node_ptr head);
// tested
void delete_student_by_number(node_ptr head);
// tested
void update_student_by_name(node_ptr head);
// tested
void update_student_by_number(node_ptr head);
// tested
void sort_students(node_ptr head, int compartor);



#endif //STUDENT_H
