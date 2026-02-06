#!/bin/bash

# Указываем файл для сохранения команд и результатов
commands_file="commands.txt"
> $commands_file  # Очистить файл перед записью

# 1. Запускаем процесс sleep 100 в фоновом режиме
echo "Запускаем процесс sleep 100; echo 'Done' в фоновом режиме" >> $commands_file
(sleep 100; echo "Done") &

# Получаем PID запущенного процесса
PID=$!

# Сохраняем команду и PID
echo "Получаем PID процесса: $PID" >> $commands_file
echo "PID = $PID" >> $commands_file

# 2. Проверяем содержимое /proc/[PID]/stat и сохраняем результат
echo "Проверяем /proc/$PID/stat" >> $commands_file
cat /proc/$PID/stat >> $commands_file

# 3. Завершаем процесс
echo "Завершаем процесс с помощью kill $PID" >> $commands_file
kill $PID

# 4. Проверяем, что процесс больше не существует и сохраняем результат
echo "Проверяем, что процесс не существует:" >> $commands_file
if ps -p $PID > /dev/null
then
   echo "Процесс не завершен." >> $commands_file
else
   echo "Процесс завершен." >> $commands_file
fi
