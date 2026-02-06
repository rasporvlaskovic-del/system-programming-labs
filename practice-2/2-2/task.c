#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 10

// Инициализация счетов
int account1 = 500;
int account2 = 500;

// Мьютекс для защиты операций
pthread_mutex_t mutex;

void* transfer(void* arg) {
    // Блокируем мьютекс
    pthread_mutex_lock(&mutex);

    // Переводим 10 с account1 на account2
    account1 -= 10;
    account2 += 10;

    // Разблокируем мьютекс
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Инициализация мьютекса
    pthread_mutex_init(&mutex, NULL);

    // Создание потоков
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, transfer, NULL);
    }

    // Ожидаем завершения всех потоков
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Уничтожаем мьютекс
    pthread_mutex_destroy(&mutex);

    // Выводим итоговые значения счетов
    printf("Final account1: %d\n", account1);
    printf("Final account2: %d\n", account2);

    return 0;
}
