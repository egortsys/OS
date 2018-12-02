#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>
#include <ctype.h>

#define KEY_SIZE 256

typedef char Type;

typedef struct _array {
    int size;
    Type **data;
} *Array;


Array ArrayCreate(int size);
void ArrayInsert(Array arr, Type *val, int idx);
void ArrayErase(Array arr, int idx);
Type *ArrayGetElem(Array arr, int idx);
int ArrayFind(Array arr, Type *val);
void ArrayPrint(Array arr);
void ArrayDestroy(Array *arr);

#endif