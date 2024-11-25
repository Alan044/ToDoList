#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct task task_t;
typedef struct arr_task tasks;

struct task{
    char* name;
    char* date;
    int index;
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
    new_task->index = arr->index;

    arr->array_of_tasks[arr->index] = new_task;
    arr->index += 1;
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



void print_tasks(tasks* arr)
{
 
    for(int i = 0; i < arr->index ; i++) 
    {
        task_t* task = arr->array_of_tasks[i];
        printf("First task is %s, and the date for it is %s \n", task->name, task->date);
    }
    return;

}

void destroy(tasks* arr)
{
    for (int i = 0; i < arr->index; i++) {
        task_t* task = arr->array_of_tasks[i];
        free(task->name);
        free(task->date);
        free(task);
    }
    free(arr->array_of_tasks);
    free(arr);

}


int main(void) 
{
    tasks* arr = create_array();
    task_t* task = create_task_info(arr);
    task_t* task2 = create_task_info(arr);
    print_tasks(arr);
    
    destroy(arr);
    printf("trying git tag ");

    
    return 0;
}