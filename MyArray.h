#pragma once
#include <iostream>

using namespace std;

constexpr auto PAGE_SIZE = 5;
constexpr auto MAX_ELEM_PER_PAGE(size_t tsize) { return (tsize / PAGE_SIZE + 1) * PAGE_SIZE; }

template <class T>
class MyVector
{
private:
	T* array_buffer;
	size_t size;
public:
	//Конструкторы
	MyVector();
	MyVector(const size_t size);
	// Копирование
	MyVector(const MyVector& obj);
	MyVector<T>& operator= (const MyVector<T>& obj); //сдеать через указатели? проверка на достаточное количество памяти, либ новая страница
	// Перенос
	MyVector(const MyVector&& obj);
	MyVector<T>& operator= (MyVector<T>&& obj);

	MyVector<T>& operator+= (MyVector<T>& obj);
	T operator[](size_t count);

	bool empty() const; // Проверяет заполнен ли вектор.
	const size_t csize() const; // Возвращает количество данных.
	size_t max_size() const; // Возвращает количество данных до перевыделения памяти. сколько фактически выделенно памяти
	void resize(const size_t size); // Изменяет размер массива и данных.
	void erase(); // Очищает данные из массива. способ создания нового массива
	void swap(MyVector<T>& obj); // Обменивает данные в объектах.

	void push_back(const T& data); // Добавления нового элемента в конец вектора
	void pop_back(); // Удалить последний элемент

	void push_front(const T& data); // Добавления нового элемента в начало вектора
	void pop_front(); // Удалить первый элемент

	// Оператор потока
	template <class U>
	friend std::ostream& operator<< (std::ostream& os, const MyVector<U>& obj);

	~MyVector(); // Деструктор
};

template<class T>
inline MyVector<T>::~MyVector()
{
	delete[] this->array_buffer;
}

template<class U>
inline std::ostream& operator<<(std::ostream& os, const MyVector<U>& obj)
{
	for (int i = 0; i < obj.size; i++)
		os << obj.array_buffer[i];
	return os;
}

template<class T>
inline MyVector<T>::MyVector()
{
	std::array<T> array_buffer;
}

template<class T>
inline MyVector<T>::MyVector(const size_t size)
{
	std::array<T, MAX_ELEM_PER_PAGE(size)> array_buffer;
}

template<class T>
inline bool MyVector<T>::empty() const
{
	if (this->size == 0)
		return true;
	else
		return false;
}

template<class T>
inline const size_t MyVector<T>::csize() const
{
	return this->size;
}
