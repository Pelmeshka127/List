# List Implementation
Двусвязный список – это структура данных, состоящая из последовательности элементов, каждый из которых содержит какое-либо значение и два указателя на соседние элементы.
В данном проекте реализованы две стуркутры: список на индексах и список на указателях. Для визуального представления используется graphviz.

## Запуск Проекта ##

В терминале введите

```
make

./list

```

## Список на индексах ##
``` C
/// Структура узла списка
struct list_node {
    elem_t data; /// значение
    int next;    /// индекс следующего  узла
    int prev;    /// индекс предыдущего узла
};

/// Структура списка
struct list_s {
    int capacity; /// максимальное количесвто элементов
    int size;     /// размер списка
    int head;     /// индекс "головы" списка
    int tail;     /// индекс "хвоста" списка
    int free;     /// индекс наименьшего свободного узла
    list_node *node; /// массив узлов списка
    int error;       /// код ошибки
    bool is_sorted;  /// состояние списка
};
```

Для работы с этим списком присутствуют следующие функции

```C
/// Инициализация списка
int List_Ctor(list_s * const header, int Capacity);

/// Вставка нового узла в конец списка
int List_Insert_Front(list_s * const header, elem_t value);

/// Встака нового узла в начало списка
int List_Insert_Back(list_s * const header, elem_t value);

/// Вставка новго узла после данного узла
int List_Insert_After(list_s * const header, int index, elem_t value);

/// Вставка новго узла перед данным узлом
int List_Insert_Before(list_s * const header, int index, elem_t value);

/// Удаление узла
int List_Erase_Node(list_s * const header, int index);

/// Изменеие размера списка
int List_Realloc(list_s * const header, int mode);

/// Сортировка списка по логическим индексам
int List_Linearize(list_s * const header);

/// Удаление списка
void List_Dtor(list_s * const header);
```
Одна из сновных задач при написании этого проекта - научиться пользоваться графической библиотекой graphviz.

Вот визульное представление списка

![image](https://github.com/Pelmeshka127/List/raw/main/List_On_Idexes/graphics/gpaph6.png)

Таким образом, мы можем в любой момент наблюдать за состоянием нашего списка, чтобы его отладка происходила удобнее и быстрее.

