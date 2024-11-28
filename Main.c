#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>


typedef struct task task_t;
typedef struct arr_task tasks;
typedef struct info info_t;
// Create another struct to help with further information about the tasks such as, days left
// Category of Task?, 


struct info{
    int index;
    int days_left;
    char* Category;    
};


struct task{
    char* name;
    char* date;
    info_t* info;
};

struct arr_task {
    task_t** array_of_tasks;
    int size;
};

tasks* create_array()
{
    tasks* arr = calloc(1, sizeof(tasks));
    arr->array_of_tasks = calloc(arr->size, sizeof(task_t*));
    arr->size = 0;
    return arr;
} 

task_t* create_task(char* name, char* date, tasks* arr)
{
    task_t *new_task = calloc(1,sizeof(task_t));

    new_task->name = strdup(name);
    new_task->date = strdup(date);
    new_task->info->index = arr->size;

    arr->array_of_tasks[arr->size] = new_task;
    arr->size += 1;
    return new_task;
}

task_t* create_task_info(tasks* arr)
{
    char buf[100];
    char date[100];

    printf("What is the name of the task? \n");
    scanf("%99s", buf);

    printf("When is the task due ?  \n ");
    scanf("%99s", date);
    
    task_t* task = create_task(buf,date, arr);

    return task;
}



void print_tasks(tasks* arr)
{
 
    for(int i = 0; i < arr->size ; i++) 
    {
        task_t* task = arr->array_of_tasks[i];
        printf("First task is %s, and the date for it is %s \n", task->name, task->date);
    }
    return;
}

void calculate_days(task_t* task)
{
    return;
}

void print_ascending(tasks* arr)
{
    // maybe with the use of print_tasks 
}
void print_descending(tasks* arr)
{
    // maybe with the use of print_tasks 
}

void destroy(tasks* arr)
{
    for (int i = 0; i < arr->size; i++) {
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
    gtk_init
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