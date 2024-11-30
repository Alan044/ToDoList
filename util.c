#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include "util.h"
#include <stdlib.h>


static bool valid_month(char* buf, char* error)
{

    if ((buf[5] != '1' && buf[5] != '0')) {
        printf("%s \n", error);
        return false;
    }
    if (buf[5] == '1') {
        if(buf[6] == '0'||  buf[6] == '2'|| buf[6] == '1') {
            return true;
        }
        printf("%s \n", error);
        return false;
    }
    if (buf[5] == '0') {
        if(buf[6] != '0') {
            return true;
        }
        printf("%s \n", error);
        return false;
    }
    return true;
}

static bool valid_days(char* buf, char* error)
{
    if ((buf[8] != '2' && buf[8] != '0' && buf[8] != '3' && buf[8] != '1')) {
        printf("%s \n", error);
        return false;
    }
    if (buf[8] == '3') {
        if (buf[9] == '1' || buf[9] == '0' ) {
            return true;
        }
        printf("%s \n", error);
        return false;
    }
    if (buf[8] == '0') {
        if(buf[9] != '0') {
            return true;
        }
        printf("%s \n", error);
        return false;
    }
    return true;
}

static bool valid_length_and_char(char* buf, char* error)
{
    if(strlen(buf) > 10 || strlen(buf) < 10)
    {
        printf("%s \n", error);
        return false;
    }        
    if ((buf[4] != '-' || buf[7] != '-'))
    {
        printf("%s \n", error);
        return false;
    }
    return true;
}

char* ask_date() 
{
    char buf[256];
    while (true) {
    printf("When is the task due? \n");
    printf("Please write the following date on this format xxxx-xx-xx \n");
    scanf("%255s", buf);
    char* error = "Invalid date";
    for (int i = 0; i < 10; i++ ) {
        
        if (!(buf[0] == '2')) {
            printf("%s \n", error);
            printf("test1");
            break;
        }
        if(!(valid_length_and_char(buf, error))) {
            printf("test2");
            break;
        }
        if(!(valid_month(buf, error))) {
            printf("test3");
            break;
        }
        if(!(valid_days(buf, error))) {
            printf("test4");
            break;
        }
        
            if(isdigit(buf[i])) {
                return strdup(buf);
            } else {
            printf("te3");
            printf("%s \n", error);
            break;
            }
        }
    }    
}

typedef struct task task_t;
typedef struct arr_task tasks;
typedef struct info info_t;
typedef struct option option_t;

struct info 
{
    int index;
    int days_left;
    char* category;
};

struct task 
{
    char* name;
    char* date;
    info_t* info;
};

struct arr_task 
{
    task_t** array_of_tasks;
    int size;
    int capacity;  
};

struct option
{
    bool valid;
    int index;
};

tasks* create_array() 
{
    tasks* arr = calloc(1, sizeof(tasks));
    arr->capacity = 2;  
    arr->array_of_tasks = calloc(arr->capacity, sizeof(task_t*));
    arr->size = 0;
    return arr;
}

void resize_array(tasks* arr) {
    if (arr->size >= arr->capacity) {
        task_t** new_array = realloc(arr->array_of_tasks, arr->capacity * 2 * sizeof(task_t*));
        if (!new_array) {
            perror("Failed to resize array");
            exit(EXIT_FAILURE);
        }
        arr->array_of_tasks = new_array;
        arr->capacity *= 2;
    }
}

task_t* create_task(char* name, char* date, tasks* arr) 
{
    resize_array(arr);  

    task_t* new_task = calloc(1, sizeof(task_t));
    info_t* info_i = calloc(1, sizeof(info_t));

    new_task->name = strdup(name);
    new_task->date = date;
    new_task->info = info_i;
    new_task->info->index = arr->size;

    arr->array_of_tasks[arr->size] = new_task;
    arr->size += 1;
    return new_task;
}

task_t* create_task_info(tasks* arr) 
{
    char buf[100];

    printf("What is the name of the task? \n");
    scanf(" %99s", buf);

    char* date = ask_date();
    return create_task(buf, date, arr);
}

void print_tasks(tasks* arr) 
{
    for (int i = 0; i < arr->size; i++) 
    {
        task_t* task = arr->array_of_tasks[i];
        printf("Task: %s, Due Date: %s\n", task->name, task->date);
    }
}


void destroy(tasks* arr) {
    for (int i = 0; i < arr->size; i++) {
        task_t* task = arr->array_of_tasks[i];
        free(task->name);
        free(task->date);
        free(task->info); 
        free(task);
    }
    free(arr->array_of_tasks);
    free(arr);
}

option_t valid_name(tasks* arr, char *name_to_remove)
{
    for (int i = 0; i < arr->size; i++) 
    {
        if (strcmp(arr->array_of_tasks[i]->name,name_to_remove) == 0) {
            option_t option = {.valid = true, .index = i};
            printf("test2");
            return option;
        }
    
    }
    printf("test\n");
    option_t option = {.valid = false, .index = arr->capacity + 1};
    return option;
}


void remove_task(tasks*arr, char*name_to_remove)
{
    //check if name exists
    option_t result = valid_name(arr, name_to_remove);

    if(result.valid)
    {
        int index = result.index;
        task_t* task = arr->array_of_tasks[index];
        free(task->name);
        free(task->date);
        free(task->info);
        free(task);

        for (int i = index; i < arr->size - 1; i++) {
            arr->array_of_tasks[i] = arr->array_of_tasks[i + 1];
        }
    
        arr->size --;
        printf("removed the task you specified and here is the new list \n");
        print_tasks(arr);
        return;
    }
    printf("Could not find that task, here is the list again \n");
    print_tasks(arr);
}