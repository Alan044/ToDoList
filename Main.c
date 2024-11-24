#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct task task_t;
typedef struct arr_task tasks;

struct task{
    char* name;
    char* date;
};

struct arr_task {
    task_t** array_of_tasks;
    int index;
};

tasks* create_array()
{
    tasks* arr = calloc(1, sizeof(task_t*));
    arr->array_of_tasks = calloc(arr->index, sizeof(task_t*));
    arr->index = 0;
    return arr;
} 

task_t* create_task(char* name, char* date, tasks* arr)
{
    task_t *new_task = calloc(1,sizeof(task_t));

    new_task->name = strdup(name);
    new_task->date = strdup(date);

    return new_task;
}

task_t* create_task_info(tasks* arr)
{
    char buf[100];
    char date[100];

    printf("what is the name of the task? \n");
    scanf("%99s", buf);

    printf("When is the task due ?  \n ");
    scanf("%99s", date);
    
    task_t* task = create_task(buf,date, arr);

    return task;
}



void print_tasks(char* name, char* date)
{
    printf("First task is %s, and the date for it is %s \n", name, date);
    return;

}


int main(void) 
{
    tasks* arr = create_array();
    task_t* task = create_task_info(arr);
    print_tasks(task->name, task->date);

    free(task->date);
    free(task->name);
    free(task);
    return 0;
}