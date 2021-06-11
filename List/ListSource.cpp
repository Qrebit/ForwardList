#pragma warning(disable:4326)
#include<iostream>

using namespace std;

#define tab "\t"

class List 
{
	class Element 
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) {
			this->Data = Data;
			this->pNext = pNext;
			this->pPrev = pPrev;
			cout << "ECons:\t" << this << endl;
		}
		~Element() 
		{
			cout << "EDest:\t" << this << endl;
		}
		friend class List;
	};
	Element* Head;
	Element* Tail;
	unsigned int size;

	class BaseIterator {
	protected:
		Element* Temp;
	public:
		BaseIterator(Element* Temp = nullptr) :Temp(Temp) {
		}
		~BaseIterator() {
		}
		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};
public:
	class Iterator:BaseIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :BaseIterator(Temp) {
		}
		~Iterator() {
		}

		Iterator& operator++() {
			Temp = Temp->pNext;
			return *this;
		}
		Iterator  operator++(int) {
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		Iterator& operator--() {
			Temp = Temp->pPrev;
			return *this;
		}
		Iterator  operator--(int) {
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		bool operator==(const Iterator& other)const {
			return this->Temp == other.Temp;
		}
		bool operator!=(const Iterator& other)const {
			return this->Temp != other.Temp;
		}

	};
	class ReverseIterator:public BaseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) :BaseIterator(Temp) 
		{
		}
		~ReverseIterator() 
		{
		}

		ReverseIterator& operator--() {
			Temp = Temp->pNext;
			return *this;
		}
		ReverseIterator  operator--(int) {
			ReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		ReverseIterator& operator++() {
			Temp = Temp->pPrev;
			return *this;
		}
		ReverseIterator  operator++(int) {
			ReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		bool operator==(const ReverseIterator& other)const {
			return this->Temp == other.Temp;
		}
		bool operator!=(const ReverseIterator& other)const {
			return this->Temp != other.Temp;
		}
	};
	Iterator begin() {
		return Head;
	}
	Iterator end() {
		return nullptr;
	}
	ReverseIterator rbegin() {
		return Tail;
	}
	ReverseIterator rend() {
		return nullptr;
	}

	List() {
		Head = Tail = nullptr;
		size = 0;
		cout << "LCons:\t" << this << endl;
	}
	List(initializer_list<int> il) :List() {
		for (int const* it = il.begin(); it != il.end(); it++) push_back(*it);
	}
	explicit List(size_t size) :List() {
		while (size--) push_front(0);
		cout << "Size LCons:\t" << this << endl;
	}
	~List() {
		while (Head)pop_front();
		cout << "LDest:\t" << this << endl;
	}

	//Operators

	int& operator[](int index) {
		Element* Temp;
		if (index < size / 2) {
			Temp = Head;
			for (size_t i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else {
			Temp = Tail;
			for (size_t i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;
		}
		return Temp->Data;
	}

	//Adding
	void push_front(int Data) {
		if (Head == nullptr and Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		else
		{
			Head = Head->pPrev = new Element(Data, Head);
			size++;
		}
	}
	void push_back(int Data) {
		if (Head == nullptr and Tail == nullptr) {
			push_front(Data);
			return;
		}
		else
		{
			Tail = Tail->pNext = new Element(Data, nullptr, Tail);
			size++;
		}
	}

	void insert(unsigned int index, int Data) {
		if (index > size)return;
		if (index == 0) {
			push_front(Data);
			return;
		}
		if (index == size) {
			push_back(Data);
			return;
		}
		Element* Temp;
		if (index < size / 2) {
			Temp = Head;
			for (size_t i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else {
			Temp = Tail;
			for (size_t i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;
		}
		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
		size++;
	}
	
	//Erasing

	void pop_front() {
		if (Head == Tail) {
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

	void pop_back() {
		if (Head == Tail) {
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
	
	void erase(int index) {
		if (index == 0) {
			pop_front();
			return;
		}
		if (index >= size)return;
		if (index == size - 1) {
			pop_back();
			return;
		}
		Element* Temp;
		if (index <= size / 2) {
			Temp = Head;
			for (size_t i = 0; i < index; i++) {
				Temp = Temp-> pNext;
			}
		}
		else {
			Temp = Tail;
			for (size_t i = 0; i < size - index - 1; i++) {
				Temp = Temp->pPrev;
			}
		}
		Temp->pNext->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = Temp->pNext;
		delete Temp;
	}

	void print() {
		for (Element* Temp = Head; Temp; Temp = Temp->pNext) {
			cout << Temp << tab << Temp->pPrev << tab << Temp->Data << tab <<  Temp->pNext << endl;
		}
		cout << "Количество элементов списка:" << size << endl;
	}
	void print_reverse() {
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev) {
			cout << Temp << tab << Temp->pPrev << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Количество элементов списка:" << size << endl;
	}
	


};

void main() {
	setlocale(LC_ALL, "Russian");
	List list = { 3,5,8,13 };
	for (List::ReverseIterator It = list.rbegin(); It != list.rend(); It++) 
		cout << *It << tab;
	cout << endl;

}