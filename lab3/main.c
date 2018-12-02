#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


typedef struct
{
	int value;
	char suit; 
	
} Card;

typedef struct  
{
	int NumberIterationForThread;
	Card *ColodForThreed;
	
}StructForThread;
//Функция swap будет использоваться для перемешивания массива;
void swap(Card a, Card b){
	Card c;
	c = a;
	a = b;
	b = c;
}
//Функция для перемешивания массива
void ColodShuffle (Card * Coloda){
	for(int i = 0; i < 52; i++){
		swap(Coloda[rand()%51],Coloda[rand()%51]);
	}
}

int CounterCon = 0;
void *Counter(void * ThreadData){
	StructForThread * Data = (StructForThread*) ThreadData;
	int NumberIterationInFun = Data->NumberIterationForThread;
	Card *coloda2 = Data->ColodForThreed;  
	int RandomNumberOne, RandomNumberTwo;
	for(int i = 0; i < NumberIterationInFun; i++){
		RandomNumberOne = rand() % 51;
		RandomNumberTwo = rand()% 50;
		if (coloda2[RandomNumberOne].value == coloda2[RandomNumberTwo].value){
			if(coloda2[RandomNumberOne].suit != coloda2[RandomNumberTwo].suit){
				CounterCon++;
			}
			else {
				while((coloda2[RandomNumberOne].suit == coloda2[RandomNumberTwo].suit) && (coloda2[RandomNumberOne].value == coloda2[RandomNumberTwo].value)){
					RandomNumberTwo = rand() % 50;
				}
				if (coloda2[RandomNumberOne].value == coloda2[RandomNumberTwo].value){
					if(coloda2[RandomNumberOne].suit != coloda2[RandomNumberTwo].suit){
						CounterCon++;
					}
				}
			}
		}
	}
	return NULL;
} 

int main(int argc, char **argv){
	int MaxNumberThread = 0;
	if(argc == 1 ){
		printf("Число раундов не передано параметром программы\nЗавершение программы\n");
		return 0;
	}
	if (argc == 3) {
		MaxNumberThread = atoi (*(argv+2));
	}
	int NumberIteration;
	if (MaxNumberThread < 0){
		printf("Не корректроне максимальное число потоков\nЗавершение программы\n");
		return 0;
	}
	else{
		NumberIteration = atoi(*(argv+1));
		if (NumberIteration <= 50){
			printf("В программу передано слишком маленькое число раундов,введите число > 50 \n");
			while(NumberIteration <= 50){
				scanf("%d", &NumberIteration);
			}
		}
	}
	if (NumberIteration != 0){
		/*Создадим короду карт. Числам 11, 12, 13, 14 соответствуют король, дама, валет, туз соответственно */
		int Value[] = {2,3,4,5,6,7,8,9,10,11,12,13,14};
		char Suit[] = {'B','S','P','K'};
		Card coloda[52];
		int NumberInColod = 0;
		for(int i = 0; i < 13; i++){
			for (int j = 0; j < 4; j++){
				coloda[NumberInColod].value = Value[i];
				coloda[NumberInColod].suit = Suit[j];
				NumberInColod++;
			}
		}
	
		ColodShuffle(coloda);
		int NumberOfThread = (int)log2((double) NumberIteration);
		if (NumberOfThread > MaxNumberThread){
			NumberOfThread = MaxNumberThread;
		}
		if (MaxNumberThread > 0){
			pthread_t * thread = (pthread_t*)(malloc(sizeof(pthread_t)*NumberOfThread));
			if (thread != NULL){
				StructForThread * DataOfThread = (StructForThread *)malloc(sizeof(StructForThread));
				DataOfThread -> NumberIterationForThread = (int) (NumberIteration / NumberOfThread);
				DataOfThread -> ColodForThreed = coloda;
				for(int i = 0; i < NumberOfThread; i++){
					if (pthread_create(&(thread[i]), NULL, Counter, (void *)DataOfThread) != 0){
						printf("Ошибка при создании потока\nЗавершение программы\n");
					}
				}
				for(int i = 0; i < NumberOfThread; i++){
					pthread_join(thread[i],NULL);
				}
			free(thread);
			free(DataOfThread);
			}
		}
		else {
			StructForThread * DataOfThread = (StructForThread *)malloc(sizeof(StructForThread));
			DataOfThread -> NumberIterationForThread = NumberIteration;
			DataOfThread -> ColodForThreed = coloda;
			Counter(DataOfThread);

		}
		//Для наглядности
		printf("Общее число итераций %d \n",NumberIteration);
		printf("Число потоков %d\n",NumberOfThread);
		float probability = (float)CounterCon / (float) NumberIteration;
		printf("Вероятность совпадние - %f\n", probability); 
		return 0;
	}
	else{
		return 0;
	}
} 