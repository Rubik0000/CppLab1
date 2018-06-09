#pragma once
#include <fstream>
#include <string>
#include <deque>

/*���������� ���������� ����� N ������ ���������� ������� � ��������� �� -M �� M.
��� �����, N � M ��������� �� ���� �������, ���� ������������ �������� ��� ���������
����������� ��� �������� ��������� ����� � � ����� � � �������������� ���������
std::generate*/
std::fstream* RandomNumsCycle(std::string filename, int M, int N);
std::fstream* RandomNumsGenerate(std::string filename, int M, int N);

/*�������, ���������� ���� �� ����, � ������������
���������������� ���������, ����������� ������� �� �����.*/
std::deque<int> DequeFromFile(std::fstream *file);

/*������� modify, ����������� �������������� ����������� ����������.
�� ���� ������� ������ ��������� ���������, � �������� ���������� ������� ������ 
���������� ���������������� ���������.*/
std::deque<int> Modify(std::deque<int> q, int k);

/*������������� ������� modify, ����������� �� ���� ��������� 
������ � ����� �������������� ����� ����������.*/
std::deque<int> Modify(std::deque<int>::iterator begin, std::deque<int>::iterator end, int k);

/*�������, ����������� ��������� �������������� � �������������� 
��������� std::transform ������ ������� modify.*/
void ModifyTransform(std::deque<int> &q, int k);

/*�������, ����������� ��������� �������������� 
� �������������� ��������� std::for_each ������ ������� modify.*/
void ModifyForEach(std::deque<int> &q, int k);

/*�������, ����������� ����� � ������� �������������� �����, ������������ � ����������.*/
int Sum(std::deque<int> q);
double ArithmeticMean(std::deque<int> q);

/*������� ������ ���������� � ���� � �� ����� */
void Print(std::deque<int> q);
bool SaveToFile(std::deque<int> q, std::string filename);
