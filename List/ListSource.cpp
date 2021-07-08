#pragma warning(disable:4326)
#include<iostream>
#include"ClassParts.h"
using namespace std;
using std::cin;
using std::cout;
using std::endl;

void main()
{
	setlocale(LC_ALL, "Russian");
	List<int> list = { 1,2,3,4,5 };
	list.print();
}