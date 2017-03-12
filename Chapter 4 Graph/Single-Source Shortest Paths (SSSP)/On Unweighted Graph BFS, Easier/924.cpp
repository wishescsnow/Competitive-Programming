/*input
7
0
1 6
2 4 1
5 1 6 5 3 0
1 1
2 6 0
1 5
7
0
1
2
3
4
5
6
*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
vector<vector<int> > adjList;
vector<int> visited;
vector<int> sizePerLayer;
queue<int> BFS;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int E, N, a, T;
	cin >> E;
	adjList.clear();
	adjList.resize(E);
	for(int e=0;e<E;e++)
	{
		cin >> N;
		while(N--)
		{
			cin >> a;
			adjList[e].push_back(a);
		}
	}

	cin >> T;
	while(T--)
	{
		sizePerLayer.clear();
		sizePerLayer.assign(E-1, 0);
		visited.clear();
		visited.assign(E, -1);
		cin >> a;
		visited[a] = 0;
		BFS.push(a);
		while(!BFS.empty())
		{
			int u = BFS.front(); BFS.pop();
			for(int i=0;i<(int)adjList[u].size();i++)
			{
				if(visited[adjList[u][i]] == -1)
				{
					visited[adjList[u][i]] = visited[u]+1;
					sizePerLayer[visited[adjList[u][i]]-1] ++;
					BFS.push(adjList[u][i]);
				}
			}
		}

		int ans = 0, idx = -1;

		for(int i=0;i<E-1;i++)
		{
			if(sizePerLayer[i] > ans)
			{
				ans = sizePerLayer[i];
				idx = i+1;
			}
		}

		cout << ans;
		if(ans == 0)
			cout << endl;
		else
			cout << " " << idx << endl;
	}
	return 0;
}