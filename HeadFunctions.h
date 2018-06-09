#pragma once
#include <fstream>
#include <string>
#include <deque>

/*заполнения текстового файла N целыми случайными числами в диапазоне от -M до M.
Имя файла, N и M поступают на вход функции, файл возвращается функцией как результат
Реализовать два варианта генерации чисел — в цикле и с использованием алгоритма
std::generate*/
std::fstream* RandomNumsCycle(std::string filename, int M, int N);
std::fstream* RandomNumsGenerate(std::string filename, int M, int N);

/*Функцию, получающую файл на вход, и возвращающую
последовательный контейнер, заполненный числами из файла.*/
std::deque<int> DequeFromFile(std::fstream *file);

/*Функцию modify, выполняющую преобразование полученного контейнера.
На вход функции должен поступать контейнер, в качестве результата функция должна 
возвращать модифицированный контейнер.*/
std::deque<int> Modify(std::deque<int> q, int k);

/*Перегруженную функцию modify, принимающую на вход итераторы 
начала и конца обрабатываемой части контейнера.*/
std::deque<int> Modify(std::deque<int>::iterator begin, std::deque<int>::iterator end, int k);

/*Функцию, реализующую требуемое преобразование с использованием 
алгоритма std::transform вместо функции modify.*/
void ModifyTransform(std::deque<int> &q, int k);

/*Функцию, реализующую требуемое преобразование 
с использованием алгоритма std::for_each вместо функции modify.*/
void ModifyForEach(std::deque<int> &q, int k);

/*Функции, вычисляющие сумму и среднее арифметическое чисел, содержащихся в контейнере.*/
int Sum(std::deque<int> q);
double ArithmeticMean(std::deque<int> q);

/*Функцию вывода результата в файл и на экран */
void Print(std::deque<int> q);
bool SaveToFile(std::deque<int> q, std::string filename);
