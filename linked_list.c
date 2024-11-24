#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node node_t;

struct node {
    char* current;
    node_t* next;
};
struct linked_list {
    node_t* list;
    node_t* first;
    node_t* last;
};