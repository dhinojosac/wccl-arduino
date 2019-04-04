#ifndef UNION-FIND_H_INCLUDED
#define UNION-FIND_H_INCLUDED
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    uint8_t low;
    uint8_t high;
} data_t;

typedef struct node {
    data_t data;
    struct node* next;
} node_t;

node_t * initUnion(void);
uint8_t add_at(node_t* head, data_t data);
uint8_t check_is_data(node_t* head, data_t data);
uint8_t get_len_union(node_t* head);
data_t get_data(node_t* head,uint8_t index);

#endif // UNION-FIND_H_INCLUDED
