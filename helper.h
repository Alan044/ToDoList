#ifndef helper.h
#define helper.h
#include  "helper.h"
date_t task_date(char* task);

bool valid_length_and_char(char* buf, char* error);

bool valid_year(char* buf, char* error);

char* ask_date();

void resize_array(tasks* arr);

task_t* create_task(char* name, char* date, tasks* arr);

option_t valid_name(tasks* arr, char *name_to_remove);

int calculate_days(task_t* task);




#endif 
