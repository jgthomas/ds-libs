#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doubly_linked_list.h"


Node *create_node(void *new_data)
{
        Node *new_node = malloc(sizeof(*new_node));

        if (new_node == NULL)
        {
            fprintf(stderr, "Failed to allocate memory for node\n");
            exit(EXIT_FAILURE);
        }
 
        new_node->data = new_data;

        return new_node;
}


void list_push(Node **head, void *new_data, size_t data_size)
{
        Node *new_node = create_node(new_data);

        new_node->next = (*head);
        new_node->previous = NULL;

        if ((*head) != NULL)
        {
                (*head)->previous = new_node;
        }
 
        (*head) = new_node;
}


void append(Node **node, void *new_data, size_t data_size)
{
        // create new node, set next to NULL as last
        Node *new_node = create_node(new_data);;
        new_node->next = NULL;
        new_node->previous = NULL;

        if ((*node) == NULL)
        {
                (*node) = new_node;
                return;
        }

        // set up cursor
        Node *node_ptr = (*node);

        // advance to end of list
        while (node_ptr->next != NULL)
        {
                node_ptr = node_ptr->next;
        }

        // set previous to current end node
        new_node->previous = node_ptr;

        // if end node exists, point next to new node
        if (node_ptr != NULL)
        {
                node_ptr->next = new_node;
        }
}


void print_from_head(Node *node, void (*print)(void *x))
{
        while (node != NULL)
        {
                print(node->data);
                printf(" ");
                node = node->next;
        }

        printf("\n");
}


void print_from_tail(Node *node, void (*print)(void *x))
{
        while (node->next != NULL)
        {
                node = node->next;
        }

        while (node != NULL)
        {
                print(node->data);
                printf(" ");
                node = node->previous;
        }

        printf("\n");
}


void delete_list(Node *node)
{
        while (node != NULL)
        {
                Node *temp = node;
                node = node->next;
                free(temp);
        }
}


void dl_list_reverse(Node **head)
{
        Node *temp = NULL;

        while ((*head) != NULL)
        {
                // store previous in temporary variable
                temp = (*head)->previous;

                // swap previous for next
                (*head)->previous = (*head)->next;

                // point next to the stored, old previous
                (*head)->next = temp;

                // as we swapped next and previous,
                // previous moves us to next in list
                (*head) = (*head)->previous;
        }
    
        if (temp != NULL)
        {
                (*head) = temp->previous;
        }
}


void dl_list_delete_value(Node **node,
                          void *val,
                          bool (*equal)(void *x, void *y))
{
        Node *original_head = (*node);
        Node *before = NULL;
        bool first_elem_deleted = true;

        while ((*node) != NULL)
        {
                if (equal(val, (*node)->data))
                {
                        Node *temp = (*node);

                        if (first_elem_deleted)
                        {
                                (*node) = (*node)->next;
                                (*node)->previous = NULL;
                        }
                        else
                        {
                                before->next = (*node)->next;

                                if ((*node)->next != NULL)
                                {
                                        (*node)->next->previous = before;
                                }
                        }

                        delete_node(temp);
                        break;
                }

                before = (*node);
                (*node) = (*node)->next;
                first_elem_deleted = false;
        }

        if (!first_elem_deleted)
        {
                (*node) = original_head;
        }
}


/**
 * Search and move the found node to the front of the list
 *
 * */
bool list_find_and_move(Node **node,
                        void *search,
                        bool (*equal)(void *, void *))
{
        // if item is already in first position, do nothing
        if (equal(search, (*node)->data))
        {
                return true;
        }

        Node *original_head = (*node);

        while ((*node) != NULL)
        {
                (*node) = (*node)->next;

                if (equal(search, (*node)->data))
                {
                        if ((*node)->next != NULL)
                        {
                                (*node)->previous->next = (*node)->next;
                                (*node)->next->previous = (*node)->previous;
                        }
                        else
                        {
                                (*node)->previous->next = NULL;
                        }

                        (*node)->next = original_head;
                        original_head->previous = (*node);

                        (*node)->previous = NULL;

                        return true;
                }
        }

        // if not found, restore list to initial state
        (*node) = original_head;
        return false;
}
