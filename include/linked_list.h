//
// Created by hules on 25-3-26.
//

// 旨在实现一个类似linux风格的双向循环链表

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>

#define FORWARD_TRAVERSAL 0
#define BACKWARD_TRAVERSAL 1

typedef struct list_node {
    void *data;
    struct list_node *next, *prev;
} node;
typedef struct list_node *node_ptr;

typedef int (*compartor_func)(void *a, void *b);
typedef void (*visit_func)(void* data);

// info 包含目标数据的（部分）特征
node_ptr init_list();
void add_head(node_ptr head, void *data);
void add_tail(node_ptr head, void *data);
void traversal_list(node_ptr head, int order, visit_func visit);
node_ptr get_item(node_ptr head, void *info, compartor_func compare);
void delete_item(node_ptr head, void *info, compartor_func compare);
void update_item(node_ptr head, void *info, compartor_func compare, void *new_data);
int get_length(node_ptr head);
void bubble_sort(node_ptr head, compartor_func compare);
void* free_list(node_ptr head);



#endif //LINKED_LIST_H