/*input
9 10
0 0 0 0 0 0 1 0 0 0
0 0 0 0 0 0 0 0 1 0
0 0 0 1 0 0 0 0 0 0
0 0 1 0 0 0 0 0 0 0
0 0 0 0 0 0 1 0 0 0
0 0 0 0 0 1 0 0 0 0
0 0 0 1 1 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0 1 0
7 2 2 7 south
0 0
*/
#include <iostream>
#include <queue>
#include <string.h>

using namespace std;
int visited[60][60][4];
queue<pair<int, pair<int, int> > > BFS;

void move(int count, int srcx, int srcy, int &dstx, int &dsty, int orientation)
{
	switch(orientation)
	{
		case 0:
			dstx = srcx;
			dsty = srcy+count;
			return;
		case 1:
			dstx = srcx+count;
			dsty = srcy;
			return;
		case 2:
			dstx = srcx;
			dsty = srcy-count;
			return;
		case 3:
			dstx = srcx-count;
			dsty = srcy;
			return;
	}
}

int convertToIndex(char orientation)
{
	switch(orientation)
	{
		case 'e':
			return 0;
		case 's':
			return 1;
		case 'w':
			return 2;
		case 'n':
			return 3;
	}
}

int turn(bool left, int orientation)
{
	if(left)
	{
		switch(orientation)
		{
			case 0:
				return 3;
			case 1:
				return 0;
			case 2:
				return 1;
			case 3:
				return 2;
		}
	}
	else
	{
		switch(orientation)
		{
			case 0:
				return 1;
			case 1:
				return 2;
			case 2:
				return 3;
			case 3:
				return 0;
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int M, N, B1, B2, E1, E2;
	bool block;
	string orien;
	while((cin >> M >> N) && !(M == 0 && N == 0))
	{
		for(int i=0;i<=M;i++)
			for(int j=0;j<=N;j++)
				for(int k=0;k<4;k++)
					visited[i][j][k] = -1;

		for(int r=0;r<M;r++)
		{
			for(int c=0;c<N;c++)
			{
				cin >> block;
				for(int d=0;d<4;d++)
				{
					if(block)
					{
						visited[r][c][d] = -2;
						visited[r][c+1][d] = -2;
						visited[r+1][c][d] = -2;
						visited[r+1][c+1][d] = -2;
					}
				}
			}
		}

		cin >> B1 >> B2 >> E1 >> E2 >> orien;

		while(!BFS.empty())
			BFS.pop();

		BFS.push(make_pair(convertToIndex(orien[0]), make_pair(B1, B2)));
		visited[B1][B2][convertToIndex(orien[0])] = 0;

		while(!BFS.empty())
		{
			pair<int, pair<int, int> > coor = BFS.front(); BFS.pop();
			int o = coor.first;
			int r = coor.second.first, c = coor.second.second;
			int newr, newc;
			if(visited[r][c][turn(true, o)] == -1)
			{
				visited[r][c][turn(true, o)] = visited[r][c][o]+1;
				BFS.push(make_pair(turn(true, o), make_pair(r, c)));
			}
			if(visited[r][c][turn(false, o)] == -1)
			{
				visited[r][c][turn(false, o)] = visited[r][c][o]+1;
				BFS.push(make_pair(turn(false, o), make_pair(r, c)));
			}
			move(1, r, c, newr, newc, o);
			if(visited[newr][newc][o] == -2)
				continue;
			if(newr > 0 && newr < M && newc > 0 && newc < N && visited[newr][newc][o] == -1)
			{
				visited[newr][newc][o] = visited[r][c][o]+1;
				BFS.push(make_pair(o, make_pair(newr, newc)));
			}
			move(2, r, c, newr, newc, o);
			if(visited[newr][newc][o] == -2)
				continue;
			if(newr > 0 && newr < M && newc > 0 && newc < N && visited[newr][newc][o] == -1)
			{
				visited[newr][newc][o] = visited[r][c][o]+1;
				BFS.push(make_pair(o, make_pair(newr, newc)));
			}
			move(3, r, c, newr, newc, o);
			if(newr > 0 && newr < M && newc > 0 && newc < N && visited[newr][newc][o] == -1)
			{
				visited[newr][newc][o] = visited[r][c][o]+1;
				BFS.push(make_pair(o, make_pair(newr, newc)));
			}
		}

		int minDistance = -1;
		for(int k=0;k<4;k++)
		{
			if(visited[E1][E2][k] >= 0 && (minDistance == -1 || visited[E1][E2][k] < minDistance))
				minDistance = visited[E1][E2][k];
		}

		cout << minDistance << endl;
	}
	return 0;
}