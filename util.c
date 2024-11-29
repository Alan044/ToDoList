#pragma once
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include "util.h"


static bool valid_month(char* buf, char* error)
{

    if ((buf[5] != '1' && buf[5] != '0')) {
        printf("%s \n", error);
        return false;
    }
    if (buf[5] == '1') {
        if(buf[6] == '0'||  buf[6] == '2'|| buf[6] == '1') {
            return true;
        }
        printf("%s \n", error);
        return false;
    }
    if (buf[5] == '0') {
        if(buf[6] != '0') {
            return true;
        }
        printf("%s \n", error);
        return false;
    }
    return true;
}

static bool valid_days(char* buf, char* error)
{
    if ((buf[8] != '2' && buf[8] != '0' && buf[8] != '3' && buf[8] != '1')) {
        printf("%s \n", error);
        return false;
    }
    if (buf[8] == '3') {
        if (buf[9] == '1' || buf[9] == '0' ) {
            return true;
        }
        printf("%s \n", error);
        return false;
    }
    if (buf[8] == '0') {
        if(buf[9] != '0') {
            return true;
        }
        printf("%s \n", error);
        return false;
    }
    return true;
}

static bool valid_length_and_char(char* buf, char* error)
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

char* ask_date() 
{
    char buf[256];
    while (true) {
    printf("When is the task due? \n");
    printf("Please write the following date on this format xxxx-xx-xx \n");
    scanf("%255s", buf);
    char* error = "Invalid date";
    for (int i = 0; i < 10; i++ ) {
        
        if (!(buf[0] == '2')) {
            printf("%s \n", error);
            printf("test1");
            break;
        }
        if(!(valid_length_and_char(buf, error))) {
            printf("test2");
            break;
        }
        if(!(valid_month(buf, error))) {
            printf("test3");
            break;
        }
        if(!(valid_days(buf, error))) {
            printf("test4");
            break;
        }
        
            if(isdigit(buf[i])) {
                return strdup(buf);
            } else {
            printf("te3");
            printf("%s \n", error);
            break;
            }
        }
    }    
}

