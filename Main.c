#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
typedef struct task task_t;
typedef struct arr_task tasks;
typedef struct info info_t;

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

tasks* create_array() 
{
    tasks* arr = calloc(1, sizeof(tasks));
    arr->capacity = 2;  
    arr->array_of_tasks = calloc(arr->capacity, sizeof(task_t*));
    arr->size = 0;
    return arr;
}

char* ask_date() 
{
    char buf[256];
    printf("When is the task due? \n");
    printf("Please write the following date on this format xxxx-xx-xx \n");
    scanf("%255s", buf);
    char* error = "Invalid date";
    
    if(strlen(buf) > 10 || strlen(buf) < 10)
    {
        printf("test1");
        return error;
    }

    for (int i = 0; i < 11; i++) 
    {
        if (!(buf[4] == '-' && buf[7] == '-')) {
            return error;
        }

        if(isdigit(buf[i])) {
            return strdup(buf);
        } else {
            printf("test3");
            return error;
        }
    }
}

void resize_array(tasks* arr) 
{
    if (arr->size >= arr->capacity) {
        arr->capacity *= 2;
        arr->array_of_tasks = realloc(arr->array_of_tasks, arr->capacity * sizeof(task_t*));
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

int main(void) {
    tasks* arr = create_array();

    while (true) {
        printf("What is your choice of the day? (A: Add, L: List, Q: Quit)\n");

        char answer;
        scanf(" %c", &answer);

        if (answer == 'A') {
            create_task_info(arr);
        } else if (answer == 'L') {
            print_tasks(arr);
        } else if (answer == 'Q') {
            destroy(arr);
            break;
        } else {
            printf("Invalid choice! Please enter A, L, or Q.\n");
        }
    }

    return 0;
}
