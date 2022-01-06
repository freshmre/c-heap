#pragma once

typedef struct node {
    char *val;
    struct node *left;
    struct node *right;
} node;

int init_maxheap(void);
int insert_maxheap(node *root, char *s);
