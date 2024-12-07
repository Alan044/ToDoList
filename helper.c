
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
