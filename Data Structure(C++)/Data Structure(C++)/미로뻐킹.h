#pragma once
#include<vector>
#include<stack>
#include<iostream>
using namespace std;

enum MAZE_KEY
{
	None = 0,
	Blank = ' ',  // 문자는 사실 숫자고 ASCII코드에 의해서 표현.
	Wall = '#',
	Start = 'S',
	End = 'E',
	Player = '@',
	Path = '*',
};
enum VECTOR
{
	// 플레이어가 움직이는 방향 순서.
	Down,
	Left,
	Up,
	Right,

	Count,
};
struct Vector2
{
public:
	int x;
	int y;

public:
	Vector2()
	{

	}
	Vector2(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
public:
	bool IsEquals(int x, int y)
	{
		return (this->x == x) && (this->y == y);
	}
	bool IsEquals(Vector2 target)
	{
		return this->x == target.x && this->y == target.y;
	}
	void AddVector(VECTOR vec)
	{
		switch (vec)
		{
		case VECTOR::Up:
			this->y -= 1;
			break;
		case VECTOR::Down:
			this->y += 1;
			break;
		case VECTOR::Left:
			this->x -= 1;
			break;
		case VECTOR::Right:
			this->x += 1;
			break;
		}
	}
	Vector2 operator +(Vector2 a)
	{
		return Vector2(this->x + a.x, this->y + a.y);
	}
};
class MazeManager
{
	vector<string> backGround;

	Vector2 startPos;
	Vector2 endPos;
	Vector2 playerPos;
	Vector2 maxSize;

	stack<Vector2> searchPath;
	vector<Vector2> optimalPath;

	int searchCount = 0;
	bool isEndSearch = false;

public:
	void InitBackGround(vector<string> stage)
	{
		backGround = stage;
		maxSize = Vector2(stage.size(), stage[0].size());

		searchCount = 0;
		isEndSearch = false;
		
		for (int i = 0; i < stage.size(); i++)
		{
			for (int j = 0; j < stage[0].size(); j++)
			{
				if (stage[i][j] == MAZE_KEY::Start)
				{
					startPos = Vector2(i, j);
					playerPos = Vector2(i, j);
				}
				else if (stage[i][j] == MAZE_KEY::End)
				{
					endPos = Vector2(i, j);
				}
			}
		}

	}
	void ShowBackGround()
	{
		cout << "시작점 : " << startPos.x <<" "<< startPos.y << endl;
		cout << "도착점 : " << endPos.x << " " << endPos.y << endl;
		for (int i = 0; i < backGround.size(); i++)
		{
			for (int j = 0; j < backGround[0].size(); j++)
			{
				cout << backGround[i][j];

			}
			cout << endl;
		}
	}
	bool IsValidMove(Vector2 origin, VECTOR vec)
	{
		origin.AddVector(vec);

		if (origin.x < 0 || origin.y < 0)
			return false;

		if (origin.x >= maxSize.x || origin.y >= maxSize.y)
			return false;

		// 이전에 움직였던 지점인가?
		if (searchPath.size() > 0 && origin.IsEquals(searchPath.top()))
			return false;

		// 원점에서 vec방향을 움직였을 때. 그 곳이 유효한가?
		char word = backGround[origin.x][origin.y];

		// 해당 위치의 문자가 Blank일때.
		return (word != MAZE_KEY::Wall);
	}
	vector<Vector2> SearchMaze()
	{
		if (playerPos.IsEquals(endPos))
		{
			searchPath.push(playerPos);
			optimalPath = searchPath;
			isEndSearch = true;
			
			ShowBackground();
			Console.WriteLine("골인 지점");
			Console.ReadLine();

			return null;
		}

		int myIndex = searchCount++;

		for (VECTOR vec = 0; vec < VECTOR.Count; vec++)
		{
			if (isEndSearch)
				break;

			ShowBackground();
			bool isValid = IsValidMove(playerPos, vec);

			Console.WriteLine("============================");
			Console.WriteLine("[SearchMaze{0}] vec : {1}", myIndex, vec.ToString());
			Console.WriteLine("{0} 방향으로 {1}", vec, isValid ? "이동 할 수 있습니다." : "이동할 수 없습니다.");
			Console.WriteLine("============================");
			Thread.Sleep(50);

			// 해당 방향으로 이동.
			if (isValid)
			{
				// 움직임.
				searchPath.Push(playerPos); // 이전 위치 저장.
				playerPos.AddVector(vec);

				SearchMaze();
			}
		}

		// 여전히 찾고 있을 경우.
		if (!isEndSearch)
		{
			ShowBackground();
			Console.WriteLine("[SearchMaze{0}]", myIndex);
			Console.WriteLine("더이상 길이 없습니다. 되돌아 갑니다. : {0}", searchPath.Peek().ToString());
			Thread.Sleep(50);

			playerPos = searchPath.Pop();
		}

		return searchPath.ToArray();
	}
};