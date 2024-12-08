#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"

int main(void) {
    tasks* arr = create_array();
    time_t now = time(NULL);
    struct tm *current = localtime(&now);
    printf("Current local time is: %s \n", asctime(current));
    
    while (true) {
        printf("What is your choice of the day? (A: Add, L: List, R: Remove, E: Edit, Q: Quit)\n");

        char answer[99];
        scanf(" %98s", answer);
    if (valid_input(answer).valid) {
        if (strcmp(answer, "A") == 0) {
            create_task_info(arr);
        } else if (strcmp(answer, "L") == 0) {
            print_tasks(arr);
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
