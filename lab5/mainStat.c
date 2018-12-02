#include <stdio.h>
#include <stdlib.h>

#include "array.h"

int main(void)
{
    int act = 0, size = 0, idx = 0;
    Type key[KEY_SIZE];

    printf("Enter array size: ");
    scanf("%d", &size);

    Array arr = ArrayCreate(size);
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
            ArrayInsert(arr, key, idx);
            printf("Elem %s added\n", key);
            break;
        case 2:
            printf("Enter index for delete: ");
            scanf("%d", &idx);
            ArrayErase(arr, idx);
            printf("Elem deleted\n", key);
            break;
        case 3:
            printf("Enter index: ");
            scanf("%d", &idx);
            printf("%s\n", ArrayGetElem(arr, idx));
            break;
        case 4:
            printf("Enter key for search: ");
            scanf("%255s", &key);
            int findIdx = ArrayFind(arr, key);
            if (findIdx == -1) {
                printf("This elem isn't in array\n");
            } else {
                printf("Index %d\n", findIdx);
            }
            break;
        case 5:
            ArrayPrint(arr);
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
    ArrayDestroy(&arr);
    return 0;
}