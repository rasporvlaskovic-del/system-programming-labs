#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    pid_t pid;

    // Создаём дочерний процесс с помощью fork()
    pid = fork();

    if (pid == -1) {
        // Обработка ошибки при создании процесса
        perror("Ошибка при создании процесса");
        return 1;
    }

    if (pid == 0) {
        // Дочерний процесс
        int fd = open("child.txt", O_WRONLY | O_CREAT, 0644);
        if (fd == -1) {
            perror("Ошибка при создании файла");
            return 1;
        }

        // Запись в файл
        write(fd, "Hello from child\n", 17);
        close(fd);

        exit(0);  // Завершаем дочерний процесс
    } else {
        // Родительский процесс
        int status;
        wait(&status);  // Ожидаем завершения дочернего процесса

        // Чтение содержимого файла
        char buffer[256];
        FILE *file = fopen("child.txt", "r");
        if (file == NULL) {
            perror("Ошибка при открытии файла");
            return 1;
        }

        printf("Содержимое файла 'child.txt':\n");
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            printf("%s", buffer);
        }
        fclose(file);
    }

    return 0;
}
