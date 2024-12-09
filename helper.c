
#include <stdlib.h>
#include "util.h"
#include <string.h>
#include <time.h>


date_t task_date(char* task)
{
    char* year = calloc(1,5*sizeof(char));
    memcpy(year, task, 4);
    year[4] = '\0';

    char* month = calloc(1,3*sizeof(char));
    strncpy(month, task + 5, 2);
    month[2] = '\0';
    

    char* day = calloc(1,3*sizeof(char));
    strncpy(day, task + 8, 2);
    day[2] = '\0';

    date_t date = {.year = year, .month = month, .day = day};
    return date;
}

bool valid_length_and_char(char* buf, char* error)
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

bool valid_year(char* buf, char* error)
{
    time_t now = time(NULL);
    struct tm *current = localtime(&now);

    int current_year = current->tm_year;
    int current_month = current->tm_mon;
    int current_day = current->tm_mday;

    date_t date = task_date(buf);
    int task_year = atoi(date.year) - 1900;
    int task_month = atoi(date.month) - 1;
    int task_day = atoi(date.day);
    if (task_year < current_year) {

        printf("%s", error);
        free(date.year);
        free(date.month);
        free(date.day);   
        
        return false;
    } else if (task_year == current_year) 
    {
            if (task_month == current_month) 
            {
                if (task_day > current_day)
                {
                    free(date.year);
                    free(date.month);
                    free(date.day);   
                    return true;
                }
            printf("%s", error);          
            free(date.year);
            free(date.month);
            free(date.day);   
            return false;
            }
        printf("%s", error);       
        free(date.year);
        free(date.month);
        free(date.day);   
        return false;
    }
    free(date.year);
    free(date.month);
    free(date.day);   
    return true;
}

char* ask_date() 
{
    char buf[256];
    while (true) {
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


void resize_array(tasks* arr) 
{
    if (arr->size >= arr->capacity) 
    {
        task_t** new_array = realloc(arr->array_of_tasks, arr->capacity * 2 * sizeof(task_t*));
        if (!new_array) 
        {
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

int calculate_days(task_t* task)
{
    time_t now = time(NULL);
    
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