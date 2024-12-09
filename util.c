#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <time.h>
#include "util.h"
#include "helper.h"
#include <stdlib.h>

input_t valid_input(char* input)
{
    if (strlen(input) > 1) {
        input_t input = { .input = "p", .valid = false};
        return input;    
    }
    char* valid_answers[] = {"A", "L", "R", "E", "Q"};
    for (int i = 0; i < 5; i++) {
        if (strcmp(input, valid_answers[i])) {
            input_t input2 = { .valid = true, .input = input};
            return input2;
        } 
    }
    input_t input2 = { .input = "p", .valid = false};
    return input2;
}

tasks* create_array() 
{
    tasks* arr = calloc(1, sizeof(tasks));
    arr->capacity = 2;  
    arr->array_of_tasks = calloc(arr->capacity, sizeof(task_t*));
    arr->size = 0;
    return arr;
}

task_t* create_task_info(tasks* arr) 
{
    printf("What should the name of the task be: ?\n");
    char* task = ask_task();

    printf("When is task due: ?\n");
    char* date = ask_date();
    return create_task(task, date, arr);
}

void print_tasks(task_t** arr, int size) 
{
    for (int i = 0; i < size; i++) 
    {
        task_t* task = arr[i];
        printf("Task: %s, Due Date: %s, Total amount of days left %d\n", task->name, 
                                                                         task->date,
                                                                         task->info->days_left);
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
char* ask_task()
{
    char buf[100];
    scanf(" %99s", buf);
    return strdup(buf);
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
        print_tasks(arr->array_of_tasks, arr->size);
        return;
    }
    printf("Could not find that task, here is the list again \n");
    print_tasks(arr->array_of_tasks, arr->size);
}
void edit_task(tasks* arr, char* name_to_edit)
{
    option_t result = valid_name(arr, name_to_edit);
    if (result.valid)
    {
        printf("What should the new name of the task be: ?\n");

        char* name = ask_task();
        printf("What should the new date of the task be: ?\n");
        char* date = ask_date();

        task_t *task = arr->array_of_tasks[result.index];
        char* free_name = arr->array_of_tasks[result.index]->name;
        char* free_date = arr->array_of_tasks[result.index]->date;
        task->date = date;
        task->name = name;
        int days = calculate_days(task);
        task->info->days_left = days;
        free(free_date); 
        free(free_name); 
        return;
    }
    printf("Could not find the name ");
}



task_t** sort_array(tasks* arr)
{

    for (int i = 0; i < arr->size - 1; i++) 
    {
        task_t* task = arr->array_of_tasks[i];
        if (arr->array_of_tasks[i + 1] == NULL)
        {
            return arr->array_of_tasks;
        }
        
        if (task->info->days_left > arr->array_of_tasks[i + 1]->info->days_left) 
        {
            task_t* task2 = arr->array_of_tasks[i + 1];
            arr->array_of_tasks[i + 1] = task;
            arr->array_of_tasks[i] = task2;

        }
    }
    return arr->array_of_tasks;
}


void print_ascending(tasks* arr)
{
    task_t** array_of_task = sort_array(arr);
    print_tasks(array_of_task,  arr->size);
}
