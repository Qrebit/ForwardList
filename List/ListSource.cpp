#pragma warning(disable:4326)
#include<iostream>
#include"ClassParts.cpp"
using namespace std;
using std::cin;
using std::cout;
using std::endl;

void main()
{
	setlocale(LC_ALL, "Russian");
	List<int> list = { 1,2,3,4,5 };
	list.print();
	List<double> d_list = { 2.5,3.14, 8.3 };
	d_list.print();

	List<string> s_list = { "Hello","World","!" };
	s_list.print();
}