//
// Created by Hans on 25-5-12.
//

#include "manager.h"
void init_file_system() {
    const char *dir_name = DIR;
    DWORD dwAttrib = GetFileAttributes(dir_name);
    if (dwAttrib == INVALID_FILE_ATTRIBUTES) {
        if (_mkdir(dir_name) == -1) {
            fprintf(stderr, "创建文件夹失败！\n");
            exit(EXIT_FAILURE);
        } else if (dwAttrib & FILE_ATTRIBUTE_DIRECTORY) {
        } else {
            fprintf(stderr, "路径已存在但不是目录\n");
            exit(EXIT_FAILURE);
        }
    }
}

void operate_exist_file() {
    clean_screen(1, 1);
    char *operating_file = list_choose_classes();
    if (operating_file == NULL) {
        printf("输入无效！\n");
        return;
    }
    CSV_File *class = open_class(operating_file);
    node_ptr list = read_from_class(class);
    while (1) {
        clean_screen(1, 1);
        printf("操作文件 %s 中\n", operating_file);
        printf("使用对应数字选择目录选项。其他输入没有效果。\n");
        printf("[1] 显示所有学生\n"
               "[2] 新增学生信息\n"
               "[3] 查找学生信息\n"
               "[4] 删除学生信息\n"
               "[5] 修改学生信息\n"
               "[6] 按指定键排序\n"
               "[7] 保存并退出\n");
        int option;
        do {
            printf("请输入 1-7： ");
        } while (scanf("%d", &option) != 1);
        switch (option) {
            case 1:
                clean_screen(1, 1);
                int order;
                printf("选择显示顺序。\n");
                printf("使用对应数字选择目录选项。其他输入没有效果。\n");
                printf("[0] 升序\n"
                       "[1] 降序\n");
                do {
                    printf("请输入 0-1： ");
                } while (scanf("%d", &order) != 1);
                list_students(list, order);
                press_to_exit_function();
                break;
            case 2:
                clean_screen(1, 1);
                printf("新增学生信息。\n");
                input_student(list);
                press_to_exit_function();
                break;
            case 3:
                clean_screen(1, 1);
                printf("查找学生信息。\n");
                int finding;
                printf("选择查找方式。\n");
                printf("使用对应数字选择目录选项。其他输入没有效果。\n");
                printf("[1] 按学号查找\n"
                       "[2] 按名字查找\n");
                do {
                    printf("请输入 1-2： ");
                } while (scanf("%d", &finding) != 1);
                switch (finding) {
                    case 1:
                        find_students_by_number(list);
                        break;
                    case 2:
                        find_students_by_name(list);
                        break;
                    default:
                        printf("输入无效！\n");
                }
                press_to_exit_function();
                break;
            case 4:
                clean_screen(1, 1);
                printf("删除学生信息。\n");
                int deleting;
                printf("选择删除方式。\n");
                printf("使用对应数字选择目录选项。其他输入没有效果。\n");
                printf("[1] 按学号删除\n"
                       "[2] 按名字删除\n");
                do {
                    printf("请输入 1-2： ");
                } while (scanf("%d", &deleting) != 1);
                switch (deleting) {
                    case 1:
                        delete_student_by_number(list);
                        printf("删除操作完成!\n");
                        break;
                    case 2:
                        delete_student_by_name(list);
                        printf("删除操作完成!\n");
                        break;
                    default:
                        printf("输入无效！\n");
                }
                press_to_exit_function();
                break;
            case 5:
                clean_screen(1, 1);
                printf("修改学生信息。\n");
                int updating;
                printf("选择修改方式。\n");
                printf("使用对应数字选择目录选项。其他输入没有效果。\n");
                printf("[1] 按学号修改\n"
                       "[2] 按名字修改\n");
                do {
                    printf("请输入 1-2： ");
                } while (scanf("%d", &updating) != 1);
                switch (updating) {
                    case 1:
                        update_student_by_number(list);
                        printf("修改操作完成!\n");
                        break;
                    case 2:
                        update_student_by_name(list);
                        printf("修改操作完成!\n");
                        break;
                    default:
                        printf("输入无效！\n");
                }
                press_to_exit_function();
                break;
            case 6:
                clean_screen(1, 1);
                printf("按指定键排序。\n");
                int sorting;
                printf("选择排序方式。\n");
                printf("使用对应数字选择目录选项。其他输入没有效果。\n");
                printf("[0] 按学号排序\n"
                       "[1] 按名字排序\n"
                       "[2] 按计算机成绩排序\n"
                       "[3] 按数学成绩排序\n"
                       "[4] 按英语成绩排序\n"
                       "[5] 按总分排序\n"
                       "[6] 按平均分排序\n");
                do {
                    printf("请输入 0-6： ");
                } while (scanf("%d", &sorting) != 1);
                switch (sorting) {
                    case NUMBER_COMPARTOR:
                        sort_students(list, NUMBER_COMPARTOR);
                        printf("排序操作完成!\n");
                        break;
                    case NAME_COMPARTOR:
                        sort_students(list, NAME_COMPARTOR);
                        printf("排序操作完成!\n");
                        break;
                    case COMPUTER_SCORE_COMPARTOR:
                        sort_students(list, COMPUTER_SCORE_COMPARTOR);
                        printf("排序操作完成!\n");
                        break;
                    case MATH_SCORE_COMPARTOR:
                        sort_students(list, MATH_SCORE_COMPARTOR);
                        printf("排序操作完成!\n");
                        break;
                    case ENGLISH_SCORE_COMPARTOR:
                        sort_students(list, ENGLISH_SCORE_COMPARTOR);
                        printf("排序操作完成!\n");
                        break;
                    case SUM_COMPARTOR:
                        sort_students(list, SUM_COMPARTOR);
                        printf("排序操作完成!\n");
                        break;
                    case AVG_COMPARTOR:
                        sort_students(list, AVG_COMPARTOR);
                        printf("排序操作完成!\n");
                        break;
                    default:
                        printf("输入无效！\n");
                }
                press_to_exit_function();
                break;
            case 7:
                clean_screen(1, 1);
                save_class(list, operating_file);
                printf("保存完成!\n");
                press_to_exit_function();
                return;
            default:
                continue;
        }
    }
}

