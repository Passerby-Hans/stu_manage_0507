//
// Created by Hans on 25-5-12.
//

#include "student.h"

node_ptr read_from_class(CSV_File *class) {
    node_ptr head = init_list();

    for (int i = 1; i < count_rows(class); i++) {
        char *row = NULL;
        read_row_by_indexes(class, &row, i);
        int length = 0;
        char **cells = split(row, ',', &length);
        for (int j = 0; j < length; j++) {
            cells[j] = remove_blanks(cells[j]);
            // printf("%s ", cells[j]);
        }
        student *stu = calloc(1, sizeof(student));
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

        add_tail(head, stu);
        // putchar('\n');
    }
    close_file(class);
    return head;
}

void visit_print(void *stu) {
    student *stu_s = (student *) stu;
    printf("%10s%10s%10s%10s%10.2lf%10.2lf%10.2lf%10.2lf%10.2lf\n", stu_s->number, stu_s->name, stu_s->sex,
           stu_s->class_no, stu_s->score[COMPUTER_SUBJECT], stu_s->score[MATH_SUBJECT], stu_s->score[ENGLISH_SUBJECT],
           stu_s->sum, stu_s->avg);
}

void list_students(node_ptr head, int order) {
    printf("共有 %d 条记录\n", get_length(head));
    printf("%10s%10s%10s%10s%10s%10s%10s%10s%10s\n", "学号", "姓名", "性别", "班级", "计算机", "数学", "英语", "总分",
           "平均分");

    traversal_list(head, order, visit_print);
}

void input_student(node_ptr head) {
    student *stu = calloc(1, sizeof(student));
    printf("请输入学号：\n");
    if (scanf("%s", (stu)->number) != 1) {
        fprintf(stderr, "读取失败\n");
        exit(EXIT_FAILURE);
    }
    printf("请输入姓名：\n");
    if (scanf("%s", (stu)->name) != 1) {
        fprintf(stderr, "读取失败\n");
        exit(EXIT_FAILURE);
    }
    printf("请输入性别：\n");
    if (scanf("%s", (stu)->sex) != 1) {
        fprintf(stderr, "读取失败\n");
        exit(EXIT_FAILURE);
    }
    printf("请输入班级：\n");
    if (scanf("%s", (stu)->class_no) != 1) {
        fprintf(stderr, "读取失败\n");
        exit(EXIT_FAILURE);
    }
    char temp[100];
    printf("请输入计算机成绩：\n");
    if (scanf("%s", temp) != 1) {
        fprintf(stderr, "读取失败\n");
        exit(EXIT_FAILURE);
    }
    (stu)->score[COMPUTER_SUBJECT] = strtod(temp, NULL);


    printf("请输入数学成绩：\n");
    if (scanf("%s", temp ) != 1) {
        fprintf(stderr, "读取失败\n");
        exit(EXIT_FAILURE);
    }
    (stu)->score[MATH_SUBJECT] = strtod(temp, NULL);

    printf("请输入英语成绩：\n");
    if (scanf("%s", temp) != 1) {
        fprintf(stderr, "读取失败\n");
        exit(EXIT_FAILURE);
    }
    (stu)->score[ENGLISH_SUBJECT] = strtod(temp, NULL);

    (stu)->sum = (stu)->score[COMPUTER_SUBJECT] +
                                        (stu)->score[MATH_SUBJECT] +
                                        (stu)->score[ENGLISH_SUBJECT];
    (stu)->avg = (stu)->sum / NUM_SUBJECT;

    add_tail(head, stu);
}

int name_compartor(void *this, void *that) { return strcmp(((student*)this)->name, ((student*)that)->name); }

int number_compartor(void *this, void *that) { return strcmp(((student*)this)->number, ((student*)that)->number); }

node_ptr find_name(node_ptr head) {
    student *temp_stu = calloc(1, sizeof(student));
    printf("请输入姓名：\n");
    if (scanf("%s", temp_stu->name) != 1) {
        fprintf(stderr, "读取失败\n");
        exit(EXIT_FAILURE);
    }
    node_ptr target = get_item(head, temp_stu, name_compartor);
    free(temp_stu);
    return target;
}

