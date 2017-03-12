/*input
3 6
6 2
0 3 3 3
1 2 6 2
0 4 4 4
1 1
1 6
0 6 5 6
0 5 5 5
0 3 4 3
5 6
1 6
3 1 3 5
1 1 5 1
1 1 1 6
2 6
6 2
2 6 5 6
0 3 4 3
1 2 6 2
3 4
6 1
0 3 5 3
1 2 6 2
0 5 5 5
5 3
1 6
6 2 6 6
1 2 1 6
3 0 3 5
3 5
6 1
0 3 4 3
1 5 2 5
1 1 6 1
6 6
4 1
5 1 5 6
4 0 4 5
1 4 4 4
1 1
6 3
5 0 5 4
1 0 1 5
2 1 2 6
5 5
1 4
3 1 3 6
2 0 2 5
1 1 1 6
0 0
*/
#include <iostream>
#include <vector>
#include <queue>
#include <string.h>

using namespace std;
char visited[36];
int path[36];
typedef pair<int, int> ii;
typedef pair<ii, ii> iiii;
vector<iiii> horizontal;
vector<iiii> vertical;
queue<ii> BFS;

void printPath(int index)
{
	if(visited[path[index]] != 'Z')
		printPath(path[index]);
	cout << visited[index];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int i1, i2, i3, i4;
	ii start, end;
	iiii wall;
	while((cin >> i1 >> i2) && !(i1 == 0 && i2 == 0))
	{
		horizontal.clear();
		vertical.clear();
		for(int i=0;i<36;i++)
		{
			visited[i] = 'A';
			path[i] = -1;
		}
		start = ii(i2, i1);
		cin >> i1 >> i2;
		end = ii(i2, i1);
		cin >> i1 >> i2 >> i3 >> i4;
		wall = make_pair(ii(i2, i1), ii(i4, i3));
		if(i4 == i2)
			horizontal.push_back(wall);
		else
			vertical.push_back(wall);

		cin >> i1 >> i2 >> i3 >> i4;
		wall = make_pair(ii(i2, i1), ii(i4, i3));
		if(i4 == i2)
			horizontal.push_back(wall);
		else
			vertical.push_back(wall);

		cin >> i1 >> i2 >> i3 >> i4;
		wall = make_pair(ii(i2, i1), ii(i4, i3));
		if(i4 == i2)
			horizontal.push_back(wall);
		else
			vertical.push_back(wall);

		while(!BFS.empty())
			BFS.pop();

		BFS.push(start);
		visited[(start.first-1)*6 + (start.second-1)] = 'Z';
		while(!BFS.empty())
		{
			bool go = true;
			ii point = BFS.front(); BFS.pop();
			int r = point.first, c = point.second;
			if(r - 1 > 0 && visited[(r-2)*6 + (c-1)] == 'A')
			{
				for(int i=0;i<(int)horizontal.size();i++)
				{
					if(r-1 == horizontal[i].first.first && c <= horizontal[i].second.second && c > horizontal[i].first.second)
						go = false;
				}
				if(go)
				{
					visited[(r-2)*6 + (c-1)] = 'N';
					path[(r-2)*6 + (c-1)] = (r-1)*6 + (c-1);
					if(r-1 == end.first && c == end.second)
						break;
					BFS.push(ii(r-1, c));
				}
				go = true;
			}
			if(c + 1 <= 6 && visited[(r-1)*6 + (c)] == 'A')
			{
				for(int i=0;i<(int)vertical.size();i++)
				{
					if(c == vertical[i].first.second && r <= vertical[i].second.first && r > vertical[i].first.first)
						go = false;
				}
				if(go)
				{
					visited[(r-1)*6 + (c)] = 'E';
					path[(r-1)*6 + (c)] = (r-1)*6 + (c-1);
					if(r == end.first && c+1 == end.second)
						break;
					BFS.push(ii(r, c+1));
				}
				go = true;
			}
			if(r + 1 <= 6 && visited[(r)*6 + (c-1)] == 'A')
			{
				for(int i=0;i<(int)horizontal.size();i++)
				{
					if(r == horizontal[i].first.first && c <= horizontal[i].second.second && c > horizontal[i].first.second)
						go = false;
				}
				if(go)
				{
					visited[(r)*6 + (c-1)] = 'S';
					path[(r)*6 + (c-1)] = (r-1)*6 + (c-1);
					if(r+1 == end.first && c == end.second)
						break;
					BFS.push(ii(r+1, c));
				}
				go = true;
			}
			if(c - 1 > 0 && visited[(r-1)*6 + (c-2)] == 'A')
			{
				for(int i=0;i<(int)vertical.size();i++)
				{
					if(c-1 == vertical[i].first.second && r <= vertical[i].second.first && r > vertical[i].first.first)
						go = false;
				}
				if(go)
				{
					visited[(r-1)*6 + (c-2)] = 'W';
					path[(r-1)*6 + (c-2)] = (r-1)*6 + (c-1);
					if(r == end.first && c-1 == end.second)
						break;
					BFS.push(ii(r, c-1));
				}
				go = true;
			}
		}

		printPath((end.first-1)*6 + (end.second-1));
		cout << endl;
	}
	return 0;
}