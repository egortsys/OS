#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "array.h"

int main(void)
{
    Array (*ArrayCreate)(int size);
    void (*ArrayInsert)(Array arr, Type *val, int idx);
    void (*ArrayErase)(Array arr, int idx);
    Type *(*ArrayGetElem)(Array arr, int idx);
    int (*ArrayFind)(Array arr, Type *val);
    void (*ArrayPrint)(Array arr);
    void (*ArrayDestroy)(Array *arr);
    char *err;

    void *libHandle;
    libHandle = dlopen("libarray.so", RTLD_LAZY);
    if (!libHandle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    ArrayCreate = dlsym(libHandle, "ArrayCreate");
    ArrayInsert = dlsym(libHandle, "ArrayInsert");
    ArrayErase = dlsym(libHandle, "ArrayErase");
    ArrayGetElem = dlsym(libHandle, "ArrayGetElem");
    ArrayFind = dlsym(libHandle, "ArrayFind");
    ArrayPrint = dlsym(libHandle, "ArrayPrint");
    ArrayDestroy = dlsym(libHandle, "ArrayDestroy");

    if (err = dlerror()) {
        fprintf(stderr, "%s\n", err);
        exit(EXIT_FAILURE);
    }

    int act = 0, size = 0, idx = 0;
    Type key[KEY_SIZE];

    printf("Enter array size: ");
    scanf("%d", &size);

    Array arr = (*ArrayCreate)(size);
    printf("This is compile-time linking\n\n");
    printf("Choose an operation:\n");
    printf("1) Insert elem in array\n");
    printf("2) Delete elem from array\n");
    printf("3) Get elem from array\n");
    printf("4) Find elem in array\n");
    printf("5) Print array\n");
    printf("0) Exit\n");
    while (scanf("%d", &act) && act) {
        switch(act) {
        case 1:
            printf("Enter key for insert: ");
            scanf("%255s", &key);
            printf("Enter index for insert: ");
            scanf("%d", &idx);
            (*ArrayInsert)(arr, key, idx);
            printf("Elem %s added\n", key);
            break;
        case 2:
            printf("Enter index for delete: ");
            scanf("%d", &idx);
            (*ArrayErase)(arr, idx);
            printf("Elem %s deleted\n", key);
            break;
        case 3:
            printf("Enter index: ");
            scanf("%d", &idx);
            Type *res = (*ArrayGetElem)(arr, idx);
            printf("%s\n", res);
            break;
        case 4:
            printf("Enter key for search: ");
            scanf("%255s", &key);
            int findIdx = (*ArrayFind)(arr, key);
            if (findIdx == -1) {
                printf("This elem isn't in array\n");
            } else {
                printf("Index %d\n", findIdx);
            }
            break;
        case 5:
            (*ArrayPrint)(arr);
            break;
        default:
            printf("Incorrect command\n");
            break;
        }
        printf("Choose an operation:\n");
        printf("1) Insert elem in array\n");
        printf("2) Delete elem from array\n");
        printf("3) Get elem from array\n");
        printf("4) Find elem in array\n");
        printf("5) Print array\n");
        printf("0) Exit\n");
    }
    (*ArrayDestroy)(&arr);
    return 0;
}