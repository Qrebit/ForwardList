#pragma once

template<typename T>
class ForwardList
{
	Element<T>* Head;
	int size;
public:
	Iterator<T> getHead() {
		return Head;
	}
	Iterator<T> begin() {
		return Head;
	}
	Iterator<T> end() {
		return nullptr;
	}
	ForwardList()
	{
		Head = nullptr;
		size = 0;
	}
	ForwardList(initializer_list<T> il) :ForwardList() {
		cout << typeid(il.begin()).name() << endl;
		for (T const* it = il.begin(); it != il.end(); it++) {
			push_back(*it);
		}
	}
	ForwardList(const ForwardList<T>& other) {
		Element* Temp = other.Head;
		while (Temp) {
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
	}
	~ForwardList()
	{
		while (Head) {
			pop_front();
		}
	}

	//			Adding elements:
	void push_front(T Data)
	{
		Head = new Element<T>(Data, Head);
		size++;
	}
	void push_back(T Data)
	{
		if (Head == nullptr) push_front(Data);
		else
		{
			Element<T>* Temp = Head;	//Temp - это итератор.
			while (Temp->pNext != nullptr) Temp = Temp->pNext;
			Temp->pNext = new Element<T>(Data);
		}
		size++;
	}

	void insert(T Data, int index) {
		if (index == 0) push_front(Data);
		else {
			Element<T>* Temp = Head;
			for (int i = 0; i < index - 1; i++) Temp = Temp->pNext;
			Temp->pNext = new Element<T>(Data, Temp->pNext);
		}
		size++;
	}
	//Erasing Elements
	void pop_front()
	{
		Element<T>* Temp = Head;
		Head = Head->pNext;
		delete Temp;
		size--;
	}
	void pop_back()
	{
		Element<T>* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}
	void erase(int index)
	{
		if (index == 0) pop_front();
		else {
			Element<T>* Temp = Head;
			for (int i = 0; i < index - 1; i++) Temp = Temp->pNext;
			Element<T>* Add = Temp->pNext;
			Temp->pNext = Temp->pNext->pNext;
			delete Add;
		}
		size--;
	}
	ForwardList<T>& operator=(const ForwardList<T>& other) {
		while (Head)pop_front();
		Element<T>* Temp = other.Head;
		while (Temp) {
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		return *this;
	}

	//			Methods:
	void print()
	{
		for (Iterator<T> Temp = Head; Temp != nullptr; Temp++) cout << *Temp << tab;
		cout << endl;
		cout << "Кол-Во элементов -" << size << endl;
		cout << "Общее Кол-Во элементов -" << Element<T>::count << endl;
	}
};