node_ptr find_number(node_ptr head) {
    student *temp_stu = calloc(1, sizeof(student));
    printf("请输入学号：\n");
    if (scanf("%s", temp_stu->number) != 1) {
        fprintf(stderr, "读取失败\n");
        exit(EXIT_FAILURE);
    }

    node_ptr target = get_item(head, temp_stu, number_compartor);
    free(temp_stu);
    return target;
}

void find_students_by_name(node_ptr head) {
    node_ptr target = find_name(head);
    if (target == NULL)
        printf("没有找到对应的记录！\n");
    else
        visit_print(target->data);
}

void find_students_by_number(node_ptr head) {
    node_ptr target = find_number(head);
    if (target == NULL)
        printf("没有找到对应的记录！\n");
    else
        visit_print(target->data);
}

void delete_student_by_name(node_ptr head) {
    student *temp_stu = calloc(1, sizeof(student));
    node_ptr target = find_name(head);

    if (target == NULL) {
        printf("没有找到对应的记录！\n");
    } else {
        memcpy(target->data, temp_stu, sizeof(student));
        delete_item(head, temp_stu, name_compartor);
    }

    free(temp_stu);
}

void delete_student_by_number(node_ptr head) {
    student *temp_stu = calloc(1, sizeof(student));
    node_ptr target = find_number(head);

    if (target == NULL) {
        printf("没有找到对应的记录！\n");
    } else {
        memcpy(target->data, temp_stu, sizeof(student));
        delete_item(head, temp_stu, number_compartor);
    }

    free(temp_stu);
}

int double_compartor(double this, double that) { return this >= that ? 1 : this == that ? 0 : -1; }

int computer_score_compartor(void *this, void *that) {
    return double_compartor(((student*)this)->score[COMPUTER_SUBJECT], ((student*)that)->score[COMPUTER_SUBJECT]);
}

int math_score_compartor(void *this, void *that) {
    return double_compartor(((student*)this)->score[MATH_SUBJECT], ((student*)that)->score[MATH_SUBJECT]);
}

int english_score_compartor(void *this, void *that) {
    return double_compartor(((student*)this)->score[ENGLISH_SUBJECT], ((student*)that)->score[ENGLISH_SUBJECT]);
}

int sum_compartor(void *this, void *that) { return double_compartor(((student*)this)->sum, ((student*)that)->sum); }

int avg_compartor(void *this, void *that) { return double_compartor(((student*)this)->avg, ((student*)that)->avg); }

void sort_students(node_ptr head, int compartor) {
    int (*compartor_list_A[7])(void *, void *);
    compartor_list_A[NUMBER_COMPARTOR] = number_compartor;
    compartor_list_A[NAME_COMPARTOR] = name_compartor;
    compartor_list_A[COMPUTER_SCORE_COMPARTOR] = computer_score_compartor;
    compartor_list_A[MATH_SCORE_COMPARTOR] = math_score_compartor;
    compartor_list_A[ENGLISH_SCORE_COMPARTOR] = english_score_compartor;
    compartor_list_A[SUM_COMPARTOR] = sum_compartor;
    compartor_list_A[AVG_COMPARTOR] = avg_compartor;

    switch (compartor) {
        case NUMBER_COMPARTOR:
            bubble_sort(head, compartor_list_A[NUMBER_COMPARTOR]);
            break;
        case NAME_COMPARTOR:
            bubble_sort(head, compartor_list_A[NAME_COMPARTOR]);
            break;
        case COMPUTER_SCORE_COMPARTOR:
            bubble_sort(head, compartor_list_A[COMPUTER_SCORE_COMPARTOR]);
            break;
        case MATH_SCORE_COMPARTOR:
            bubble_sort(head, compartor_list_A[MATH_SCORE_COMPARTOR]);
            break;
        case ENGLISH_SCORE_COMPARTOR:
            bubble_sort(head, compartor_list_A[ENGLISH_SCORE_COMPARTOR]);
            break;
        case SUM_COMPARTOR:
            bubble_sort(head, compartor_list_A[SUM_COMPARTOR]);
            break;
        case AVG_COMPARTOR:
            bubble_sort(head, compartor_list_A[AVG_COMPARTOR]);
            break;
        default:
            printf("错误的参数！\n");
    }

}

