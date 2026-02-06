#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t child_completed = 0;

void sigchld_handler(int signum) {
    child_completed++;
    // Используем write() вместо printf() для асинхронной безопасности
    write(1, "Child process completed\n", 23);
}

int main() {
    // Устанавливаем обработчик сигнала SIGCHLD
    struct sigaction sa;
    sa.sa_handler = sigchld_handler;
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sigaction(SIGCHLD, &sa, NULL);

    pid_t pid1, pid2, pid3;

    // Создаем 3 дочерних процесса
    if ((pid1 = fork()) == 0) {
        // Первый дочерний процесс выполняет sleep
        sleep(1);
        exit(0);
    }
    
    if ((pid2 = fork()) == 0) {
        // Второй дочерний процесс выполняет sleep
        sleep(2);
        exit(0);
    }

    if ((pid3 = fork()) == 0) {
        // Третий дочерний процесс выполняет sleep
        sleep(3);
        exit(0);
    }

    // Родительский процесс ожидает завершения всех дочерних
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    // Родительский процесс выводит количество завершенных дочерних процессов
    write(1, "All child processes completed\n", 30);

    return 0;
}
