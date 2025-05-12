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
    char sex[4];
    char class_no[10];
    double score[NUM_SUBJECT];
    double sum;
    double avg;
} student;


node_ptr read_from_class(CSV_File* class);


#endif //STUDENT_H
