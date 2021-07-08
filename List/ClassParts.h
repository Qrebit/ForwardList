#pragma once
#include<iostream>
#include "ClassList.h"
using namespace std;
using std::cin;
using std::cout;
using std::endl;

template<typename T>size_t List<T>::getSize()const
{
	return size;
}

template<typename T>const List<T>::Iterator List<T>::begin()const
{
	return Head;
}
template<typename T>const List<T>::Iterator List<T>::end()const
{
	return nullptr;
}
template<typename T>const List<T>::ReverseIterator List<T>::rbegin()const
{
	return Tail;
}
template<typename T>const List<T>::ReverseIterator List<T>::rend()const
{
	return nullptr;
}
template<typename T>List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T>List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template<typename T>List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template<typename T>List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}

template<typename T>List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
}
template<typename T>List<T>::List(int size) :List()
{
	while (size--)push_back(0);
}
template<typename T>List<T>::List(const initializer_list<T>& il) : List()
{
	cout << typeid(il.begin()).name() << endl;
	for (T const* it = il.begin(); it != il.end(); it++)
		push_back(*it);
}
template<typename T>List<T>::List(const List<T>& other) :List()
{
	Element* Temp = other.Head;
	while (Temp)
	{
		push_back(Temp->Data);
		Temp = Temp->pNext;
	}
}
template<typename T>List<T>::List(List<T>&& other)
{
	this->size = other.size;
	this->Head = other.Head;
	this->Tail = other.Tail;
	other.Head = other.Tail = nullptr;
}
template<typename T>List<T>::~List()
{
	while (Tail)pop_back();
}
//Операторы
template<typename T>T& List<T>::operator[](size_t index)
{
	Element* Temp;
	if (index < size / 2)
	{
		Temp = Head;
		for (size_t i = 0; i < index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (size_t i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;
	}
	return Temp->Data;
}

template<typename T>List<T>& List<T>::operator=(const List<T>& other) {
	if (this == &other)return *this;
	while (Head)pop_front();
	for (T i : other)push_back(i);
}

template<typename T>List<T>& List<T>::operator=(List<T>&& other) {
	while (Head)pop_front();
	this->size = other.size;
	this->Head = other.Head;
	this->Tail = other.Tail;
	other.Head = other.Tail = nullptr;
	return *this;
}
//Добавление
template<typename T> void push_front(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
		size++;
		return;
	}
	Head = Head->pPrev = new Element(Data, Head);
	size++;
}
template<typename T> void push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
		size++;
		return;
	}
	Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	size++;
}
template<typename T> void insert(unsigned int Index, T Data)
{
	if (Index > size)return;
	if (Index == 0)
	{
		push_front(Data);
		return;
	}
	if (Index == size)
	{
		push_back(Data);
		return;
	}
	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (size_t i = 0; i < Index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (size_t i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
	}
	Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
	size++;
}

//Удаление
template<typename T> void pop_front()
{
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
		size--;
		return;
	}
	Head = Head->pNext;
	delete Head->pPrev;
	Head->pPrev = nullptr;
	size--;
}
template<typename T> void pop_back()
{
	if (Head == Tail)
	{
		delete Tail;
		Head = Tail = nullptr;
		size--;
		return;
	}
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	size--;
}
template<typename T> void erase(size_t index)
{
	if (index == 0)
	{
		pop_front();
		return;
	}
	if (index == size - 1)
	{
		pop_back();
		return;
	}
	if (index >= size)return;

	Element* Temp;
	if (index < size / 2)
	{
		Temp = Head;
		for (size_t i = 0; i < index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (size_t i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;
	}
	Temp->pPrev->pNext = Temp->pNext;
	Temp->pNext->pPrev = Temp->pPrev;
	delete Temp;
}

//Методы
template<typename T> void print()
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
	{
		cout << Temp << tab << Temp->pPrev << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	cout << "Количество элементов списка: " << size << endl;
}
template<typename T>List<T> print_reverse()
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp << tab << Temp->pPrev << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов списка: " << size << endl;
}

template<typename T>
List<T> operator+(const List<T> left, const List<T> right) {
	List<T> cat = left;
	for (T i : right)cat.push_back(i);
	return cat;
}
