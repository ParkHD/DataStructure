#pragma once
#include <assert.h>

template<typename T>
class Node							// c++자기자신을 참조를 못하나유 ㅠ
{
	template<typename T>
	friend class Iterator;
	template<typename T>
	friend class Reverse_Iterator;
	template<typename T>
	friend class DoubleList;
public:
	Node()
	{
		m_pNext = nullptr;
		m_pPrev = nullptr;
	}
	~Node()
	{

	}
private:
	Node<T>* m_pNext;
	Node<T>* m_pPrev;
	T		 value;
};

template<typename T>
class Iterator
{
	template<typename T>
	friend class DoubleList;

public:
	Iterator()
	{
		m_pNode = nullptr;
	}
	~Iterator()
	{

	}
private:
	Node<T>* m_pNode;
public:
	bool operator ==(const Iterator<T>& iter)
	{
		return m_pNode == iter.m_pNode;
	}
	bool operator !=(const Iterator<T>& iter)
	{
		return m_pNode != iter.m_pNode;
	}
	void operator ++()
	{
		m_pNode = m_pNode->m_pNext;
	}
	void operator --()
	{
		m_pNode = m_pNode->m_pPrev;
	}
	T operator *()
	{
		return m_pNode->value;
	}
};
template<typename T>
class Reverse_Iterator
{
public :
	Reverse_Iterator()
	{
		m_pNode = nullptr;
	}
private:
	Node<T>* m_pNode;
public:
	bool operator ==(const Reverse_Iterator iter)
	{
		return m_pNode == iter.m_pNode;
	}
	bool operator !=(const Reverse_Iterator iter)
	{
		return m_pNode != iter.m_pNode;
	}
	void operator ++()
	{
		m_pNode = m_pNode->m_pPrev;
	}
	void operator --()
	{
		m_pNode = m_pNode->m_pNext;
	}	
	T operator *()
	{
		return m_pNode->value;
	}
};

template<typename T>
class DoubleList
{
public:
	DoubleList()
	{
		head = new Node<T>;
		tail = new Node<T>;
		tail->m_pPrev = head;
		head->m_pNext = tail;

		m_size = 0;
	}
public:
	typedef Iterator<T> iterator;
	typedef Reverse_Iterator<T> reverse_iterator;
private:
	Node<T>* head;
	Node<T>* tail;
	int		 m_size;
public:
	void push_back(T value)
	{
		Node<T>* newNode = new Node<T>;
		newNode->value = value;
		Node<T>* preNode = tail->m_pPrev;

		preNode->m_pNext = newNode;
		newNode->m_pPrev = preNode;
		newNode->m_pNext = tail;
		tail->m_pPrev = newNode;

		m_size++;
	}
	void push_front(T value)
	{
		Node<T>* newNode = new Node<T>;
		newNode->value = value;
		Node<T>* nextNode = head->m_pNext;

		newNode->m_pNext = nextNode;
		nextNode->m_pPrev = newNode;
		head->m_pNext = newNode;
		newNode->m_pPrev = head;

		m_size++;
	}
	T pop_back()
	{
		if (empty())
		{
			assert(false);
		}
		Node<T>* deleteNode = tail->m_pPrev;
		T value = deleteNode->value;

		deleteNode->m_pPrev->m_pNext = tail;
		tail->m_pPrev = deleteNode->m_pPrev;

		delete deleteNode;
		m_size--;
		return value;
	}
	T pop_front()
	{
		if (empty())
		{
			assert(false);
		}
		Node<T>* deleteNode = head->m_pNext;
		T value = deleteNode->value;

		deleteNode->m_pNext->m_pPrev = head;
		head->m_pNext = deleteNode->m_pNext;

		delete deleteNode;
		m_size--;
		return value;
	}
	void clear()
	{
		Node<T>* deleteNode = head->m_pNext;
		while (deleteNode != tail)
		{
			Node<T>* nextNode = deleteNode->m_pNext;
			delete deleteNode;
			deleteNode = nextNode;
		}
		m_size = 0;
		head->m_pNext = tail;
		tail->m_pPrev = head;
	}
public:
	iterator begin()
	{
		iterator iter;
		iter.m_pNode = head->m_pNext;
		return iter;
	}
	iterator end()
	{
		iterator iter;
		iter.m_pNode = tail;
		return iter;
	}
	reverse_iterator rbegin()
	{
		reverse_iterator iter;
		iter.m_pNode = tail->m_pPrev;
		return iter;
	}
	reverse_iterator rend()
	{
		iterator iter;
		iter.m_pNode = head;
		return iter;
	}
public:
	int size() const
	{
		return m_size;
	}
	bool empty() const
	{
		return m_size <= 0;
	}
	void sort(bool (*Func)(const T&, const T&))
	{
		iterator iter;
		iterator end_iter = end();
		--end_iter;
		for (iter = begin(); iter != end_iter; ++iter)
		{
			iterator iter1 = iter;
			++iter1;
			iterator end_iter1 = end();
			for (; iter1 != end_iter1; ++iter1)
			{
				if (Func(iter.m_pNode->value, iter1.m_pNode->value))
				{
					T temp = iter.m_pNode->value;
					iter.m_pNode->value = iter1.m_pNode->value;
					iter1.m_pNode->value = temp;
				}
			}
		}
	}
						
};