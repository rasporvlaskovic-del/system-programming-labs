#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* run_ls(void* arg) {
    system("ls > thread1.txt");
    pthread_exit(NULL);
}

void* run_date(void* arg) {
    system("date > thread2.txt");
    pthread_exit(NULL);
}

void* run_whoami(void* arg) {
    system("whoami > thread3.txt");
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2, thread3;

    // Создание потоков
    pthread_create(&thread1, NULL, run_ls, NULL);
    pthread_create(&thread2, NULL, run_date, NULL);
    pthread_create(&thread3, NULL, run_whoami, NULL);

    // Ожидание завершения всех потоков
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    // Главный поток читает файлы
    char buffer[256];

    FILE* file1 = fopen("thread1.txt", "r");
    if (file1) {
        printf("Contents of thread1.txt:\n");
        while (fgets(buffer, sizeof(buffer), file1)) {
            printf("%s", buffer);
        }
        fclose(file1);
    }

    FILE* file2 = fopen("thread2.txt", "r");
    if (file2) {
        printf("\nContents of thread2.txt:\n");
        while (fgets(buffer, sizeof(buffer), file2)) {
            printf("%s", buffer);
        }
        fclose(file2);
    }

    FILE* file3 = fopen("thread3.txt", "r");
    if (file3) {
        printf("\nContents of thread3.txt:\n");
        while (fgets(buffer, sizeof(buffer), file3)) {
            printf("%s", buffer);
        }
        fclose(file3);
    }

    return 0;
}
