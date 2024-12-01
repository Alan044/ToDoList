#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"

int main(void) {
    tasks* arr = create_array();

    while (true) {
        printf("What is your choice of the day? (A: Add, L: List, R: Remove, E: Edit, Q: Quit)\n");

        char answer;
        scanf(" %c", &answer);

        if (answer == 'A') {
            create_task_info(arr);
        } else if (answer == 'L') {
            print_tasks(arr);
        } else if (answer == 'R') {
            printf("what is the task you would like to remove \n");
            char answer[256];
            scanf("%255s", answer);
            remove_task(arr, answer);
        } else if (answer == 'E') {
            printf("what is the task you would like to remove \n");
            char answer[256];
            scanf("%255s", answer);
            edit_task(arr, answer);
        } else if (answer == 'Q') {
            destroy(arr);
            break;
        } else {
            printf("Invalid choice! Please enter A, L, R, E or Q.\n");
        }
    }

    return 0;
}
