# Проверка свойства текста: содержит ли текст подстроку из 3+ одинаковых символов подряд
# Вход: char* text в %rdi
# Выход: bool (1 - true, 0 - false) в %rax

.global checkProperty
checkProperty:
    xor %rax, %rax            # Обнуляем результат (по умолчанию false)
    mov %rdi, %rsi            # Сохраняем указатель на начало строки
    
check_loop:
    mov (%rsi), %cl           # Загружаем текущий символ в %cl
    test %cl, %cl             # Проверяем на нулевой символ
    jz end_check              # Если конец строки - выходим
    
    mov %cl, %dl              # Сохраняем текущий символ в %dl
    mov $1, %r8d              # Счетчик повторений = 1
    
count_repeats:
    inc %rsi                  # Переходим к следующему символу
    mov (%rsi), %cl           # Загружаем следующий символ
    cmp %dl, %cl              # Сравниваем с предыдущим
    jne next_char             # Если не совпадает - переходим к следующему символу
    inc %r8d                  # Увеличиваем счетчик повторений
    cmp $3, %r8d              # Проверяем, достигли ли 3 повторений
    jge found_property        # Если да - свойство найдено
    jmp count_repeats         # Продолжаем считать
    
next_char:
    test %cl, %cl             # Проверяем на конец строки
    jz end_check              # Если конец строки - выходим
    jmp check_loop            # Переходим к следующему символу
    
found_property:
    mov $1, %rax              # Устанавливаем результат в true
    
end_check:
    ret