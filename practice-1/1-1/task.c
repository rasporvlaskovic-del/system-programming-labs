#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Открываем файл для записи
    int fd = open("binary.txt", O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("Ошибка открытия файла");
        return 1;
    }

    // Генерируем файл с '0' и '1'
    for (int i = 0; i < 100; i++) {
        char c = (i % 2 == 0) ? '0' : '1';
        write(fd, &c, 1);
    }

    close(fd);

    // Чтение и подсчет единиц
    fd = open("binary.txt", O_RDONLY);
    if (fd == -1) {
        perror("Ошибка открытия файла");
        return 1;
    }

    int ones_count = 0;
    char buffer;
    while (read(fd, &buffer, 1) > 0) {
        if (buffer == '1') {
            ones_count++;
        }
    }

    close(fd);

    // Записываем результат в файл ones.txt
    fd = open("ones.txt", O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("Ошибка открытия файла");
        return 1;
    }

    dprintf(fd, "Количество единиц: %d\n", ones_count);
    close(fd);

    return 0;
}
