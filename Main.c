#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"
#include "helper.h"


#define buffer_Size 99

int main(void) {
    tasks* arr = create_array();
    time_t now = time(NULL);
    struct tm *current = localtime(&now);
    printf("Current local time is: %s \n", asctime(current));
    FILE *test = fopen("example.txt", "a+");
    if (test == NULL) {
        perror("Cannot open file");
        return 1;
    }

    // Hoppa till filens början eftersom "a+" sätter pekaren i slutet
    fseek(test, 0, SEEK_SET);

    char name[256];
    char date[256];
    int days_left;

    // Anta att filformatet matchar det du skriver ut vid avslut.
    // Om du t.ex. skriver: 
    // "Name: %s, Date: %s, Total days left %d \n"
    // kan du läsa in med motsvarande fscanf:
    while (fscanf(test, "Name: %[^,], Date: %[^,], Total days left %d ", name, date, &days_left) == 3)  {
        // Skapa och lägg till uppgiften i arr
        char *saved_name = strdup(name);
        char *saved_date = strdup(date);

        // Skapa en uppgift med dessa data
        // Om din create_task inte kan ta emot days_left direkt, 
        // måste du ev. anpassa koden eller lägga till en funktion
        // som sätter rätt info. 
        // Just nu förlitar vi oss på calculate_days, 
        // men vill du att days_left i filen ska styra kanske
        // du behöver en separat metod.
        
        // I detta exempel ignorerar vi days_left från filen 
        // och förlitar oss på att calculate_days ger oss rätt värde igen.
        create_task(saved_name, saved_date, arr);
    }
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
            fclose(test);

        // Öppna på nytt i skrivläge för att skriva om filen
        test = fopen("example.txt", "w");
        if (test == NULL) {
            perror("Cannot open file for writing");
        } else {
            for (int i = 0; i < arr->size; i++) {
                task_t* task = arr->array_of_tasks[i]; 
                fprintf(test,"Name: %s, Date: %s, Total days left %d \n",
                        task->name, task->date, task->info->days_left);
            }
            fclose(test);
        }
        destroy(arr);
            break;
        }  
        } else 
        
        {
            printf("Invalid, these are the options \n");
        }
    }
    return 0;
}
