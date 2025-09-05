markdown
# Лабораторная работа №2: Шаблонный класс Vector

## Описание проекта

Проект представляет собой реализацию шаблонного класса `Vector` - динамического массива с возможностью автоматического изменения размера. Класс предоставляет широкий набор методов для работы с данными, включая математические операции и поддержку итераторов.

## Функциональность

### Основные операции:
- **Динамическое изменение размера** - автоматическое увеличение capacity при необходимости
- **Добавление/удаление элементов** - `pushBack()`, `popBack()`
- **Доступ к элементам** - оператор `[]`, `getElem()`, `setElem()`
- **Проверка состояния** - `isEmpty()`, `size()`, `clear()`

### Математические операции:
- **Сложение векторов** - `operator+`, `operator+=`
- **Вычитание векторов** - `operator-`, `operator-=`
- **Умножение на скаляр** - `operator*`, `operator*=`
- **Деление на скаляр** - `operator/`, `operator/=`

### Итераторы:
- **Поддержка range-based for loops**
- **Прямые итераторы** с перегрузкой операторов
- **Безопасный доступ** с проверкой границ

## Структура проекта
OOP_lab2/
├── core/ # Основные классы
│ ├── vector.h # Шаблонный класс Vector
│ └── iterator.h # Класс итератора
├── tests/ # Тесты
│ └── testvector.cpp # Google Tests
├── OOP_lab2.pro # Файл проекта qmake
└── main.cpp # Точка входа для тестов

text

## Ключевые компоненты

### Класс Vector:
```cpp
template <typename Type>
class Vector {
    // Конструкторы
    Vector(int length = 0);
    Vector(std::initializer_list<Type> list);
    Vector(const Vector& other); // Копирование
    Vector(Vector&& other) noexcept; // Перемещение
    
    // Операции
    Type& operator[](int index);
    Vector& operator+=(const Vector& other);
    // ... другие операторы
    
    // Методы
    void pushBack(const Type& value);
    void popBack();
    void clear();
    bool isEmpty() const;
    int size() const;
    
    // Итераторы
    Iterator<Type> begin();
    Iterator<Type> end();
};
Класс Iterator:
cpp
template <typename Type>
class Iterator {
    Iterator(Vector<Type>& container, int startIndex = 0);
    Iterator<Type> next();
    Type& value();
    bool isEnd() const;
    
    // Перегрузка операторов
    Iterator& operator++();
    Type& operator*();
    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;
};
Математические операции
Поддерживаемые операции:
Поэлементное сложение: v1 + v2

Поэлементное вычитание: v1 - v2

Умножение на скаляр: v * 3, 3 * v

Деление на скаляр: v / 2

Ограничения:
Векторы должны быть одинакового размера для арифметических операций

Запрещено деление на ноль

Проверка границ при доступе к элементам

Использование
Создание векторов:
cpp
Vector<int> v1; // Пустой вектор
Vector<double> v2(10); // Вектор из 10 элементов
Vector<std::string> v3 = {"hello", "world"}; // Инициализация списком
Добавление элементов:
cpp
Vector<int> v;
v.pushBack(1);
v.pushBack(2);
v.pushBack(3);
Математические операции:
cpp
Vector<int> a = {1, 2, 3};
Vector<int> b = {4, 5, 6};
Vector<int> sum = a + b; // {5, 7, 9}
Vector<int> scaled = a * 2; // {2, 4, 6}
Использование итераторов:
cpp
Vector<int> v = {1, 2, 3, 4, 5};

// Range-based for loop
for (const auto& item : v) {
    std::cout << item << " ";
}

// Ручное использование итераторов
for (auto it = v.begin(); it != v.end(); ++it) {
    *it *= 2; // Умножаем каждый элемент на 2
}
Тестирование
Проект использует Google Test для модульного тестирования. Тесты покрывают:

Конструкторы - default, copy, move, initializer_list

Доступ к элементам - оператор [], getElem, setElem

Арифметические операции - сложение, вычитание, умножение, деление

Итераторы - обход элементов, изменение значений

Граничные случаи - пустой вектор, выход за границы

Запуск тестов:
bash
qmake OOP_lab2.pro
make
./OOP_lab2
Особенности реализации
Безопасность:
Проверка границ при доступе к элементам

Исключения при недопустимых операциях

Защита от деления на ноль

Производительность:
Move-семантика для избежания лишних копирований

Оптимальное изменение capacity (удвоение при необходимости)

Inline методы для часто используемых операций

Совместимость:
Поддержка C++17 стандарта

Совместимость с STL-алгоритмами через итераторы

Поддержка range-based for loops

Требования
C++17 или новее

Google Test для тестирования

Компилятор с поддержкой C++17

Сборка
С помощью qmake:
bash
qmake OOP_lab2.pro
make
Прямая компиляция:
bash
g++ -std=c++17 -I. -Igtest/include main.cpp testvector.cpp -lgtest -lgtest_main -lpthread -o vector_test
