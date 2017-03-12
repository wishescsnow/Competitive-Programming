/*input
10 10
9
0 1 2
1 1 2
2 2 2 9
3 2 1 7
5 3 3 6 9
6 4 0 1 2 7
7 3 0 3 8
8 2 7 9
9 3 2 3 4
0 0
9 9
3 3
3
0 1 2
1 1 2
2 1 0
0 0
2 2
0 0
*/
#include <iostream>
#include <string.h>
#include <queue>

using namespace std;
int map[1010][1010];
queue<pair<int, int> > BFS;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int R, C, nr, nc, r, c, sr, sc, dr, dc;
	while((cin >> R >> C) && !(R == 0 && C == 0))
	{
		memset(map, 0, sizeof map);
		cin >> nr;
		while(nr--)
		{
			cin >> r >> nc;
			while(nc--)
			{
				cin >> c;
				map[r][c] = -1;
			}
		}

		cin >> sr >> sc;
		cin >> dr >> dc;

		while(!BFS.empty())
			BFS.pop();

		BFS.push(make_pair(sr, sc));
		if(map[sr][sc] == -1)
		{
			cout << map[sr][sc] << endl;
			continue;
		}

		while(!BFS.empty())
		{
			pair<int, int> u = BFS.front(); BFS.pop();
			if(u.first - 1 >= 0 && map[u.first-1][u.second] == 0 && !(u.first - 1 == sr && u.second == sc))
			{
				map[u.first-1][u.second] = map[u.first][u.second] + 1;
				if(u.first-1 == dr && u.second == dc)
					break;
				BFS.push(make_pair(u.first-1, u.second));
			}
			if(u.second + 1 < C && map[u.first][u.second + 1] == 0 && !(u.first == sr && u.second + 1 == sc))
			{
				map[u.first][u.second + 1] = map[u.first][u.second] + 1;
				if(u.first == dr && u.second + 1 == dc)
					break;
				BFS.push(make_pair(u.first, u.second + 1));
			}
			if(u.first + 1 < R && map[u.first + 1][u.second] == 0 && !(u.first + 1 == sr && u.second == sc))
			{
				map[u.first+1][u.second] = map[u.first][u.second] + 1;
				if(u.first+1 == dr && u.second == dc)
					break;
				BFS.push(make_pair(u.first + 1, u.second));
			}
			if(u.second - 1 >= 0 && map[u.first][u.second - 1] == 0 && !(u.first == sr && u.second - 1 == sc))
			{
				map[u.first][u.second - 1] = map[u.first][u.second] + 1;
				if(u.first == dr && u.second - 1 == dc)
					break;
				BFS.push(make_pair(u.first, u.second - 1));
			}
		}

		cout << map[dr][dc] << endl;
	}
	return 0;
}