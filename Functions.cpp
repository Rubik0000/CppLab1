#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include "HeadFunctions.h"

//проверка итераторов на корректность
void OkIterator(std::deque<int>::iterator begin, std::deque<int>::iterator end, int k)
{
	if (end < begin) {
		throw "Начальный итератор больше конечного";
	}
	if ((end - begin - 1) < k || k < 0) {
		throw "Задан неверный индекс";
	}
}

//проверка чисел на корректность
double CheckNumber(int frstminus, int knum) 
{
	if (0 == frstminus) {
		throw "Очередь не содержит отрицательных элементов";
	}
	double num = ((double)(knum + frstminus) / 2);
	if (0 == num){
		throw "Полученное значение равно 0";
	}
	return num;
}

/*заполнения текстового файла N целыми случайными числами в диапазоне от -M до M. 
Имя файла, N и M поступают на вход функции, файл возвращается функцией как результат
Реализовать два варианта генерации чисел — в цикле и с использованием алгоритма 
std::generate*/
std::fstream* RandomNumsCycle(std::string filename, int M, int N)
{
	std::fstream *f = new std::fstream();
	(*f).open(filename, std::fstream::out);
	if (!(*f).is_open()) {
		return nullptr;
	}
	std::srand(std::time(NULL));
	for (int i = 0; i < N; ++i) {
		*f << std::rand() % (2 * M + 1) - M << ' ';
	}
	(*f).close();
	return f;
}

std::fstream* RandomNumsGenerate(std::string filename, int M, int N)
{
	std::fstream *f = new std::fstream();
	(*f).open(filename, std::fstream::out);
	if (!(*f).is_open()) {
		return nullptr;
	}
	std::deque<int> q(N);
	std::srand(std::time(NULL));
	std::generate_n(q.begin(), N, [M]() {return std::rand() % (2 * M) - M; });
	for (int el : q) {
		(*f) << el << ' ';
	}
	q.clear();
	(*f).close();
	return f;
}

/*Функцию, получающую файл на вход, и возвращающую последовательный
контейнер, заполненный числами из файла.*/
std::deque<int> DequeFromFile(std::fstream *file) 
{
	std::deque<int> queue;
	if ((*file).is_open()) {
		int el;
		while (!(*file).eof()) {
			*file >> el;
			queue.push_back(el);
		}
	}
	return queue;

}

/*Функцию modify, выполняющую преобразование полученного контейнера.
На вход функции должен поступать контейнер, в качестве результата функция должна возвращать модифицированный контейнер.
*/
std::deque<int> Modify(std::deque<int> q, int k)
{
	if (k >= q.size() || k < 0) {
		throw std::exception("Задан неверный индекс");
	}
	int firstMinus = 0;
	for (int el : q) {
		if (el < 0) {
			firstMinus = el;
			break;
		}
	}
	double num = CheckNumber(firstMinus, q[k]);
	std::deque<int> newq;
	for (int el : q) {
		newq.push_back(el / num);
	}
	return newq;
}

/*Перегруженную функцию modify, принимающую на вход итераторы начала
и конца обрабатываемой части контейнера.*/
std::deque<int> Modify(std::deque<int>::iterator begin, std::deque<int>::iterator end, int k) {
	OkIterator(begin, end, k);
	int firstMinus = 0, knum, i = 0;
	bool find = false;
	for (auto iter = begin; iter != end; ++iter) {
		if (!find && *iter < 0) {
			find = true;
			firstMinus = *iter;
		}
		if (i == k) {
			knum = *iter;
		}
		++i;
	}
	double num = CheckNumber(firstMinus, knum);
	std::deque<int> newq;
	for (auto iter = begin; iter != end; ++iter) {
		newq.push_back(*iter / num);
	}
	return newq;
}

/*Функцию, реализующую требуемое преобразование с использованием 
алгоритма std::transform вместо функции modify.*/
void ModifyTransform(std::deque<int> &q, int k)
{
	OkIterator(q.begin(), q.end(), k);
	bool find = false;
	int firstMinus = 0, knum, i = 0;
	std::transform(q.begin(), q.end(), q.begin(),
		[&firstMinus, &find, &i, k, &knum](int a) {
			if (!find && a  < 0) {
				find = true;
				firstMinus = a;
			} 
			if (i == k) {
				knum = a;
			}
			++i;
			return a;
		});
	double num = CheckNumber(firstMinus, knum);
	std::transform(q.begin(), q.end(), q.begin(), [num](int a) {return a / num; });
}

/*Функцию, реализующую требуемое преобразование с использованием
алгоритма std::for_each вместо функции modify.*/
void ModifyForEach(std::deque<int> &q, int k)
{
	OkIterator(q.begin(), q.end(), k);
	bool find = false;
	int firstMinus = 0, knum, i = 0;
	std::for_each(q.begin(), q.end(),
		[&firstMinus, &find, &i, k, &knum](int a) {
			if (!find && a < 0) {
				find = true;
				firstMinus = a; 
			}
			if (i == k) {
				knum = a;
			}
			++i;
			return a;
		});
	double num = CheckNumber(firstMinus, knum);
	std::for_each(q.begin(), q.end(), [num](int &a) { a /= num; });
}

/*Функции, вычисляющие сумму и среднее арифметическое чисел, содержащихся в контейнере.*/
int Sum(std::deque<int> q)
{
	int sum = 0;
	for (int i = 0; i < q.size(); ++i) {
		sum += (q)[i];
	}
	return sum;
}

double ArithmeticMean(std::deque<int> q)
{
	int count = q.size();
	if (0 == count)
		throw "Очередь не содержит элементов";
	int sum = 0;
	for (int i = 0; i < count; ++i) {
		sum += q[i];
	}
	return ((double)sum / count);
}

/*Функцию вывода результата в файл и на экран */
void Print(std::deque<int> q)
{
	for (int i = 0; i < q.size(); ++i) {
		std::cout << q[i] << ' ';
	}
}

bool SaveToFile(std::deque<int> q, std::string filename)
{
	std::fstream f;
	f.open(filename, std::fstream::out);
	if (!f.is_open())
		return false;
	for (int i = 0; i < q.size(); ++i) {
		f << q[i] << ' ';
	}
	f.close();
	return true;
}