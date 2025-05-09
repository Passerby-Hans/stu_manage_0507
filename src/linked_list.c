//
// Created by Hans on 25-4-8.
//

#include "linked_list.h"

node_ptr init_list()
{
    node_ptr head = (node_ptr)calloc(1, sizeof(node));
    head->next = head;
    head->prev = head;
    return head;
}

void add_head(node_ptr head, void *data)
{
    node_ptr new_node = (node_ptr)calloc(1, sizeof(node));
    new_node->data = data;

    new_node->prev = head;
    new_node->next = head->next;
    head->next->prev = new_node;
    head->next = new_node;
}

void add_tail(node_ptr head, void *data)
{
    node_ptr new_node = (node_ptr)calloc(1, sizeof(node));
    new_node->data = data;

    new_node->next = head;
    new_node->prev = head->prev;
    head->prev->next = new_node;
    head->prev = new_node;
}
void traversal_list(node_ptr head, int order, visit_func visit)
{
    if (order == FORWARD_TRAVERSAL)
    {
        for (node_ptr p = head->next; p != head; p = p->next)
        {
            visit(p->data);
        }
    }
    else if (order == BACKWARD_TRAVERSAL)
    {
        for (node_ptr p = head->prev; p != head; p = p->prev)
        {
            visit(p->data);
        }
    }
}
node_ptr get_item(node_ptr head, void *info, compartor_func compare)
{
    for (node_ptr p = head->next; p != head; p = p->next)
    {
        if (compare(p->data, info) == 0)
        {
            return p;
        }
    }
    return NULL;
}
void delete_item(node_ptr head, void *info, compartor_func compare)
{
    node_ptr current = head->next;
    while (current != head)
    {
        if (compare(current->data, info) == 0)
        {
            node_ptr temp = current;
            current->prev->next = current->next;
            current->next->prev = current->prev;
            current = current->next;
            free(temp->data);
            free(temp);
        }
        else
        {
            current = current->next;
        }
    }
}
void update_item(node_ptr head, void *info, compartor_func compare, void *new_data)
{
    // 更新一个
    for (node_ptr p = head->next; p != head; p = p->next)
    {
        if (compare(p->data, info) == 0)
        {
            p->data = new_data;
            return;
        }
    }
}
int get_length(node_ptr head)
{
    int length = 0;
    for (node_ptr p = head->next; p != head; p = p->next)
    {
        length++;
    }
    return length;
}
void bubble_sort(node_ptr head, compartor_func compare)
{
    int length = get_length(head);
    if (length == 0) return;
    for (int i = 0; i < (length - 1); i++)
    {
        for (node_ptr p = head->next; p != head->prev; p = p->next)
        {
            if (compare(p->data, p->next->data) > 0)
            {
                void* temp = p->data;
                p->data = p->next->data;
                p->next->data = temp;
            }
        }
    }
}

void* free_list(node_ptr head)
{
    node_ptr current = head->next;
    while (current != head)
    {
        node_ptr temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
    free(head);
    return NULL;
}