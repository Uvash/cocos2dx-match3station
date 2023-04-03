# match 3 station
## Описание
Игра представляет модификацию игры три в ряд
Основные отличия
- Необходимость поддерживать все три параметра станции выше нуля.
- Обмен фигурок возможен на любой дистанции.
- После каждого хода, один из трёх параметров случайно теряет очки
- Успешная комбинация востанавливает очки в зависимости от уничтоженных фигурок

## Установка
### windows
Предполагаеться, что на компьютере уже установлен cocos2d и прописанны нужные ему пути.
После скачивания репозитория, сгенерируйте новый **.sln** из папки **proj.win32** с помощью cmake. 
```sh
<корень проекта>\match3station\proj.win32 cmake .. -G"Visual Studio 17 2022" -Tv143 -Awin32
```
После необходимо добавить статические библиотеки **.lib**
Есть два варианта:
- Взять откомпилированные библиотеки из [репозитория](https://github.com/cocos2d/cocos2d-x-3rd-party-libs-bin/tree/v4) кокоса
-  Собрать самомоу. Исходники лежат внутри проекта, в теории с помощью cmake создать проект студии и откомпилировать (студия может затребовать библиотеки для линукса)

Помещаем папку с библиотеками в
```sh
<корень проекта>\match3station\cocos2d\external
```
Пример путь до **libbox2d.lib** в варианте DEBUG:
```sh
<корень проекта>\match3station\cocos2d\external\Box2D\prebuilt\win32\debug
```
### Android
Сложностей не замечено, андроид студия спокойно подцепляет необходимые ей настройки из проекта.



