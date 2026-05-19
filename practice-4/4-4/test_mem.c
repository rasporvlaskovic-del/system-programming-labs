#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    void *mem = malloc(500 * 1024 * 1024); // 500 MB
    memset(mem, 1, 500 * 1024 * 1024);     // Инициализируем, чтобы ОС реально выделила страницы
    sleep(15);                             // Время для проверки ДО free
    free(mem);
    sleep(15);                             // Время для проверки ПОСЛЕ free
    return 0;
}