#pragma once
#include<assert.h>

template<typename T>
class CQNode
{
	template<typename T>
	friend class QueueList;
public:
	CQNode()
		:m_pNext(nullptr)
	{

	}
	~CQNode()
	{

	}
private:
	CQNode<T>* m_pNext;
	T		   m_Data;
};

template<typename T>
class QueueList
{
public:
	QueueList()
		: m_pFront(nullptr),
		m_pRear(nullptr),
		m_size(0)
	{
	}
	~QueueList()
	{
		clear();
	}
private:
	typedef CQNode<T> NODE;
	typedef CQNode<T>* PNODE;

private:
	PNODE m_pFront;
	PNODE m_pRear;
	int m_size;
public:
	void push(const T& data)
	{
		PNODE newNode = new NODE;
		newNode->m_Data = data;

		if (m_pRear)
			m_pRear->m_pNext = newNode;
		m_pRear = newNode;

		if (!m_pFront)
			m_pFront = newNode;

		m_size++;
	}
	T front() const
	{
		if (empty())
			assert(false);
		return m_pFront->m_Data;
	}
	T pop()
	{
		if (empty())
			assert(false);

		PNODE nextNode = m_pFront->m_pNext;
		T data = m_pFront->m_Data;
		delete m_pFront;
		m_pFront = nextNode;

		if (!m_pFront)
			m_pRear = nullptr;

		m_size--;
		return data;
	}
	void clear()
	{
		while (m_pFront == nullptr)
		{
			pop();
		}
		m_size = 0;
	}
	bool empty() const
	{
		return m_size <= 0;
	}
	int size() const
	{
		return m_size;
	}
};

template<typename T, int SIZE = 100>
class CircleQueue
{
public:
	CircleQueue() :
		m_size(0),
		m_head(0),
		m_tail(0)
	{

	}
	~CircleQueue()
	{
		clear();
	}
private:
	T	m_Array[SIZE + 1];
	int m_size;
	int m_head;	//rear
	int m_tail; //front
public :
	void push(const T& data)
	{
		if (full())
			assert(false);
		int head = (m_head + 1) % (SIZE + 1);
		m_Array[head] = data;
		m_head = head;

		m_size++;
	}
	T front() const
	{
		if (empty())
			assert(false);
		int tail = (m_tail + 1) % (SIZE + 1);
		return m_Array[tail];
	}
	T pop()
	{
		if (empty())
			assert(false);
		int tail = (m_tail + 1) % (SIZE + 1);
		T data = m_Array[tail];
		m_tail = tail;
		m_size--;
		return data;
	}
	void clear()
	{
		m_size = 0;
		m_head = 0;
		m_tail = 0;
	}
	bool full() const
	{
		return m_size == SIZE;
	}
	bool empty() const
	{
		return m_size <= 0;
	}
	int size() const
	{
		return m_size;
	}
};