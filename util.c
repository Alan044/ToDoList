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
  
char* ask_date() 
{
    char buf[256];
    while (true) {
    printf("When is the task due? \n");
    printf("Please write the following date on this format xxxx-xx-xx \n");
    scanf("%255s", buf);
    char* error = "Invalid date";
    for (int i = 0; i < 10; i++ ) {


        if (!(valid_year(buf, error))) {
            printf("%s \n", error);
            break;
        }
        if(!(valid_length_and_char(buf, error))) {
            break;
        }
        
            if(isdigit(buf[i])) {
                return strdup(buf);
            } else {
            printf("%s \n", error);
            break;
            }
        }
    }    
}

char* ask_task()
{
    char buf[100];
    printf("What should the new name be: ?\n");
    scanf(" %99s", buf);
    return strdup(buf);
}


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

    new_task->name = name;
    new_task->date = date;
    new_task->info = info_i;
    new_task->info->index = arr->size;
    int total_days = calculate_days(new_task);
    new_task->info->days_left = total_days;

    arr->array_of_tasks[arr->size] = new_task;
    arr->size += 1;
    return new_task;
}

task_t* create_task_info(tasks* arr) 
{
    char* task = ask_task();
    char* date = ask_date();
    return create_task(task, date, arr);
}

void print_tasks(tasks* arr) 
{
    for (int i = 0; i < arr->size; i++) 
    {
        task_t* task = arr->array_of_tasks[i];
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

option_t valid_name(tasks* arr, char *name_to_remove)
{
    for (int i = 0; i < arr->size; i++) 
    {
        if (strcmp(arr->array_of_tasks[i]->name,name_to_remove) == 0) {
            option_t option = {.valid = true, .index = i};
            return option;
        }
    
    }
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
void edit_task(tasks* arr, char* name_to_edit)
{
    option_t result = valid_name(arr, name_to_edit);
    if (result.valid)
    {
        char* name = ask_task();
        char* date = ask_date();

        task_t *task = arr->array_of_tasks[result.index];
        char* free_name = arr->array_of_tasks[result.index]->name;
        char* free_date = arr->array_of_tasks[result.index]->date;
        task->date = date;
        task->name = name;
        free(free_date); 
        free(free_name); 
        return;
    }
    printf("Could not find the name ");
}

int calculate_days(task_t* task)
{
    time_t now = time(NULL);
    struct tm *current = localtime(&now);
    
    date_t date = task_date(task->date);
    struct tm *task_date = localtime(&now);

    int year_int = atoi(date.year);
    int month_int = atoi(date.month) -1;
    if (date.day[0] == '0') {
        int day_int = atoi(&date.day[1]);
        task_date->tm_mday = day_int; 
    } else {
        int day_int = atoi(date.day);    
        task_date->tm_mday = day_int; 
    }
    task_date->tm_year = year_int -1900; 
    task_date->tm_mon = month_int; 

    int seconds = difftime(mktime(task_date) ,  now);
    int days = seconds / (60* 60 * 24);
    free(date.year);
    free(date.month);
    free(date.day);   
    return days;
}
