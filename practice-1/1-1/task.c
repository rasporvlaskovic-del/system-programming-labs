#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    int input_fd, output_fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, i;
    int ones_count = 0;

    // Открытие файла binary.txt для чтения
    input_fd = open("binary.txt", O_RDONLY);
    if (input_fd == -1) {
        perror("Error opening binary.txt");
        return 1;
    }

    // Чтение данных из binary.txt
    while ((bytes_read = read(input_fd, buffer, BUFFER_SIZE)) > 0) {
        // Подсчет единичных символов
        for (i = 0; i < bytes_read; i++) {
            if (buffer[i] == '1') {
                ones_count++;
            }
        }
    }

    if (bytes_read == -1) {
        perror("Error reading binary.txt");
        close(input_fd);
        return 1;
    }

    // Закрытие файла binary.txt
    close(input_fd);

    // Открытие/создание файла ones.txt для записи
    output_fd = open("ones.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_fd == -1) {
        perror("Error opening ones.txt");
        return 1;
    }

    // Запись результата в ones.txt
    char result[50];
    snprintf(result, sizeof(result), "Number of ones: %d\n", ones_count);
    if (write(output_fd, result, sizeof(result)) == -1) {
        perror("Error writing to ones.txt");
        close(output_fd);
        return 1;
    }

    // Закрытие файла ones.txt
    close(output_fd);

    printf("The number of ones has been written to ones.txt\n");

    return 0;
}
