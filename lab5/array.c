#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "array.h"

Array ArrayCreate(int size)
{
    if (size <= 0) {
        fprintf(stderr, "ERROR: size must be > 0\n");
        exit(EXIT_FAILURE);
    }

    Array arr = (Array) malloc(sizeof(*arr));
    if (!arr) {
        fprintf(stderr, "ERROR: no memory\n");
        exit(EXIT_FAILURE);
    }
    arr->size = size;
    arr->data = (Type **) malloc(size * sizeof(Type *));
    for (int i = 0; i < size; ++i) {
        arr->data[i] = NULL;
    }

    return arr;
}

void ArrayInsert(Array arr, Type *val, int idx)
{
    Type *ins = (Type *) malloc(strlen(val) + 1);
    if (!ins) {
        fprintf(stderr, "ERROR: no memory\n");
        exit(EXIT_FAILURE);
    }

    strcpy(ins, val);
    if (idx < 0 || idx >= arr->size) {
        printf("Out of range. Try another index.\n");
    }

    arr->data[idx] = ins;
}

void ArrayErase(Array arr, int idx)
{
    if (idx < 0 || idx >= arr->size) {
        printf("Out of range. Try another index.\n");
    }

    if (arr->data[idx]) {
        free(arr->data[idx]);
        arr->data[idx] = NULL;
    }
}

Type *ArrayGetElem(Array arr, int idx)
{
    if (idx < 0 || idx >= arr->size) {
        printf("Out of range. Try another index.\n");
    }

    return arr->data[idx];
}

int ArrayFind(Array arr, Type *val)
{
    for (int i = 0; i < arr->size; ++i) {
        if (arr->data[i] && !strcmp(arr->data[i], val))
            return i;
    }
    return -1;
}

void ArrayPrint(Array arr)
{
    for (int i = 0; i < arr->size; ++i) {
        printf("%d: %s\n", i, arr->data[i]);
    }
}

void ArrayDestroy(Array *arr)
{
    for (int i = 0; i < (*arr)->size; ++i) {
        free((*arr)->data[i]);
        (*arr)->data[i] = NULL;
    }
    free((*arr)->data);
    (*arr)->data = NULL;
    free(*arr);
    *arr = NULL;
}