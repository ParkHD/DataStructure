#pragma once
#include <assert.h>
template<typename T>
class CListNode
{
	template<typename T>
	friend class CLinkedList;
	template<typename T>
	friend class CListIterator;
	template<typename T>
	friend class CListReverseIterator;
private:
	CListNode()
	{
		m_pNext = nullptr;
		m_pPrev = nullptr;
	}
	~CListNode()
	{

	}
private :
	T m_Data;
	CListNode<T>* m_pNext;
	CListNode<T>* m_pPrev;
};
template<typename T>
class CListIterator
{
	template<typename T>
	friend class CLinkedList;

public:
	CListIterator()
	{
		m_pNode = nullptr;
	}
	~CListIterator()
	{

	}
private  :
	typedef CListNode<T>* PNODE;
private:
	PNODE m_pNode;
public:
	bool operator == (const CListIterator<T>& iter)
	{
		return m_pNode == iter.m_pNode;
	}
	bool operator != (const CListIterator<T>& iter)
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
	T& operator *()
	{
		return m_pNode->m_Data;
	}
};

template<typename T>
class CListReverseIterator
{
	template<typename T>
	friend class CLinkedList;
public:
	CListReverseIterator()
	{
		m_pNode = nullptr;
	}
	~CListReverseIterator()
	{

	}
private:
	typedef CListNode<T>* PNODE;
private:
	PNODE m_pNode;
public:
	bool operator == (const CListReverseIterator<T>& iter)
	{
		return m_pNode == iter.m_pNode;
	}
	bool operator != (const CListReverseIterator<T>& iter)
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
	T& operator *()
	{
		return m_pNode->m_Data;
	}
};

template<typename T>
class CLinkedList
{
public :
	CLinkedList()
	{
		head = new NODE;
		tail = new NODE;

		head->m_pNext = tail;
		tail->m_pPrev = head;
	}
	~CLinkedList()
	{
		clear();
		delete head;
		delete tail;
	}
private:
	typedef CListNode<T> NODE;
	typedef CListNode<T>* PNODE;
public:
	typedef CListIterator<T> iterator;
	typedef CListReverseIterator<T> reverse_iterator;
private:
	PNODE head;
	PNODE tail;
	int m_iSize;
public:
	void push_back(const T& data) // &쓰는 이유는 구조체나 class큰 값이 올때 참조로 받아오면 속도가빠르다 안쓰면 복사로 받아오기떄문에 늦음
	{
		PNODE newNode = new NODE;
		newNode->m_Data = data;

		PNODE pPrev = tail->m_pPrev;
// 
		pPrev->m_pNext = newNode;
		newNode->m_pPrev = pPrev;
		newNode->m_pNext = tail;
		tail->m_pPrev = newNode;

		++m_iSize;
	}
	void push_front(const T& data) // &쓰는 이유는 구조체나 class큰 값이 올때 참조로 받아오면 속도가빠르다 안쓰면 복사로 받아오기떄문에 늦음
	{
		PNODE newNode = new NODE;
		newNode->m_Data = data;

		PNODE pNext = head->m_pNext;

		newNode->m_pNext = pNext;
		pNext->m_pPrev = newNode;
		head->m_pNext = newNode;
		newNode->m_pPrev = head;

		++m_iSize;
	}
	void pop_back()
	{
		if (empty())
			assert(false);
		PNODE pDeleteNode = tail->m_pPrev;
		PNODE pPrev = pDeleteNode->m_pPrev;
		pPrev->m_pNext = tail;
		tail->m_pPrev = pPrev;

		delete pDeleteNode;
		--m_iSize;
	}
	void pop_front()
	{
		if (empty())
			assert(false);
		PNODE pDeleteNode = head->m_pNext;
		PNODE pNext = pDeleteNode->m_pNext;
		pNext->m_pPrev = head;
		head->m_pNext = pNext;

		delete pDeleteNode;
		--m_iSize;
	}

	T front() const
	{
		if (empty())
			assert(false);
		return head->m_pNext->m_Data;
	}
	T back() const
	{
		if (empty())
			assert(false);
		return tail->m_pPrev->m_Data;
	}
	void clear()
	{
		PNODE pNode = head->m_pNext;
		while (pNode != tail)
		{
			PNODE pNext = pNode->m_pNext;
			delete pNode;
			pNode = pNext;
		}
		m_iSize = 0;
		head->m_pNext = tail;
		tail->m_pPrev = head;
	}
	int size() const
	{
		return m_iSize;
	}
	bool empty() const
	{
		return m_iSize == 0;
	}

public:
	iterator begin() const
	{
		iterator iter;
		iter.m_pNode = head->m_pNext;
		return iter;
	}
	iterator end() const
	{
		iterator iter;
		iter.m_pNode = tail;
		return iter;
	}
	reverse_iterator rbegin() const
	{
		reverse_iterator iter;
		iter.m_pNode = tail->m_pPrev;
		return iter;
	}
	reverse_iterator rend() const
	{
		reverse_iterator iter;
		iter.m_pNode = head;
		return iter;
	}
	void sort(bool (*pFunc)(const T&, const T&))
	{
		for (PNODE pFirst = head->m_pNext; pFirst != tail->m_pPrev; pFirst = pFirst->m_pNext)
		{
			for (PNODE pSecond = pFirst->m_pNext; pSecond != tail; pSecond = pSecond->m_pNext)
			{
				if (pFunc(pFirst->m_Data, pSecond->m_Data))
				{
					T temp = pFirst->m_Data;
					pFirst->m_Data = pSecond->m_Data;
					pSecond->m_Data = temp;
				}
			}
		}
	}
};