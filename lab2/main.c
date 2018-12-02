#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    pid_t process;
    int number_process;
    int fd[2];
    if (pipe(fd) < 0 ){
        printf("Pipe не создан");
        exit(0);
    } 
    printf("Введите желаемое число процессов\n");
    scanf("%d",&number_process);
    for (int i=0 ; i<number_process; i++){
        process = fork();
        if (process < 0){
            perror("forc");
            exit(0);
        }
        if (process > 0){
            printf("Введите желаемое имя файла\n");
            char * file_name = (char*) malloc(sizeof(char)*50);
            scanf("%s", file_name);
            int* number = (int *) malloc(sizeof(int));
            printf("Введите верхню границу множества\n");
            scanf("%d", number);
            while (*number <=0){
                printf("Введите положительное число");
                scanf("%d", number);
            } 
            if(!(write(fd[1], file_name, sizeof(char)*50))){
                printf("Имя файла не записано \n");
                exit(0);
            }
            if (!(write(fd[1], number , sizeof(int*)))){
                printf("Верхняя граница не записана \n");
                exit(0);
            }
            for(int i = 1; i <= *number; i++){
                if (!(write(fd[1], &i , sizeof(int*)))){
                    printf("Число не записано \n");
                }
            }
        }
        else{
            int *number2 = (int*) malloc(sizeof(int));
            char * file_name_child = (char*) malloc(sizeof(char)*50);
            FILE * output;
            read(fd[0], file_name_child, sizeof(char)*50);
            output = fopen(file_name_child, "a");
            fseek(output,1,SEEK_END);
            close(fd[1]);
            if(read(fd[0], number2,sizeof(int*)) ){
                int *number_write = (int*) malloc(sizeof(int));
                for(int i = 0; i < *number2; i++){
                    if(read(fd[0], number_write ,sizeof(int*))){
                        fprintf(output, "%d ", *number_write);
                    }
                    else {
                        exit(0);
                    }
                }
            }
            else {
                printf("Ошибка считывания \n");
                fprintf(output, "%c", '\n');
                fclose(output);
                exit(0);
            }
        }
    }
}