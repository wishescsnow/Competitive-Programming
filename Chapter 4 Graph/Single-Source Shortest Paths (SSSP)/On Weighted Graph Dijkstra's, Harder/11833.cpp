/*input
4 6 3 3
0 1 10
1 2 10
0 2 1
3 0 1
3 1 10
3 2 10
6 7 2 5
5 2 1
2 1 10
1 0 1
3 0 2
3 4 2
3 5 3
5 4 2
5 5 2 4
0 1 1
1 2 2
2 3 3
3 4 4
4 0 5
7 11 4 1
0 1 2
1 2 8
0 6 1
0 5 7
6 5 3
6 1 9
5 4 2
4 3 4
4 6 10
3 2 8
6 2 3
0 0 0 0
*/
#include <iostream>
#include <vector>
#include <queue>
#define INF 1000000000

using namespace std;
typedef pair<int, int> ii;
vector<vector<ii> > adjList;
vector<vector<ii> > serviceRoute;
priority_queue<ii, vector<ii>, greater<ii> > pq;
vector<int> dist;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N, M, C, K, U, V, P;
	while((cin >> N >> M >> C >> K) && !(N == 0 && M == 0 && C == 0 && K == 0))
	{
		adjList.clear();
		adjList.resize(N);
		serviceRoute.clear();
		serviceRoute.resize(C);
		dist.clear();
		dist.assign(N, INF);

		while(M--)
		{
			cin >> U >> V >> P;
			if((U >= 0 && U < C-1 && V == U + 1) || (V >= 0 && V < C-1 && U == V + 1))
			{
				serviceRoute[U].push_back(ii(V, P));
				serviceRoute[V].push_back(ii(U, P));
				continue;
			}
			adjList[U].push_back(ii(V, P));
			adjList[V].push_back(ii(U, P));
		}

		pq.push(ii(0, K));
		dist[K] = 0;

		while(!pq.empty())
		{
			ii front = pq.top(); pq.pop();
			int d = front.first, u = front.second;
			if(d > dist[u]) continue;
			if(u >= 0 && u < C-1)
			{
				for(int i=0;i<(int)serviceRoute[u].size();i++)
				{
					ii v = serviceRoute[u][i];
					if(dist[u] + v.second < dist[v.first])
					{
						dist[v.first] = dist[u] + v.second;
						pq.push(ii(dist[v.first], v.first));
					}
				}
			}
			else
			{
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
		}

		cout << dist[C-1] << endl;
	}
	return 0;
}