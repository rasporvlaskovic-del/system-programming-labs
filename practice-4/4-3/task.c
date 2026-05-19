#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

volatile sig_atomic_t keep_running = 1;

void sigterm_handler(int signum) {
    keep_running = 0;
}

int main() {
    pid_t pid = fork(); // [cite: 138]
    if (pid < 0) exit(EXIT_FAILURE);
    if (pid > 0) exit(EXIT_SUCCESS); // Родитель завершается

    if (setsid() < 0) exit(EXIT_FAILURE); // [cite: 138]

    signal(SIGTERM, sigterm_handler); // [cite: 140]

    pid = fork();
    if (pid < 0) exit(EXIT_FAILURE);
    if (pid > 0) exit(EXIT_SUCCESS);

    umask(0); // [cite: 138]
    chdir("/"); // [cite: 138]

    // Закрываем стандартные дескрипторы [cite: 138]
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    FILE *log_file = fopen("/tmp/daemon_iter.log", "w");
    if (!log_file) exit(EXIT_FAILURE);

    int iteration = 1;
    while (keep_running) {
        fprintf(log_file, "Итерация: %d\n", iteration++); // [cite: 139]
        fflush(log_file);
        sleep(2);
    }

    fprintf(log_file, "Демон корректно завершен по SIGTERM.\n");
    fclose(log_file);
    return EXIT_SUCCESS;
}