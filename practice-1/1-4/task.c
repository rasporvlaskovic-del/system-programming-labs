#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

int main() {
    pid_t pid = fork();  // Создаем дочерний процесс

    if (pid == -1) {
        // Ошибка при создании процесса
        perror("Ошибка при создании процесса");
        return 1;
    }

    if (pid == 0) {
        // Дочерний процесс, запускаем команду sleep
        printf("Дочерний процесс: sleep 100\n");
        execlp("sleep", "sleep", "100", NULL);  // Запуск команды sleep
        // Если execlp вернется, значит произошла ошибка
        perror("Ошибка при запуске sleep");
        exit(1);
    } else {
        // Родительский процесс
        sleep(2);  // Даем время дочернему процессу запуститься

        // Ищем PID дочернего процесса
        printf("Родительский процесс: ищем PID дочернего процесса\n");
        printf("PID дочернего процесса: %d\n", pid);

        // Выводим статус процесса с помощью /proc/[PID]/status
        char path[256];
        snprintf(path, sizeof(path), "/proc/%d/status", pid);
        FILE *statusFile = fopen(path, "r");
        if (statusFile == NULL) {
            perror("Не удалось открыть файл статуса процесса");
            return 1;
        }

        char line[256];
        while (fgets(line, sizeof(line), statusFile)) {
            printf("%s", line);  // Выводим содержимое файла
        }
        fclose(statusFile);

        // Отправляем сигнал SIGTERM дочернему процессу
        printf("\nОтправляем сигнал SIGTERM дочернему процессу...\n");
        kill(pid, SIGTERM);  // Отправка сигнала SIGTERM

        // Ожидаем завершения дочернего процесса
        wait(NULL);

        // Проверяем, завершился ли процесс
        printf("\nПроцесс завершен.\n");
    }

    return 0;
}
