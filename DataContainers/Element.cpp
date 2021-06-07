#include "Element.h"
template<typename T>
int Element<T>::count = 0; // Static инициализация

template<typename T>
Element<T>::Element(T Data, Element<T>* pNext) :Data(Data), pNext(pNext) {
	count++;
}
template<typename T>
Element<T>::~Element() {
	count--;
}