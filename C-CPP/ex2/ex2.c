/**
 * Source file that contains all functions implementation.
 * @author: ElinorB
 */
#include "ex2.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_LINE_LENGTH 1026
#define DELIMITERS ","

int get_data_size (char buffer[MAX_LINE_LENGTH]);
LinkedList *new_linked_list();
Node *new_node();
void arr_copy (char *dest, const char *src, int n);
unsigned int check_nodes_num (LinkedList *p_list);
double calc_average (Node *p_node);
FILE *open_file_helper (const char *filename);
/**
 * Adds a node as the head of the list.
 *
 * Assumptions:
 *    You cannot assume the pointers are valid.
 *
 * In case of errors:
 *    Invalid pointer - print error to stderr and return from function.
 *
 * @param list pointer to list to add a node to.
 * @param node pointer to the node to add to the list.
 */
void add_to_start_linked_list(LinkedList *const list, Node *const node)
{
    if (list == NULL)
    {
      fprintf( stderr, "ERROR:linked list pointer is non-valid(add_to_start_linked_list) \n");
      return;
    }
    if(node == NULL)
      {
        fprintf (stderr, "ERROR:node pointer is non-valid(add_to_start_linked_list)  \n");
        return;
      }
    if((list->tail == NULL)&&(list->head == NULL)){
        list->tail = node;
        list->head = node;
        return;
    }
    Node *temp = list->head;
    list->head = node;
    temp->prev = node;
    node->next = temp;
}
/**
 * Adds a node as the tail of the list.
 *
 * Assumptions:
 *   You cannot assume the pointers are valid.
 *
 * In case of errors:
 *    Invalid pointer - print error to stderr and return from function.
 *
 * @param list pointer to list to add a node to.
 * @param node pointer to the node to add to the list.
 */
void add_to_end_linked_list(LinkedList *const list, Node *const node)
{
    if (list == NULL)
        {
            fprintf( stderr, "ERROR:linked list pointer is non-valid(add_to_end_linked_list())\n");
            return;
        }
    if(node == NULL)
        {
            fprintf (stderr, "ERROR:node pointer is non-valid(add_to_end_linked_list()) \n");
            return;
        }
    if((list->tail == NULL)&&(list->head == NULL)){
            list->tail = node;
            list->head = node;
            return;
        }
    Node *temp = list->tail;
    list->tail = node;
    temp->next = node;
    node->prev = temp;
}
/**
 * removes a node from the list and frees it's resources.
 *
 * Assumptions:
 *    You cannot assume the pointers are valid.
 *    You cannot assume the node is in the list. In this case don't free its resources.
 *    To be sure - you are supposed to compare the given node
 *    to the nodes in the list using == operator.
 *
 * In case of errors:
 *    Invalid pointer - print informative error message to stderr and return from function.
 *
 * @param list pointer to list to remove a node from.
 * @param node pointer to the node to remove from the list.
 */
void remove_node(LinkedList *const list, Node *const node)
{
    if (list == NULL)
        {
            fprintf( stderr, "ERROR:linked list pointer is non-valid(remove_node()) \n");
            return;
        }
    if(node == NULL)
        {
            fprintf (stderr, "ERROR: node pointer is non-valid(remove_node())) \n");
            return;
        }
    Node *cur_node = list->head;
    while(cur_node != NULL)
    {
        Node *temp_node;
        Node *temp_node2;
        if(list->head == node){
            if(list->tail == node){
                list->head = NULL;
                list->tail = NULL;
                free (node);
                return;
            }
            temp_node = cur_node->next;
            temp_node->prev = NULL;
            list->head = temp_node;
            free(node);
            return;
        }
        else if(list->tail == node){
            temp_node = list->tail;
            temp_node2 = temp_node->prev;
            temp_node2->next = NULL;
            list->tail = temp_node2;
            free(node);
            return;
        }
        if(cur_node == node){
            temp_node = cur_node->prev;
            temp_node2 = cur_node->next;
            temp_node->next = temp_node2;
            temp_node2->prev = temp_node;
            free (node);
            return;
        }
        temp_node = cur_node->next;
        cur_node = temp_node;

    }
}
/**
 * Frees the resources (all dynamic allocations) of the given list.
 *
 * Assumptions:
 *    You cannot assume the pointer is valid.
 *
 * In case of errors:
 *    Invalid pointer - This means there is nothing to free, just return from function.
 *
 * @param list the list to free.
 */
