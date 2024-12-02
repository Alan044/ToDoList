#pragma once
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

typedef struct task task_t;
typedef struct arr_task tasks;
typedef struct info info_t;
typedef struct option option_t;
typedef struct input input_t;

struct input
{
    bool valid;
    char* input;
};
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
task_t* create_task_info(tasks* arr);

void print_tasks(tasks* arr);

void remove_task(tasks* arr, char* name_to_remove);

void edit_task(tasks* arr, char* name_to_edit);

void destroy(tasks* arr);

tasks* create_array(); 

char* ask_date();

char* ask_task();

input_t valid_input(char* input);