void operate_new_file() {
    clean_screen(1, 1);
    char *operating_file = calloc(MAX_FILE_STR_LEN, sizeof(char));
    if (operating_file == NULL) {
        fprintf(stderr, "开辟内存失败！\n");
        exit(EXIT_FAILURE);
    }
    printf("输入文件名称：");
    scanf("%s", operating_file);
    CSV_File *class = open_class(operating_file);
    node_ptr list = read_from_class(class);
    while (1) {
        clean_screen(1, 1);
        printf("操作文件 %s 中\n", operating_file);
        printf("使用对应数字选择目录选项。其他输入没有效果。\n");
        printf("[1] 显示所有学生\n"
               "[2] 新增学生信息\n"
               "[3] 查找学生信息\n"
               "[4] 删除学生信息\n"
               "[5] 修改学生信息\n"
               "[6] 按指定键排序\n"
               "[7] 保存并退出\n");
        int option;
        do {
            printf("请输入 1-7： ");
        } while (scanf("%d", &option) != 1);
        switch (option) {
            case 1:
                clean_screen(1, 1);
                int order;
                printf("选择显示顺序。\n");
                printf("使用对应数字选择目录选项。其他输入没有效果。\n");
                printf("[0] 升序\n"
                       "[1] 降序\n");
                do {
                    printf("请输入 0-1： ");
                } while (scanf("%d", &order) != 1);
                list_students(list, order);
                press_to_exit_function();
                break;
            case 2:
                clean_screen(1, 1);
                printf("新增学生信息。\n");
                input_student(list);
                press_to_exit_function();
                break;
            case 3:
                clean_screen(1, 1);
                printf("查找学生信息。\n");
                int finding;
                printf("选择查找方式。\n");
                printf("使用对应数字选择目录选项。其他输入没有效果。\n");
                printf("[1] 按学号查找\n"
                       "[2] 按名字查找\n");
                do {
                    printf("请输入 1-2： ");
                } while (scanf("%d", &finding) != 1);
                switch (finding) {
                    case 1:
                        find_students_by_number(list);
                        break;
                    case 2:
                        find_students_by_name(list);
                        break;
                    default:
                        printf("输入无效！\n");
                }
                press_to_exit_function();
                break;
            case 4:
                clean_screen(1, 1);
                printf("删除学生信息。\n");
                int deleting;
                printf("选择删除方式。\n");
                printf("使用对应数字选择目录选项。其他输入没有效果。\n");
                printf("[1] 按学号删除\n"
                       "[2] 按名字删除\n");
                do {
                    printf("请输入 1-2： ");
                } while (scanf("%d", &deleting) != 1);
                switch (deleting) {
                    case 1:
                        delete_student_by_number(list);
                        printf("删除操作完成!\n");
                        break;
                    case 2:
                        delete_student_by_name(list);
                        printf("删除操作完成!\n");
                        break;
                    default:
                        printf("输入无效！\n");
                }
                press_to_exit_function();
                break;
            case 5:
                clean_screen(1, 1);
                printf("修改学生信息。\n");
                int updating;
                printf("选择修改方式。\n");
                printf("使用对应数字选择目录选项。其他输入没有效果。\n");
                printf("[1] 按学号修改\n"
                       "[2] 按名字修改\n");
                do {
                    printf("请输入 1-2： ");
                } while (scanf("%d", &updating) != 1);
                switch (updating) {
                    case 1:
                        update_student_by_number(list);
                        printf("修改操作完成!\n");
                        break;
                    case 2:
                        update_student_by_name(list);
                        printf("修改操作完成!\n");
                        break;
                    default:
                        printf("输入无效！\n");
                }
                press_to_exit_function();
                break;
            case 6:
                clean_screen(1, 1);
                printf("按指定键排序。\n");
                int sorting;
                printf("选择排序方式。\n");
                printf("使用对应数字选择目录选项。其他输入没有效果。\n");
                printf("[0] 按学号排序\n"
                       "[1] 按名字排序\n"
                       "[2] 按计算机成绩排序\n"
                       "[3] 按数学成绩排序\n"
                       "[4] 按英语成绩排序\n"
                       "[5] 按总分排序\n"
                       "[6] 按平均分排序\n");
                do {
                    printf("请输入 0-6： ");
                } while (scanf("%d", &sorting) != 1);
                switch (sorting) {
                    case NUMBER_COMPARTOR:
                        sort_students(list, NUMBER_COMPARTOR);
                        printf("排序操作完成!\n");
                        break;
                    case NAME_COMPARTOR:
                        sort_students(list, NAME_COMPARTOR);
                        printf("排序操作完成!\n");
                        break;
                    case COMPUTER_SCORE_COMPARTOR:
                        sort_students(list, COMPUTER_SCORE_COMPARTOR);
                        printf("排序操作完成!\n");
                        break;
                    case MATH_SCORE_COMPARTOR:
                        sort_students(list, MATH_SCORE_COMPARTOR);
                        printf("排序操作完成!\n");
                        break;
                    case ENGLISH_SCORE_COMPARTOR:
                        sort_students(list, ENGLISH_SCORE_COMPARTOR);
                        printf("排序操作完成!\n");
                        break;
                    case SUM_COMPARTOR:
                        sort_students(list, SUM_COMPARTOR);
                        printf("排序操作完成!\n");
                        break;
                    case AVG_COMPARTOR:
                        sort_students(list, AVG_COMPARTOR);
                        printf("排序操作完成!\n");
                        break;
                    default:
                        printf("输入无效！\n");
                }
                press_to_exit_function();
                break;
            case 7:
                clean_screen(1, 1);
                save_class(list, operating_file);
                printf("保存完成!\n");
                press_to_exit_function();
                return;
            default:
                continue;
        }
    }
}

void general_menu() {
    while (1) {
        clean_screen(1, 1);
        printf("欢迎来到学生管理系统 Demo！\n");
        printf("使用对应数字选择目录选项。其他输入没有效果。\n");
        printf("[1] 选择已有的班级进行操作\n"
               "[2] 新建班级进行操作\n"
               "[3] 删除班级\n"
               "[4] 关于本程序\n"
               "[5] 退出程序\n");
        int option;
        do {
            printf("请输入 1-5： ");
        } while (scanf("%d", &option) != 1);
        switch (option) {
            case 1:
                operate_exist_file();
                break;
            case 2:
                operate_new_file();
                break;
            case 3:
                clean_screen(1, 1);
                char *operating_file = calloc(MAX_FILE_STR_LEN, sizeof(char));
                if (operating_file == NULL) {
                    fprintf(stderr, "开辟内存失败！\n");
                    exit(EXIT_FAILURE);
                }
                printf("输入文件名称：");
                scanf("%s", operating_file);
                delete_class(operating_file);
                printf("删除操作完成\n");
                press_to_exit_function();
                break;
            case 4:
                print_about();
                break;
            case 5:
                return;
            default:
                continue;
        }
    }
}
