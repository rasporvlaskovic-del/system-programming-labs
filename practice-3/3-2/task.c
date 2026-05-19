#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>

#define FIFO_NAME "myfifo"

int main() {
    pid_t pid;

    // Создание FIFO [cite: 64]
    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("mkfifo failed"); // [cite: 65]
    }

    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) { // Родитель (Писатель)
        int fd = open(FIFO_NAME, O_WRONLY);
        if (fd == -1) {
            perror("open write failed");
            exit(EXIT_FAILURE);
        }

        srand(time(NULL));
        int numbers[50];
        printf("[Писатель] Отправляю 50 чисел...\n");
        for (int i = 0; i < 50; i++) {
            numbers[i] = rand() % 1000;
        }
        
        write(fd, numbers, sizeof(numbers));
        close(fd);
        wait(NULL);
    } else { // Дочерний (Читатель)
        int fd = open(FIFO_NAME, O_RDONLY);
        if (fd == -1) {
            perror("open read failed");
            exit(EXIT_FAILURE);
        }

        int numbers[50];
        read(fd, numbers, sizeof(numbers));
        close(fd);

        int min = numbers[0], max = numbers[0];
        for (int i = 1; i < 50; i++) {
            if (numbers[i] < min) min = numbers[i];
            if (numbers[i] > max) max = numbers[i];
        }

        printf("[Читатель] Мин: %d, Макс: %d\n", min, max);
        
        // Удаление FIFO [cite: 64]
        unlink(FIFO_NAME);
        exit(EXIT_SUCCESS);
    }
    return 0;
}