#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

FILE *pidfile = NULL;

void handle_sigterm(int sig) {
    // Закрыть файл PID и удалить его
    if (pidfile != NULL) {
        fclose(pidfile);
        remove("pidfile.txt");
        printf("\nФайл pidfile.txt закрыт и удалён.\n");
    }
    exit(0);  // Завершить программу
}

int main() {
    // Открываем файл для записи PID
    pidfile = fopen("pidfile.txt", "w");
    if (pidfile == NULL) {
        perror("Не удалось открыть файл pidfile.txt");
        return 1;
    }

    // Получаем PID текущего процесса и записываем его в файл
    fprintf(pidfile, "%d\n", getpid());
    fflush(pidfile);

    // Устанавливаем обработчик сигнала SIGTERM
    signal(SIGTERM, handle_sigterm);

    // Программа будет работать в бесконечном цикле
    printf("Программа работает. PID: %d. Ожидаем сигнал SIGTERM...\n", getpid());
    
    // Бесконечный цикл
    while (1) {
        sleep(1);
    }

    return 0;
}
