/*input
1
6 7
1 2 5
2 3 3
1 4 5
4 5 4
5 6 4
6 3 3
5 2 3
0
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;
typedef pair<int, int> ii;
vector<vector<ii> > adjList;
vector<bool> taken;
priority_queue<ii> pq;

void process(int v)
{
	taken[v] = true;
	for(int i=0;i<(int)adjList[v].size();i++)
	{
		if(!taken[adjList[v][i].first])
			pq.push(make_pair(adjList[v][i].second, -adjList[v][i].first));
	}
}

int main()
{
	int c, n, m, x, y, z, ans;
	while(cin >> c && c != 0)
	{
		while(c--)
		{
			cin >> n >> m;
			adjList.clear();
			taken.clear();
			adjList.assign(n, vector<ii>());
			taken.assign(n, false);
			ans = 0;
			while(m--)
			{
				cin >> x >> y >> z;
				x--;y--;
				adjList[x].push_back(make_pair(y, z));
				adjList[y].push_back(make_pair(x, z));
			}

			process(0);

			while(!pq.empty())
			{
				ii front = pq.top(); pq.pop();
				int u = -front.second, w = front.first;
				if(!taken[u])
					process(u);
				else
					ans += w;
			}
			cout << ans << endl;
		}
	}
	return 0;
}