![Calc CI](https://github.com/itiviti-cpp-master/calc-trig/workflows/Calc%20CI/badge.svg)
# Простой калькулятор
Поддерживаются базовые арифметические операции и ввод десятичных чисел.
Операции производятся над значением из единственного регистра (он же - приёмник результата) и, если операция бинарная, вторым
операндом, вводимым после оператора.

## Ограничения
Размер вводимых чисел ограничен 10 десятичными цифрами.

## Операции
* сложение `+`
* вычитание `-`
* умножение `*`
* деление `/`
* остаток от деления `%`
* инвертирование знака `_`
* возведение в степень `^`
* квадратный корень `SQRT`

## Пользовательский интерфейс
Пользовательский ввод построчно читается из стандартного ввода, в каждой строке ожидается одна операция:
```
op [arg]
```
Результат каждой операции выводится в стандартный вывод, сообщения об ошибках - в стандартный вывод ошибок.

# Поддержка тригонометрических функций с выбором режима в калькуляторе
## Задание
Требуется расширить реализацию калькулятора для поддержки ряда новых операций:
* синус
* косинус
* тангенс
* котангенс
* арксинус
* арккосинус
* арктангенс
* арккотангенс

При этом предоставить пользователю выбор режима вычислений - в радианах или градусах. Выбор режима должен осуществляться командами
* `RAD` - радианы
* `DEG` - градусы

Программный интерфейс расширяется по сравнению с исходным калькулятором:
```
double process_line(double current, bool & rad_on, const std::string & line);
```

Если `rad_on` имеет значение `true` - это режим радианов, если `false` - режим градусов. При смене режима нужно присвоить новое значение переменной `rad_on`.

Для реализации тригонометрических функций стоит воспользоваться стандартной библиотекой, в частности, функциями из `cmath` (https://en.cppreference.com/w/cpp/numeric/math).

## Синтаксис
* `SIN` - операция синуса над значением регистра
* `COS` - операция косинуса над значением регистра
* `TAN` - операция тангенса над значением регистра
* `CTN` - операция котангенса над значением регистра
* `ASIN` - операция арксинуса над значением регистра
* `ACOS` - операция арккосинуса над значением регистра
* `ATAN` - операция арктангенса над значением регистра
* `ACTN` - операция арккотангенса над значением регистра
* `RAD` - включение режима радианов
* `DEG` - включение режима градусов

## Индикация ошибок
Если в регистре содержится значение, недопустимое в качестве аргумента для какой-либо тригонометрической функции, нужно записать в `std::cerr` ошибку и не менять регистр:
```
Bad argument for ASIN: xxx
```