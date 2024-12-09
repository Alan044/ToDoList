#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"


#define buffer_Size 99

int main(void) {
    tasks* arr = create_array();
    time_t now = time(NULL);
    struct tm *current = localtime(&now);
    printf("Current local time is: %s \n", asctime(current));
    
    while (true) {
        printf("What is your choice of the day? \n"
                                                 "A: Add \n"
                                                 "L: List \n"
                                                 "R: Remove \n"
                                                 "E: Edit \n" 
                                                 "O: Order the tasks in ascending order \n" 
                                                 "U: Order the tasks in descending order \n" 
                                                 "Q: Quit\n");
        char answer[buffer_Size];
        scanf(" %98s", answer);
    if (valid_input(answer).valid) {
        if (strcmp(answer, "A") == 0) {
            create_task_info(arr);
        } else if (strcmp(answer, "L") == 0) {
            print_tasks(arr->array_of_tasks, arr->size);
        } else if (strcmp(answer, "R") == 0) {
            printf("When is the task you would like to remove? \n");
            char* task_to_remove = ask_task();
            remove_task(arr, task_to_remove);
            free(task_to_remove);
        } else if (strcmp(answer, "E") == 0) {
            printf("When is the task you would like to edit? \n");
            char* task_to_edit = ask_task();
            edit_task(arr, task_to_edit);
            free(task_to_edit);
        } else if (strcmp(answer, "O") == 0) {
            print_ascending(arr);
        } else if (strcmp(answer, "U") == 0) {
            print_descending(arr);
        } else if (strcmp(answer, "Q") == 0) {
            destroy(arr);
            break;
        }  
        } else {
        printf("Invalid, these are the options \n");
        }
    }
    return 0;
}
