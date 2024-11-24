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
};



task_t* create_task(char* name, char* date)
{
    task_t *new_task = calloc(1,sizeof(task_t));

    new_task->name = strdup(name);
    new_task->date = strdup(date);
    tasks** arr = calloc(1, sizeof(task_t*));
    
    return new_task;
}

task_t* create_task_info()
{
    char buf[100];
    char date[100];

    printf("what is the name of the task? \n");
    scanf("%99s", buf);

    printf("When is the task due ?  \n ");
    scanf("%99s", date);
    
    task_t* task = create_task(buf,date);

    return task;
}



void print_tasks(char* name, char* date)
{
    printf("First task is %s, and the date for it is %s \n", name, date);
    return;

}


int main(void) 
{

    task_t* task = create_task_info();
    print_tasks(task->name, task->date);
    return 0;
}