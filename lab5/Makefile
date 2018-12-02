CC = gcc
FLAGS = -std=c99 -pthread -w -pipe -O2 -Wextra -Werror -Wall -Wno-sign-compare -pedantic -lm -g3

all: run

run: libarray.so mainStat.o mainDyn.o
	$(CC) $(FLAGS) -o run-stat mainStat.o -L/home/egor/Рабочий\ стол/OC/lab5var21 -larray -Wl,-rpath,.
	$(CC) $(FLAGS) -o run-dyn mainDyn.o -ldl

mainStat.o: mainStat.c
	$(CC) -c $(FLAGS) mainStat.c

mainDyn.o: mainDyn.c
	$(CC) -c $(FLAGS) mainDyn.c

array.o: array.c
	$(CC) -c -fPIC $(FLAGS) array.c

libarray.so: array.o
	$(CC) $(FLAGS) -shared -fpic -o libarray.so array.o

clean:
	rm -f *.o run-stat run-dyn *.so