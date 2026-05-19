#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main() {
    const char *filepath = "mmap_test.txt";
    
    // Создаем файл для теста
    int fd = open(filepath, O_CREAT | O_RDWR | O_TRUNC, 0644); // [cite: 124]
    write(fd, "AAAAA", 5);
    
    // Получаем размер [cite: 124]
    struct stat st;
    fstat(fd, &st);

    // Отображаем в память [cite: 124]
    char *mapped = mmap(NULL, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("mmap failed"); exit(EXIT_FAILURE); // [cite: 125]
    }

    // Меняем первый символ
    mapped[0] = 'Z';

    // Освобождаем и закрываем [cite: 124]
    munmap(mapped, st.st_size);
    close(fd);

    // Проверяем сохранение на диске
    fd = open(filepath, O_RDONLY);
    char buf[6] = {0};
    read(fd, buf, 5);
    close(fd);

    printf("Содержимое файла на диске: %s\n", buf);
    return 0;
}