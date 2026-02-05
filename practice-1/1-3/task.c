#include <stdio.h>
#include <stdlib.h>

int main() {
    // Создание файла large.txt размером 1 МБ
    FILE *file = fopen("large.txt", "wb");
    if (file == NULL) {
        perror("Ошибка при создании файла");
        return 1;
    }

    // Заполняем файл нулями (1 МБ)
    char buffer[1024 * 1024] = {0}; // 1 МБ (1024*1024 байт)
    fwrite(buffer, sizeof(char), sizeof(buffer), file);
    fclose(file);

    printf("Файл large.txt создан.\n");

    // Разделение файла на части по 100 КБ
    if (system("split -b 100k large.txt part_") != 0) {
        perror("Ошибка при разбиении файла");
        return 1;
    }

    printf("Файл разбит на части по 100 КБ.\n");

    // Собираем файл обратно с помощью команды cat
    if (system("cat part_* > reconstructed_large.txt") != 0) {
        perror("Ошибка при объединении файла");
        return 1;
    }

    printf("Файл успешно собран обратно в reconstructed_large.txt.\n");

    return 0;
}
