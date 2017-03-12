/*input
4
0 0
0 1
1 1
1 0
6
4 3
4 2
3 2
2 2
2 3
3 3
4
0 0
0 1
1 1
1 0
6
3 2
3 1
2 1
1 1
1 2
2 2
4
0 0
0 1
1 1
1 0
6
2 2
2 1
1 1
0 1
0 2
1 2
0
*/
#include <iostream>
#include <string.h>
#include <queue>

using namespace std;
int citymap[2010][2010];
queue<pair<int, int> > BFS;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int m, a, s, srcx, srcy;
	while(cin >> m && m != 0)
	{
		while(!BFS.empty())
			BFS.pop();
		memset(citymap, -1, sizeof citymap);
		while(m--)
		{
			cin >> a >> s;
			BFS.push(make_pair(a, s));
			citymap[a][s] = 0;
		}

		cin >> m;
		while(m--)
		{
			cin >> a >> s;
			citymap[a][s] = -2;
		}

		int dstx, dsty;

		while(!BFS.empty())
		{
			pair<int, int> point = BFS.front(); BFS.pop();
			int x = point.first, y = point.second;
			if(x - 1 >= 0 && citymap[x-1][y] < 0)
			{
				if(citymap[x-1][y] == -2)
				{
					citymap[x-1][y] = citymap[x][y] + 1;
					dstx = x-1;
					dsty = y;
					break;
				}
				else
				{
					citymap[x-1][y] = citymap[x][y] + 1;
					BFS.push(make_pair(x-1, y));
				}
			}
			if(y - 1 >= 0 && citymap[x][y-1] < 0)
			{
				if(citymap[x][y-1] == -2)
				{
					citymap[x][y-1] = citymap[x][y] + 1;
					dstx = x;
					dsty = y-1;
					break;
				}
				else
				{
					citymap[x][y-1] = citymap[x][y] + 1;
					BFS.push(make_pair(x, y-1));
				}
			}
			if(x + 1 <= 2000 && citymap[x+1][y] < 0)
			{
				if(citymap[x+1][y] == -2)
				{
					citymap[x+1][y] = citymap[x][y] + 1;
					dstx = x+1;
					dsty = y;
					break;
				}
				else
				{
					citymap[x+1][y] = citymap[x][y] + 1;
					BFS.push(make_pair(x+1, y));
				}
			}
			if(y + 1 <= 2000 && citymap[x][y+1] < 0)
			{
				if(citymap[x][y+1] == -2)
				{
					citymap[x][y+1] = citymap[x][y] + 1;
					dstx = x;
					dsty = y+1;
					break;
				}
				else
				{
					citymap[x][y+1] = citymap[x][y] + 1;
					BFS.push(make_pair(x, y+1));
				}
			}
		}

		cout << citymap[dstx][dsty] << endl;
	}
	return 0;
}