/*input
16
1 2  2 7  1 3  3 4  3 5  5 10  5 11
4 6  7 6  7 8  7 9  8 9  8  6  6 11 21 22 22 23
1 1  1 2  3 2  3 3  21 1 0 0
1
1 3
2 0
0 0
1
1 1
1 0
0 0
4
1 2 2 3 4 5 5 6
1 5 1 1 4 2 0 0
4
1 2
2 3
3 4
1 4
1 1
1 2
1 3
1 0
0 0
5
1 2 2 3 3 1 4 5 6 2147483647
1 1 1 0 4 1 4 2 5 1 6 2 8 2 0 0
10
1 2 1 3 3 5 2 5 3 4 5 4 6 4 7 10 10 9 8 9
2 3 7 2 10 1 0 0
4
0 0 1 2 2 3 4 4
1 0 1 1 1 2 1 3 1 4 2 0 2 1 2 2 2 3 2 4 3 0 3 1 3 2 3 3 4 0 4 1 4 2
0 0
30
1 2 2 3 3 4 4 5 5 6 6 7 7 8 8 9 9 0 0 1
11 12 12 13 13 14 14 15 15 16 16 17 17 18 18 19 19 20 20 1
21 22 22 23 23 24 24 25 25 26 26 27 27 28 28 29 29 30 30 1
1 0 1 1 1 2 1 3 1 4 1 5 1 6 1 7 1 8 1 9 1 10 1 11 1 12 1 13 1 14 1 15 1 16
1 17 1 18 1 19 1 20 1 21 18 0 18 1 18 2 18 3 18 4 18 5 18 6 18 7 18 8 18 9
18 10 18 11 18 12 18 13 18 14 18 15 0 0
32
1 2 2 3 3 4 4 5 5 6 6 7 7 8 8 9 9 0 0 1 5 14 24 13
11 12 12 13 13 14 14 15 15 16 16 17 17 18 18 19 19 20 20 1
21 22 22 23 23 24 24 25 25 26 26 27 27 28 28 29 29 30 30 1
1 0 1 1 1 2 1 3 1 4 1 5 1 6 1 7 1 8 1 9 1 10 1 11 1 12 1 13 1 14 1 15 1 16
1 17 1 18 1 19 1 20 1 21 18 0 18 1 18 2 18 3 18 4 18 5 18 6 18 7 18 8 18 9
18 10 18 11 18 12 18 13 18 14 18 15 0 0
3
1 2 2 3 4 5
1 0 1 1 1 2 1 3 2 0 2 1 2 2 2 3 3 0 3 1 3 2 3 3 4 0 4 1 4 2 4 3 5 0 5 1 5 2 5 3
0 0
1
10 11
10 0 10 1 10 2 12 1 10 0 10 1 10 2 0 0
0
*/
#include <iostream>
#include <map>
#include <vector>
#include <queue>

using namespace std;
map<int, vector<int> > adjList;
map<int, int> visited;
queue<int> BFS;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int NC, a, b, caseNum = 1;
	while(cin >> NC && NC != 0)
	{
		adjList.clear();
		while(NC--)
		{
			cin >> a >> b;
			adjList[a].push_back(b);
			adjList[b].push_back(a);
		}

		while((cin >> a >> b) && !(a == 0 && b == 0))
		{
			visited.clear();
			for(map<int, vector<int> >::iterator it=adjList.begin();it!=adjList.end();it++)
			{
				for(int i=0;i<(*it).second.size();i++)
					visited[(*it).second[i]] = -1;
				visited[(*it).first] = -1;
			}

			int ans = 0;
			if(visited.find(a) != visited.end())
			{
				visited[a] = 0;
				BFS.push(a);
			}
			while(!BFS.empty())
			{
				int u = BFS.front(); BFS.pop();
				for(int i=0;i<(int)adjList[u].size();i++)
				{
					if(visited[adjList[u][i]] == -1)
					{
						BFS.push(adjList[u][i]);
						visited[adjList[u][i]] = visited[u] + 1;
					}
				}
			}

			for(map<int, int>::iterator it=visited.begin();it!=visited.end();it++)
			{
				if((*it).second > b || (*it).second == -1)
					ans++;
			}

			cout << "Case " << caseNum++ << ": " << ans <<
			" nodes not reachable from node " << a << " with TTL = " << b << "." << endl;
		}
	}
	return 0;
}