#pragma once
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "util.h"


char* ask_date() 
{
    char buf[256];
    printf("When is the task due? \n");
    printf("Please write the following date on this format xxxx-xx-xx \n");
    scanf("%255s", buf);
    char* error = "Invalid date";
    
    if(strlen(buf) > 10 || strlen(buf) < 10)
    {
        printf("test1");
        return error;
    }

    for (int i = 0; i < 11; i++) 
    {
        if (!(buf[4] == '-' && buf[7] == '-')) {
            return error;
        }
        if (!(buf[0] == 2 && buf[5] == (1 || 0))) {
            return error;
        }

        if(isdigit(buf[i])) {
            return strdup(buf);
        } else {
            printf("test3");
            return error;
        }
    }
}