void update_student_by_name(node_ptr head) {
    node_ptr target = find_name(head);

    if (target == NULL) {
        printf("没有找到对应的记录！\n");
    } else {
        printf("请输入学号：\n");
        if (scanf("%s", ((student *) (target->data))->number) != 1) {
            fprintf(stderr, "读取失败\n");
            exit(EXIT_FAILURE);
        }
        printf("请输入姓名：\n");
        if (scanf("%s", ((student *) (target->data))->name) != 1) {
            fprintf(stderr, "读取失败\n");
            exit(EXIT_FAILURE);
        }
        printf("请输入性别：\n");
        if (scanf("%s", ((student *) (target->data))->sex) != 1) {
            fprintf(stderr, "读取失败\n");
            exit(EXIT_FAILURE);
        }
        printf("请输入班级：\n");
        if (scanf("%s", ((student *) (target->data))->class_no) != 1) {
            fprintf(stderr, "读取失败\n");
            exit(EXIT_FAILURE);
        }
        char temp[100];
        printf("请输入计算机成绩：\n");
        if (scanf("%s", temp) != 1) {
            fprintf(stderr, "读取失败\n");
            exit(EXIT_FAILURE);
        }
        ((student *) (target->data))->score[COMPUTER_SUBJECT] = strtod(temp, NULL);


        printf("请输入数学成绩：\n");
        if (scanf("%s", temp ) != 1) {
            fprintf(stderr, "读取失败\n");
            exit(EXIT_FAILURE);
        }
        ((student *) (target->data))->score[MATH_SUBJECT] = strtod(temp, NULL);

        printf("请输入英语成绩：\n");
        if (scanf("%s", temp) != 1) {
            fprintf(stderr, "读取失败\n");
            exit(EXIT_FAILURE);
        }
        ((student *) (target->data))->score[ENGLISH_SUBJECT] = strtod(temp, NULL);

        ((student *) (target->data))->sum = ((student *) (target->data))->score[COMPUTER_SUBJECT] +
                                            ((student *) (target->data))->score[MATH_SUBJECT] +
                                            ((student *) (target->data))->score[ENGLISH_SUBJECT];
        ((student *) (target->data))->avg = ((student *) (target->data))->sum / NUM_SUBJECT;
    }
}
void update_student_by_number(node_ptr head) {
    node_ptr target = find_number(head);

    if (target == NULL) {
        printf("没有找到对应的记录！\n");
    } else {
        printf("请输入学号：\n");
        if (scanf("%s", ((student *) (target->data))->number) != 1) {
            fprintf(stderr, "读取失败\n");
            exit(EXIT_FAILURE);
        }
        printf("请输入姓名：\n");
        if (scanf("%s", ((student *) (target->data))->name) != 1) {
            fprintf(stderr, "读取失败\n");
            exit(EXIT_FAILURE);
        }
        printf("请输入性别：\n");
        if (scanf("%s", ((student *) (target->data))->sex) != 1) {
            fprintf(stderr, "读取失败\n");
            exit(EXIT_FAILURE);
        }
        printf("请输入班级：\n");
        if (scanf("%s", ((student *) (target->data))->class_no) != 1) {
            fprintf(stderr, "读取失败\n");
            exit(EXIT_FAILURE);
        }
        char temp[100];
        printf("请输入计算机成绩：\n");
        if (scanf("%s", temp) != 1) {
            fprintf(stderr, "读取失败\n");
            exit(EXIT_FAILURE);
        }
        ((student *) (target->data))->score[COMPUTER_SUBJECT] = strtod(temp, NULL);


        printf("请输入数学成绩：\n");
        if (scanf("%s", temp ) != 1) {
            fprintf(stderr, "读取失败\n");
            exit(EXIT_FAILURE);
        }
        ((student *) (target->data))->score[MATH_SUBJECT] = strtod(temp, NULL);

        printf("请输入英语成绩：\n");
        if (scanf("%s", temp) != 1) {
            fprintf(stderr, "读取失败\n");
            exit(EXIT_FAILURE);
        }
        ((student *) (target->data))->score[ENGLISH_SUBJECT] = strtod(temp, NULL);

        ((student *) (target->data))->sum = ((student *) (target->data))->score[COMPUTER_SUBJECT] +
                                            ((student *) (target->data))->score[MATH_SUBJECT] +
                                            ((student *) (target->data))->score[ENGLISH_SUBJECT];
        ((student *) (target->data))->avg = ((student *) (target->data))->sum / NUM_SUBJECT;
    }
}
