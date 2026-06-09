# adownloader

Консольное приложение. Загрузка файлов по URL.

Используется стандарт C++ 17

Разрабатывался и проверялся на Windows, Visual Studio 2022, MSVC.(https://visualstudio.microsoft.com)

Cmake был скачан в Visual Studio, использовалась версия 3.20+(https://cmake.org),(https://cmake.org/cmake/help/latest/guide/tutorial/index.html).

git(https://git-scm.com/install/)

#Используемые библиотеки

-Стандартные библиотеки:
iostream - ввод вывод
string - строки
ctime - используется для получения локального времени
chrono - используется для получения миллисекунд
fstream - чтение и запись файлов

https://en.cppreference.com/cpp/header

-Boost
Был установлен с помощью vcpkg командой "vcpkg install boost:x64-windows"(https://github.com/microsoft/vcpkg), 
который в свою очередь был установлен командой git clone https://github.com/microsoft/vcpkg в git.

После установки были доступны Boost.Asio и Boost.Beast.

https://www.boost.org/

Использовался код из примера на сайте (https://www.boost.org/doc/libs/latest/libs/beast/doc/html/beast/quick_start/http_client.html)

#Программа и примеры

Проект собирался через CMake.

В Powershell visual studio подавалась команда ".\out\build\x64-Debug\adownloader.exe urls.txt dwnlds 999"

В консоли писалось:
time:21:39:30:278 programm start
time:21:39:30:279 downloading http://bolid.ru/favicon.ico
protocol = http
host = bolid.ru
target = /favicon.ico
filename = favicon.ico
time:21:39:30:469 server code isnt 200: 301
time:21:39:30:470 downloading http://bolid.ru/bld/images/logo.png
host = bolid.ru
target = /bld/images/logo.png
filename = logo.png
time:21:39:30:862 server code isnt 200: 301
time:21:39:30:862 downloading http://example.com/
protocol = http
host = example.com
target = /
filename = file
time:21:39:31:38 downloading http://neverssl.com/
protocol = http
host = neverssl.com
target = /
filename = file
time:21:39:52:797 downloading endedfile
time:21:39:52:798 downloading http://www.google.com/robots.txt
protocol = http
host = www.google.com
filename = robots.txt
time:21:39:52:956 downloading endedrobots.txt
time:21:39:52:957 programm end

Создавались 2 файла: file(пустой) и robots.txt с текстом.

#Файлы и каталоги

dwnlds - каталог где создаются файлы и куда загружается информация с url
src - каталог с файлом main.cpp где содержится основной код
.gitignore
CmakeLists.txt - файл конфигурации Cmake
README.md - файл с описанием программы
urls.txt - файл с url с которых мы и скачиваем нужные данные.

#Что реализовано в программе

-чтение параметров командной строки
-открытие файлов(urls) и помещение содержимого в массив
-парсинг URL
-отправка HTTP GET запроса
-получение ответа
-сохранение ответа в файл
-вывод информации в консоль c указанным временем с точностью до миллисекунд