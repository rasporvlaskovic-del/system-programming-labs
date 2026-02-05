#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Функция для выполнения команды в потоке
void* run_command(void* arg) {
    char* command = (char*)arg;
    system(command);
    return NULL;
}

int main() {
    pthread_t threads[3];
    
    // Команды для выполнения в потоках
    char* commands[3] = {
        "ls > thread1.txt",     // Команда для списка файлов
        "date > thread2.txt",   // Команда для даты и времени
        "whoami > thread3.txt"  // Команда для имени пользователя
    };

    // Создание 3 потоков
    for (int i = 0; i < 3; i++) {
        if (pthread_create(&threads[i], NULL, run_command, (void*)commands[i]) != 0) {
            perror("Ошибка при создании потока");
            return 1;
        }
    }

    // Ожидание завершения всех потоков
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    // Чтение и вывод содержимого файлов
    char buffer[256];
    FILE* file;

    // Чтение файла thread1.txt
    file = fopen("thread1.txt", "r");
    if (file != NULL) {
        printf("Содержимое thread1.txt (ls):\n");
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            printf("%s", buffer);
        }
        fclose(file);
    }

    // Чтение файла thread2.txt
    file = fopen("thread2.txt", "r");
    if (file != NULL) {
        printf("\nСодержимое thread2.txt (date):\n");
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            printf("%s", buffer);
        }
        fclose(file);
    }

    // Чтение файла thread3.txt
    file = fopen("thread3.txt", "r");
    if (file != NULL) {
        printf("\nСодержимое thread3.txt (whoami):\n");
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            printf("%s", buffer);
        }
        fclose(file);
    }

    return 0;
}