void free_linked_list(LinkedList *const list)
{
    if(list == NULL){
            return;
    }
    Node *cur_node = list->head;
    Node *temp_node;
    while(cur_node != NULL)
        {
            if(cur_node->data != NULL)
            {
                free(cur_node->data);
            }
            temp_node = cur_node->next;
            if(temp_node != NULL)
            {
                temp_node->prev = NULL;
            }
            free (cur_node);
            cur_node = temp_node;
        }
    list->head = NULL;
    list->tail = NULL;
    free(list);
}
/**
 * calculates the grade average of every node in the linked list.
 *
 * Assumptions:
 *    You cannot assume the pointers are valid.
 *    You don't know the number of nodes in the linkedlist in advance.
 *    You can assume that there is at least one node with data != NULL (i.e. len > 0).
 *    You can assume that for each node 'len' is indeed the length of 'data'
 *     (in particular len=0 <=> data=NULL).
 *
 * In case of errors:
 *    Invalid pointer - print informative message to stderr, free resources allocated by function,
 *                      return NULL from function.
 *    Allocation fail - print informative message to stderr, free resources allocated by function,
 *                      return NULL from function.
 *    Node with NULL data - don't count the node in the calculation.
 *
 * @param list: LinkedList pointer to linked list from whom to calculate grade averages.
 * @param num_elements_in_returned_array: pointer to unsigned long, that should contain
 * the number of nodes in the list
 * (for nodes with data != NULL) when the function finishes execution.
 * To be clear - at the start of the function,
 * (*num_elements_in_returned_array) is a garbage value, and this function should set its value.
 *    @Note: Nodes with NULL data should not be count in the calculation.
 *    Therefore *num_elements_in_returned_array <= numOfNodes.
 * @return array of grade averages per node. To be clear - this means you should
 * calculate the grade average of every node and save it into an array,
 * which you will return from the function.
 */
double *get_averages(LinkedList *const list, size_t *const num_elements_in_returned_array)
{
    if(list == NULL)
    {
            fprintf (stderr, "ERROR:non-valid linked list pointer (get_averages())\n");
            return NULL;
    }
    if(num_elements_in_returned_array == NULL){
            fprintf (stderr, "ERROR:non-valid size_t pointer (get_averages())\n");
            return NULL;
    }
    unsigned int size_of_array = check_nodes_num(list);
    *num_elements_in_returned_array = size_of_array;
    double *averages_array = (double *)malloc (size_of_array);
    if(averages_array == NULL)
    {
            fprintf (stderr, "ERROR:unable to allocate memory (get_averages())\n");
            return NULL;
    }
    unsigned int counter = 0;
    Node *cur_node = list->head;
    while((cur_node != NULL) && (counter < size_of_array)){
        if(cur_node->len > 0){
            double average = calc_average(cur_node);
            averages_array[counter] = average;
            counter++;
        }
        Node *temp = cur_node->next;
        cur_node = temp;
    }
    return averages_array;
}
/**
 * Helper method that receives a pointer to a node and returns the average
 * of all its data numbers.
 *
 * @param p_node the node to return its average
 * @return A double that contains the average of all the node's numbers
 */
double calc_average (Node *p_node)
{
    unsigned int i = 0;
    double average = 0;
    while(i < (p_node->len)){
        average += p_node->data[i];
        i++;
    }
    average = average/(i);
    return average;
}
/**
 * Helper method that receives a pointer to linked list
 * and returns the number of nodes in it that contain at least 1
 * number in its data field.
 *
 * @param p_list The pointer to the linked list to be checked.
 * @return unsigned integer that contains the number of requested nodes
 * in the list.
 */
unsigned int check_nodes_num (LinkedList *p_list)
{
    unsigned int counter = 0;
    Node *cur_node = p_list->head;
    while(cur_node != NULL){
        if(cur_node->len > 0){
            counter++;
        }
        Node *temp = cur_node->next;
        cur_node = temp;
    }
    return counter;
}
/**
 * opens a file from a given filename and parses it's contents into a LinkedList.
 *
 * Assumptions:
 *    You cannot assume the filename is OK (meaning - you cannot assume it is a valid path to a file).
 *    You cannot assume anything on the number of ints in a row of the file, just that it is >= 1.
 *    You can assume that if the file opened, then it is exactly in the
 *    format specified in the exercise PDF.
 *    You can assume max line length of 1024.
 *
 * In case of errors:
 *    Invalid pointer - print informative message to stderr, free resources allocated by function,
 *                      return NULL from function.
 *    File open fail - print informative message to stderr, free resources allocated by function,
 *                      return NULL from function.
 *    Allocation fail - print informative message to stderr, free resources allocated by function,
 *                      return NULL from function.
 *
 * Think - in what mode should we open this file? (read? write? append?)
 *
 * @param file filename of input file that needs to be parsed.
 * @return pointer to LinkedList instance, whose nodes and data
 * arrays were parsed from the given file.
 */
