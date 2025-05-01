#include <stdio.h>
#include <string.h>

// тут я объявляю функции, которые написал на Асемблере
extern "C" {
    bool checkProperty(const char* text);
    void transformRule1(char* text);
    void transformRule2(char* text);
}

// Функция для ручного тестирования с вводом данных с терминала
void manualTest() {
    char text[101];
    printf("Введите текст (максимум 100 символов): ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';
    
    printf("\nИсходный текст: %s\n", text);
    
    // проверяю, есть ли в строке три одинаковых символа.
    bool hasProperty = checkProperty(text);

    // Если есть, то выполняю правило 1, иначе - правило 2.    
    if (hasProperty) {
        printf("Текст обладает заданным свойством. Применяем правило 1.\n");
        transformRule1(text);
    } else {
        printf("Текст не обладает заданным свойством. Применяем правило 2.\n");
        transformRule2(text);
    }
    
    printf("Преобразованный текст: %s\n", text);
}

// Функция для автоматического тестирования
void runTests() {
    struct TestCase {
        const char* input;
        const char* expected;
    };
    
    // Тесты для правила 1 (текст с 3+ одинаковыми символами)
    TestCase rule1Tests[] = {
        {"aaa", "aaa"},
        {"12aaa3bb45", "aaaaaaaaaa"},
        {"abc111def", "111111111"},
        {"xxxyyyzzz", "xxxxxxxxx"},
        {"aabbbcc", "bbbbbbb"},
        {"   space", "        "},
        {"!!!wow!!!", "!!!!!!!!!"},
        {"000000", "000000"},
        {"abc---def", "---------"},
        {"112233344", "333333333"}
    };
    
    // Тесты для правила 2 (текст без 3+ одинаковых символов), где надо изменять цифры
    TestCase rule2Tests[] = {
        {"abc1t92vr", "abctt*rvr"},
        {"123", "2**"},
        {"a1b2c3", "abb3c*"},
        {"no digits", "no digits"},
        {"1a2b3c4d", "aa3bdc*d"},
        {"test5str", "test*str"},
        {"9chars", "*chars"},
        {"2ab", "bab"},
        {"empty", "empty"},
        {"6stars", "*stars"}
    };
    
    printf("Запуск автоматических тестов...\n\n");
    
    // Тестирование правила 1
    printf("=== Тесты для правила 1 (текст с 3+ одинаковыми символами) ===\n");
    for (int i = 0; i < 10; i++) {
        char buffer[101];
        strcpy(buffer, rule1Tests[i].input);
        
        bool hasProperty = checkProperty(buffer);
        
        if (hasProperty) transformRule1(buffer);
        else  printf("Ошибка: текст должен подходить под правило 1, но проверка вернула false\n");
        
        
        printf("Тест %d: %s -> %s (ожидается: %s) - %s\n", 
               i+1, rule1Tests[i].input, buffer, rule1Tests[i].expected,
               strcmp(buffer, rule1Tests[i].expected) == 0 ? "ПРОЙДЕН" : "НЕ ПРОЙДЕН");
    }
    
    // Тестирование правила 2
    printf("\n=== Тесты для правила 2 (текст без 3+ одинаковых символов) ===\n");
    for (int i = 0; i < 10; i++) {
        char buffer[101];
        strcpy(buffer, rule2Tests[i].input);
        
        bool hasProperty = checkProperty(buffer);

        if (!hasProperty) transformRule2(buffer);
        else printf("Ошибка: текст не должен подходить под правило 1, но проверка вернула true\n");
        
        printf("Тест %d: %s -> %s (ожидается: %s) - %s\n", 
               i+1, rule2Tests[i].input, buffer, rule2Tests[i].expected,
               strcmp(buffer, rule2Tests[i].expected) == 0 ? "ПРОЙДЕН" : "НЕ ПРОЙДЕН");
    }
}

int main() {
    int choice;
    printf("Выберите режим:\n1. Ручной ввод\n2. Автоматические тесты\n> ");
    scanf("%d", &choice);
    getchar();
    
    if (choice == 1) manualTest();
    else runTests();

    
    return 0;
}