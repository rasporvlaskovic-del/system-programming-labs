#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid1, pid2;

    // Создаем первый дочерний процесс
    pid1 = fork();
    if (pid1 == -1) {
        perror("Fork failed for first child");
        exit(1);
    }

    if (pid1 == 0) {
        // Первый дочерний процесс выполняет команду ps aux
        printf("Child 1 (PID: %d) is running ps aux\n", getpid());
        execlp("ps", "ps", "aux", (char *) NULL);
        // Если execlp возвращает, значит произошла ошибка
        perror("execlp failed for ps aux");
        exit(1);
    }

    // Создаем второй дочерний процесс
    pid2 = fork();
    if (pid2 == -1) {
        perror("Fork failed for second child");
        exit(1);
    }

    if (pid2 == 0) {
        // Второй дочерний процесс выполняет команду date
        printf("Child 2 (PID: %d) is running date\n", getpid());
        execlp("date", "date", (char *) NULL);
        // Если execlp возвращает, значит произошла ошибка
        perror("execlp failed for date");
        exit(1);
    }

    // Родительский процесс ожидает завершения обоих дочерних процессов
    waitpid(pid1, NULL, 0); // Ожидаем завершение первого дочернего процесса
    waitpid(pid2, NULL, 0); // Ожидаем завершение второго дочернего процесса

    // Родительский процесс выводит сообщение
    printf("Both child processes have completed.\n");

    return 0;
}
