#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include "HeadFunctions.h"

//�������� ���������� �� ������������
void OkIterator(std::deque<int>::iterator begin, std::deque<int>::iterator end, int k)
{
	if (end < begin) {
		throw "��������� �������� ������ ���������";
	}
	if ((end - begin - 1) < k || k < 0) {
		throw "����� �������� ������";
	}
}

//�������� ����� �� ������������
double CheckNumber(int frstminus, int knum) 
{
	if (0 == frstminus) {
		throw "������� �� �������� ������������� ���������";
	}
	double num = ((double)(knum + frstminus) / 2);
	if (0 == num){
		throw "���������� �������� ����� 0";
	}
	return num;
}

/*���������� ���������� ����� N ������ ���������� ������� � ��������� �� -M �� M. 
��� �����, N � M ��������� �� ���� �������, ���� ������������ �������� ��� ���������
����������� ��� �������� ��������� ����� � � ����� � � �������������� ��������� 
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

/*�������, ���������� ���� �� ����, � ������������ ����������������
���������, ����������� ������� �� �����.*/
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

/*������� modify, ����������� �������������� ����������� ����������.
�� ���� ������� ������ ��������� ���������, � �������� ���������� ������� ������ ���������� ���������������� ���������.
*/
std::deque<int> Modify(std::deque<int> q, int k)
{
	if (k >= q.size() || k < 0) {
		throw std::exception("����� �������� ������");
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

/*������������� ������� modify, ����������� �� ���� ��������� ������
� ����� �������������� ����� ����������.*/
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

/*�������, ����������� ��������� �������������� � �������������� 
��������� std::transform ������ ������� modify.*/
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

/*�������, ����������� ��������� �������������� � ��������������
��������� std::for_each ������ ������� modify.*/
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

/*�������, ����������� ����� � ������� �������������� �����, ������������ � ����������.*/
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
		throw "������� �� �������� ���������";
	int sum = 0;
	for (int i = 0; i < count; ++i) {
		sum += q[i];
	}
	return ((double)sum / count);
}

/*������� ������ ���������� � ���� � �� ����� */
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