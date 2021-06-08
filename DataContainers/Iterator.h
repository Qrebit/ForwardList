#pragma once

template<typename T>
class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp = nullptr) {
		this->Temp = Temp;
	}
	~Iterator() {
	}
	Iterator<T>& operator++() {
		Temp = Temp->pNext;
		return *this;
	}
	Iterator<T> operator++(int) {
		Iterator<T> old = *this;
		Temp = Temp->pNext;
		return old;
	}
	bool operator==(const Iterator<T>& other)const {
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator<T>& other)const {
		return this->Temp != other.Temp;
	}

	Element<T>*& operator->() {
		return Temp;
	}
	Element<T>* get_current_address() {
		return Temp;
	}
	T& operator*() {
		return Temp->Data;
	}
	const T& operator*()const {
		return Temp->Data;
	}
};