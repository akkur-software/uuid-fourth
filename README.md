### uuid-fourth

**uuid-fourth** - это статическая open-source библиотека, предоставляющая основной функционал для работы с универсальными уникальными идентификаторами (UUID) версии 4 - генерацию, хранение и парсинг.

Идентификатор представляет собой 128-битное число.

#### Генерация UUID

Библиотека предоставляет два способа создания экземпляра *Uuid* - рандомная генерация и создание на основе существующего экземпляра UUID.

В первом случае создается экземпляр с полностью рандомным значением:

```c++
auto uuid = Uuid();
```

Во втором случае, необходимо передать в конструктор ссылку на ранее созданный экземпляр Uuid, либо его значение (массив из 16 байтов):

```c++
auto sourceUuid = Uuid();
...
auto uuidBySource = Uuid(sourceUuid);
auto uuidBySourceValue = Uuid(sourceUuid.Value());
```

#### Хранение

Экземпляр Uuid является неизменяемым, и сохраняет свое значение и строковое представление на всем протяжении жизни.

Для получения значения, используется метод `Value()`, а для получения строкового представления - метод `ToString()`.

```c++
auto uuid = Uuid(); 
auto uuidValue = uuid.Value(); // массив из 16 байтов
auto uuidString = uuid.ToString(); // строковое представление
```

#### Парсинг

Для парсинга строки, содержащей UUID, необходимо вызвать статический метод `Parse(std::string_view)`:

```c++
auto sourceString = "3422b448-2460-4fd2-9183-8000de6f8343";
auto uuid = Uuid::Parse(sourceString);
auto resultString = uuid.ToString(); // 3422b448-2460-4fd2-9183-8000de6f8343
```



#### Приятного пользования!