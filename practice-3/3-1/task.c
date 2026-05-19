#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipe_p2c[2]; // Родитель -> Дочерний (имя файла)
    int pipe_c2p[2]; // Дочерний -> Родитель (размер)
    pid_t pid;

    if (pipe(pipe_p2c) == -1 || pipe(pipe_c2p) == -1) {
        perror("pipe failed"); // [cite: 50]
        exit(EXIT_FAILURE);
    }

    // Создадим тестовый файл для проверки
    int test_fd = open("test.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    write(test_fd, "Hello, World!", 13);
    close(test_fd);

    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) { // Родительский процесс
        close(pipe_p2c[0]);
        close(pipe_c2p[1]);

        char filename[] = "test.txt";
        write(pipe_p2c[1], filename, strlen(filename) + 1);
        close(pipe_p2c[1]);

        int char_count = 0;
        wait(NULL); // Ждем завершения дочернего
        read(pipe_c2p[0], &char_count, sizeof(int));
        close(pipe_c2p[0]);

        printf("[Родитель] Дочерний процесс вернул количество символов: %d\n", char_count);
    } else { // Дочерний процесс
        close(pipe_p2c[1]);
        close(pipe_c2p[0]);

        char filename[256];
        read(pipe_p2c[0], filename, sizeof(filename));
        close(pipe_p2c[0]);

        int fd = open(filename, O_RDONLY);
        if (fd == -1) {
            perror("open failed");
            exit(EXIT_FAILURE);
        }

        int count = 0;
        char buffer[1024];
        ssize_t bytes_read;
        while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
            count += bytes_read;
        }
        close(fd);

        write(pipe_c2p[1], &count, sizeof(int));
        close(pipe_c2p[1]);
        exit(EXIT_SUCCESS);
    }
    return 0;
}