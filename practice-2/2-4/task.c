#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Программа начинает выполнение...\n");

    // Засыпаем на 5 секунд
    sleep(5);

    printf("Программа завершила выполнение после 5 секунд сна.\n");

    return 0;
}
