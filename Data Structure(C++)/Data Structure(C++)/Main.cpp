#include <iostream>
#include <vector>
#include <time.h>
#include "연결리스트.h"
#include "DoulbleList0425.h"
#include "Stack.h"
#include "Queue.h"
using namespace std;

struct ex
{
	int data;
};
bool DataSort(const ex& a, const ex& b)
{
	return a.data > b.data;
}
bool func(const int& a, const int& b)
{
	return a > b;
}
enum ex1
{
	LEFT,
	right,
	up,
	down,
};
#include "미로뻐킹.h"
int main()
{
	MazeManager manager;
	vector<string> stage = 
	{
		"######S###",
		"###### ###",
		"###### ###",
		"###    ###",
		"### ######",
		"### ######",
		"#        E",
		"# ### ## #",
		"# ###    #",
		"#   ######",
		"##########"
	};
	manager.InitBackGround(stage);
	manager.SearchMaze();
#pragma region MyRegion



	/*vector<int> vec;

	CLinkedList<int> list;
	for (int i = 0; i < 100; i++)
	{
		list.push_back(i);
	}
	cout << "size :" << list.size() << endl;

	CLinkedList<int>::iterator iter;
	CLinkedList<int>::iterator iterEnd = list.end();
	for (iter = list.begin(); iter != iterEnd; ++iter)
	{
		cout << *iter << endl;
	}

	CLinkedList<int>::reverse_iterator riter;
	CLinkedList<int>::reverse_iterator riterEnd = list.rend();
	for (riter = list.rbegin(); riter != riterEnd; ++riter)
	{
		cout << *riter << endl;
	}

	CLinkedList<ex> dataList;
	cout << "============data List==============" << endl;
	srand((unsigned int)time(0));
	for (int i = 0; i < 10; ++i)
	{
		ex tData;
		
		tData.data = rand() % 100;
		dataList.push_back(tData);

		cout << tData.data << endl;
	}
	cout << "============sort==============" << endl;
	dataList.sort(DataSort);

	CLinkedList<ex>::iterator iterD;
	CLinkedList<ex>::iterator iterDEnd = dataList.end();
	for (iterD = dataList.begin(); iterD != iterDEnd; ++iterD)
	{
		cout << (*iterD).data << endl;
	}*/


	/*DoubleList<int> list;

	list.push_back(15);
	list.push_back(10);
	list.push_back(15);
	list.push_front(20);


	for (DoubleList<int>::iterator i = list.begin(); i != list.end(); ++i)
	{
		cout << *i << endl;
	}
	list.sort(func);
	for (DoubleList<int>::iterator i = list.begin(); i != list.end(); ++i)
	{
		cout << *i << endl;
	}*/

	/*Stack<char> stack;

	char chText[] = "textTEXT";
	for (int i = 0; i < strlen(chText); i++)
	{
		stack.push(chText[i]);
	}
	for (int i = 0; i < stack.size();)
	{
		cout << stack.pop();
	}
	cout << endl;

	CStackArray<int> stackArray;
	for (int i = 0; i < 10; i++)
	{
		stackArray.push(i);
	}
	for (int i = 0; i < stackArray.size();)
	{
		cout << stackArray.pop();
	}*/


	/*QueueList<int> queue;
	queue.push(10);
	queue.push(5);
	queue.push(12);

	cout << queue.pop() << endl;
	cout << queue.pop() << endl;
	cout << queue.pop() << endl;
	cout << queue.size() << endl;

	queue.push(10);
	queue.push(5);
	queue.push(12);

	queue.clear();
	cout << queue.size() << endl;*/


	/*CircleQueue<int, 5> circleQue;

	for (int i = 0; i < 5; i++)
	{
		circleQue.push(i);
	}
	for (int i = 0; i < 3 ; i++)
	{
		cout << circleQue.pop() << endl;
	}
	cout << circleQue.size() << endl;
	circleQue.clear();
	cout << circleQue.size();*/
#pragma endregion

}