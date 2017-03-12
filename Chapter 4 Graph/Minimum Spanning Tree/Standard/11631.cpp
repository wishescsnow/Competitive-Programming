/*input
7 11
0 1 7
0 3 5
1 2 8
1 3 9
1 4 7
2 4 5
3 4 15
3 5 6
4 5 8
4 6 9
5 6 11
3 2
0 1 2000000
1 2 1
0 0
*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> ii;
priority_queue<ii> pq;
vector<vector<ii> > adjList;
vector<bool> taken;

void process(int vertex)
{
	taken[vertex] = true;
	for(int i=0;i<(int)adjList[vertex].size();i++)
	{
		ii v = adjList[vertex][i];
		if(!taken[v.first])
			//second is weight and first is vertex
			pq.push(ii(-v.second, -v.first));
	}
}

int main()
{
	int m, n, x, y, z, total, cost;
	while((cin >> m >> n) && m != 0 && n != 0)
	{
		total = 0;
		cost = 0;
		adjList.clear();
		taken.clear();
		adjList.assign(m, vector<ii>());
		taken.assign(m, false);
		while(n--)
		{
			cin >> x >> y >> z;
			adjList[x].push_back(make_pair(y, z));
			adjList[y].push_back(make_pair(x, z));
			total += z;
		}

		process(0);
		while(!pq.empty())
		{
			ii front = pq.top();
			pq.pop();
			//second is vertex and first is weight
			int u = -front.second, w = -front.first;
			if(!taken[u])
			{
				cost += w;
				process(u);
			}
		}

		cout << total-cost << endl;
	}
	return 0;
}