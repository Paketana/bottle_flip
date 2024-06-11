/*
Stwórz funkcję generującą ciąg 10 cyfr (0-100). 
Funkcja powinna sortować wygenerowany ciąg 
(od najmniejszej do największej) 
i wyświetlać go na standardowe wyjście. 
Funkcja następnie musi być uruchamiana przez wątek.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void* generate_and_sort(void* arg) {
    int arr[10];
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        arr[i] = rand() % 101;
    }
    
    for (int i = 0; i < 9; ++i) {
        for (int j = i+1; j < 10; ++j) {
            if (arr[i] > arr[j]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < 10; ++i) {
        printf("%d\n ", arr[i]);
    }
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, generate_and_sort, NULL);
    pthread_join(thread, NULL);
    return 0;
}

// gcc thread.c -o thread -lpthread