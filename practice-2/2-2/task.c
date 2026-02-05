#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 8

// Глобальная переменная для хранения максимального значения
int max = 0;

// Мьютекс для синхронизации доступа к переменной max
pthread_mutex_t max_mutex;

void* generate_random(void* arg) {
    // Генерация случайного числа
    int rand_num = rand() % 1000;

    // Захват мьютекса для безопасного обновления max
    pthread_mutex_lock(&max_mutex);

    // Если случайное число больше текущего значения max, обновляем его
    if (rand_num > max) {
        printf("Поток %ld генерировал число: %d, обновление max на: %d\n", (long)arg, rand_num, rand_num);
        max = rand_num;
    }

    // Освобождение мьютекса
    pthread_mutex_unlock(&max_mutex);

    return NULL;
}

int main() {
    // Инициализация генератора случайных чисел
    srand(time(NULL));

    // Инициализация мьютекса
    if (pthread_mutex_init(&max_mutex, NULL) != 0) {
        perror("Ошибка инициализации мьютекса");
        return 1;
    }

    pthread_t threads[NUM_THREADS];

    // Создание 8 потоков
    for (long i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, generate_random, (void*)i) != 0) {
            perror("Ошибка при создании потока");
            return 1;
        }
    }

    // Ожидание завершения всех потоков
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Вывод финального значения переменной max
    printf("\nФинальное значение max: %d\n", max);

    // Уничтожение мьютекса
    pthread_mutex_destroy(&max_mutex);

    return 0;
}
