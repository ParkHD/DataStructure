#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct vector2
{
public:
	int x;
	int y;
public:
	vector2()
	{
	}
	vector2(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
public:
	bool operator ==(vector2 vec)
	{
		return (x == vec.x) && (y == vec.y);
	}
	bool operator !=(vector2 vec)
	{
		return (x != vec.x) || (y != vec.y);
	}
	vector2 operator +(vector2 vec)
	{
		return vector2(x + vec.x, y + vec.y);
	}
};
class dfs
{
private:
	vector<string> stage;
	vector2 startPos;
	vector2 endPos;
	vector2 playerPos;

	queue<vector2> search;
	vector<vector<bool>> pastSearch;

	vector<vector<int>> shortRoute;			// 최단거리 : 앞으로 갈때마다 +1

	vector<vector2> dir;					// 상하좌우

	vector<int> result;
public:
	void init(vector<string> map, vector2 start, vector2 finish)
	{
		stage = map;
		startPos = start;
		endPos = finish;

		playerPos = start;
		search.push(start);
		pastSearch.resize(stage.size(), vector<bool>(stage[0].size(), false));

		shortRoute.resize(stage.size(), vector<int>(stage[0].size(), 0));

		dir.push_back(vector2(-1, 0)); //상
		dir.push_back(vector2(1, 0));  //하
		dir.push_back(vector2(0, -1)); //좌
		dir.push_back(vector2(0, 1));  //우
	}
	void show()
	{
		for (int x = 0; x < stage.size(); x++)
		{
			for (int y = 0; y < stage[0].size(); y++)
			{
				cout << ((startPos == vector2(x, y))? '@' : stage[x][y])<<" ";
			}
			cout << endl;
		}
	}
	bool isValid(vector2 vec)
	{
		if (vec.x < 0 || vec.y < 0 || vec.x >= stage.size() || vec.y >= stage[0].size())
			return false;
		if (stage[vec.x][vec.y] == '0')
			return false;
		if (pastSearch[vec.x][vec.y] == true)
			return false;
		else
			return true;
	}
	void searchMaze()
	{
		while (!search.empty())
		{
			pastSearch[playerPos.x][playerPos.y] = true; // 지금위치 지나온길에 추가
			playerPos = search.front();					 // search스택에 다음경로를 플레이어 위치에 삽입
			search.pop();								 // 경로삭제

			

			for (int i = 0; i<dir.size(); i++)
			{
				vector2 nextPos = playerPos + dir[i];
				if (isValid(nextPos))
				{
					shortRoute[nextPos.x][nextPos.y] = (shortRoute[playerPos.x][playerPos.y]) + 1;
					// 현재위치까지온 거리 +1 = 다음위치 거리

					if (nextPos != endPos)
					{
						search.push(nextPos);
					}
					else if (nextPos == endPos)
					{
						result.push_back(shortRoute[nextPos.x][nextPos.y]);
					}
				}
			}

			system("cls");
		}

		for (int i = 0; i < result.size(); i++)
		{
			cout << result[i] << endl;
		}
	}
};
int main()
{
	 

	vector<string> map1 =
	{
		{"101111"},
		{"101010"},
		{"101011"},
		{"111011"}
	};
	dfs maze;
	maze.init(map1, vector2(0, 0), vector2(3, 5));
	maze.show();
	maze.searchMaze();

}