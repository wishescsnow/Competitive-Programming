/*input
3
2 1 0 1
0 1 100
3 3 2 0
0 1 100
0 2 200
1 2 50
2 0 0 1
*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
const int INF = 1000000000;
typedef pair<int, int> ii;
vector<vector<ii> > adjList;
vector<int> dist;
priority_queue<ii, vector<ii>, greater<ii> > pq;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N, n, m, S, T, s1, s2, w;
	cin >> N;
	for(int t=1;t<=N;t++)
	{
		cin >> n >> m >> S >> T;
		adjList.clear();
		adjList.resize(n);
		dist.clear();
		dist.assign(n, INF);
		while(m--)
		{
			cin >> s1 >> s2 >> w;
			adjList[s1].push_back(ii(s2, w));
			adjList[s2].push_back(ii(s1, w));
		}

		dist[S] = 0;
		pq.push(ii(0, S));

		while(!pq.empty())
		{
			ii front = pq.top(); pq.pop();
			int d = front.first, u = front.second;
			if(d > dist[u]) continue;
			for(int i=0;i<(int)adjList[u].size();i++)
			{
				ii v = adjList[u][i];
				if(dist[u] + v.second < dist[v.first])
				{
					dist[v.first] = dist[u] + v.second;
					pq.push(ii(dist[v.first], v.first));
				}
			}
		}

		if(dist[T] == INF)
			cout << "Case #" << t << ": unreachable" << endl;
		else
			cout << "Case #" << t << ": " << dist[T] << endl;
	}
	return 0;
}