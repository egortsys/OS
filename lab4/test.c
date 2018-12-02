#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>

#define FILE_NAME  "shared_memory"


int main(){

    int cheak_error;
    int max_size = 100000;
    int fd = shm_open(FILE_NAME, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);    // создаем разделяемую память
    if(fd == -1){
        perror("shm::open_fail");
        exit(-1);
    }
    cheak_error = ftruncate(fd,max_size); 
    if(cheak_error == -1){ // задаем ей нужный размер (для разделяемой памяти так можно, для обычных файлов -- не всегда. Для низ лучше lseek, write)
        perror("trucate::fail");
        exit(-1);
    }
    char *mapped_memory = mmap(NULL, max_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);  // отображаем на вирт. память
    if(mapped_memory == MAP_FAILED){
        perror("mmap::mapping_fail");
        fprintf(stderr, "%p", mapped_memory);
        exit(-1);
    }
      close(fd);  // дескриптор больше не нужен


   
    char *buffer = (char *)(mapped_memory);   // указатель на буффер, гду уже сами данные
    
    pid_t pro;
    pro = fork();


    if (pro == 0){
    	char str2[50];
    	if(sscanf(buffer, "%s", str2)){
    		printf("%s\n",str2);
    	}

    }
    else if (pro > 0){
    	printf("Это родитесльский процесс\n");
    	printf("Введите желаемое имя файла\n" );
    	char str[50];
    	scanf("%s", str);
    	sprintf(buffer, "%s", str);

    }

}