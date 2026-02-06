#!/bin/bash

# Создаем директорию mydir
mkdir mydir

# Создаем 5 файлов
touch mydir/file1.txt mydir/file2.txt mydir/file3.txt mydir/file4.txt mydir/file5.txt

# Устанавливаем права на файлы
chmod 644 mydir/file1.txt
chmod 755 mydir/file2.txt
chmod 600 mydir/file3.txt
chmod 444 mydir/file4.txt
chmod 700 mydir/file5.txt

# Выводим результат команды ls -l
ls -l mydir
