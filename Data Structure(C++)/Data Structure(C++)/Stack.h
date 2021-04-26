#pragma once
#include <iostream>

template<typename T>
class SNode
{
	template<typename T>
	friend class Stack;
public :
	SNode()
	{
		m_pNext = nullptr;
	}
	~SNode()
	{

	}
private:
	T m_value;
	SNode<T>* m_pNext;
};

template<typename T>
class Stack
{
public:
	Stack()
	{
		top = new SNode<T>;
		m_size = 0;
	}
	~Stack()
	{

	}
public:
	void push(T value)
	{
		SNode<T>* newNode = new SNode<T>;
		newNode->m_value = value;

		newNode->m_pNext = top->m_pNext;
		top->m_pNext = newNode;
		m_size++;
	}
	T pop()
	{
		SNode<T>* deleteNode = top->m_pNext;
		T output = deleteNode->m_value;
		top->m_pNext = deleteNode->m_pNext;
		delete deleteNode;
		m_size--;
		return output;
	}
	void clear()
	{
		SNode<T>* deleteNode;
		while (top->m_pNext)
		{
			deleteNode = top->m_pNext;
			top->m_pNext = deleteNode->m_pNext;

			delete deleteNode;
		}
		m_size = 0;
	}
public:
	int size() const
	{
		return m_size;
	}
	bool empty()
	{
		return m_size <= 0;
	}
private:
	SNode<T>* top;
	int m_size;
};


template<typename T, int SIZE = 100>
class CStackArray
{
public :
	CStackArray()
	{
		m_iCapacity = SIZE;
		m_iSize = 0;
		m_pArray = new T[m_iCapacity];
	}
	~CStackArray()
	{
		delete[] m_pArray;
	}
private:
	T* m_pArray;
	int m_iSize;
	int m_iCapacity;
public:
	void push(const T& data)
	{
		if (empty())
		{
			m_iCapacity *= 2;
			T* pArray = new T[m_iCapacity];

			memcpy(pArray, m_pArray, sizeof(T) * m_iSize);
			// 다 돌려서 넣는것보다 이게 더 효율적이다
			// 1인자에 2번째 있는 메모리를 사이즈(3번째인자)만큼 복사한다.

			delete[] m_pArray;
			m_pArray = pArray;
		}
		m_pArray[m_iSize] = data;
		m_iSize++;
	}
	T top() const
	{
		if (empty())
		{
			assert(false);
		}
		return m_pArray[m_iSize - 1];
	}
	T pop()
	{
		if (empty())
		{
			assert(false);
		}
		T output = m_pArray[m_iSize - 1];
		m_iSize--;

		return output;
	}
	void clear()
	{
		m_iSize = 0;
	}
	bool empty() const
	{
		return m_iSize == 0;
	}
	bool full() const
	{
		return m_iSize == m_iCapacity;
	}
	int size() const
	{
		return m_iSize;
	}
	int capacity() const
	{
		return m_iCapacity;
	}
};