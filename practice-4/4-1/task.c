#include <stdio.h>
#include <stdlib.h>

struct Student {
    int id;
    char name[20];
};

int main() {
    // Выделение памяти [cite: 109]
    struct Student *students = (struct Student *)malloc(50 * sizeof(struct Student));
    
    // Проверка выделения [cite: 110]
    if (students == NULL) {
        perror("malloc failed");
        return EXIT_FAILURE;
    }

    // Заполнение данными
    for (int i = 0; i < 50; i++) {
        students[i].id = i + 1;
        snprintf(students[i].name, 20, "Student_%d", i + 1);
    }

    // Вывод для проверки
    printf("Данные студента 10: ID=%d, Имя=%s\n", students[9].id, students[9].name);
    printf("Данные студента 50: ID=%d, Имя=%s\n", students[49].id, students[49].name);

    // Освобождение памяти [cite: 109]
    free(students);
    return 0;
}