LinkedList *parse_linked_list(const char *const filename)
{
    FILE *in_file = open_file_helper(filename);
    if(in_file == NULL){return NULL;}

    LinkedList *linked_list = new_linked_list();
    if(linked_list == NULL)
    {
        fprintf (stderr, "ERROR: failed to dynamically allocate new linked list\n");
        return NULL;
    }
    char buffer[MAX_LINE_LENGTH] = {0};
    char *token = NULL;
    while(fgets (buffer,MAX_LINE_LENGTH,in_file) != NULL)
    {
        const int base = 10;
        Node *cur_node = new_node();
        if(cur_node == NULL)
        {
            fprintf (stderr, "ERROR: failed to dynamically allocate new node\n");
            free_linked_list (linked_list);
            return NULL;
        }
        char buffer_temp[MAX_LINE_LENGTH] = {0};
        arr_copy(buffer_temp, buffer, MAX_LINE_LENGTH);
        unsigned int data_size = get_data_size(buffer_temp);
        token = strtok(buffer, DELIMITERS);
        if(*token == 's')
        {
            add_to_start_linked_list (linked_list, cur_node);
        }
        else if(*token == 'e')
        {
            add_to_end_linked_list (linked_list, cur_node);
        }
        int *temp;
        if(data_size == 0){
                continue;
        }
        temp = (int*)realloc (cur_node->data, data_size*sizeof(int));
        if (temp == NULL)
            {
                free_linked_list (linked_list);
                return NULL;
            }
        cur_node->data = temp;
        cur_node->len = data_size;
        int counter = 0;
        while ((token = strtok(NULL, DELIMITERS)))
            {
                if((*token == '\n')||(strcmp (token, "\r\n")==0))
                    {
                        break;
                    }
                cur_node->data[counter] = (int)strtol(token, NULL, base);
                counter++;
            }
    }
    fclose (in_file);
    return linked_list;
}
/**
 * Helper method for file opening
 *
 * @param filename pointer to file name
 * @return pointer to opened file, NULL if failed
 */
FILE *open_file_helper (const char *const filename)
{
    if(filename == NULL)
        {
            fprintf(stderr, "ERROR: non-valid file name pointer");
            return NULL;
        }
    FILE *in_file = fopen(filename, "r");

    if(in_file == NULL)
        {
            fprintf (stderr, "ERROR: failed to open the given file\n");
            return NULL;
        }
    return in_file;
}
/**
 * Helper method that receives a pointer to destination char array,
 * and pointer to source char array ant their size "n",
 * and copies one array into the other.
 *
 * @param dest destination array to be copied to
 * @param src source array to be copied from
 * @param n their size
 */
void arr_copy (char *dest, const char *src, const int n)
{
    for(int i = 0; i<n; i++){
        dest[i] = src[i];
    }
}
/**
 * Dynamically allocate a new linked list.
 *
 * @return new linked list, might be NULL pointer if allocation didnt succeed.
 */
LinkedList *new_linked_list()
{
    LinkedList *linked_list = malloc (sizeof (LinkedList));
    if (linked_list != NULL)
        {
            linked_list->head = NULL;
            linked_list->tail = NULL;
        }
    return linked_list;
}
/**
 * Dynamically allocate a new Node.
 *
 * @return new Node, might be NULL pointer if allocation didnt succeed.
 */
Node *new_node()
{
    Node *cur_node = malloc (sizeof (Node));
    if (cur_node != NULL)
        {
            cur_node->next = NULL;
            cur_node->prev = NULL;
            cur_node->data = NULL;
            cur_node->len = 0;
        }
    return cur_node;
}

/***
 * Helper method that determines the data size of a node.
 *
 * @param buffer contains the line that holds the node data
 * @return zero if failed positive integer that represents the node data
 * size otherwise
 */
int get_data_size (char buffer[MAX_LINE_LENGTH])
{
    char *token;
    int counter = 0;
    token = strtok(buffer, DELIMITERS);
    while ((token = strtok(NULL, DELIMITERS))){
        if((*token == '\n')||(strcmp (token, "\r\n")==0))
        {
            break;
        }
        counter++;
    }
    return counter;
}

