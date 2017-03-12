/*input
5
10
10
130
15
5 8 37
10 1 70
3 4 69
5 3 17
3 6 93
2 6 79
7 3 70
8 2 81
8 5 32
4 6 64
6 5 12
2 7 84
9 4 8
10 6 94
1 6 55
10
2
70
15
6 5 32
1 6 89
3 5 0
3 4 78
4 6 27
6 8 16
2 3 22
10 2 21
4 7 46
5 1 10
1 10 76
1 7 55
10 1 46
10 5 18
7 6 57
10
6
50
15
7 6 30
8 4 0
4 10 72
6 5 0
9 2 22
4 5 26
8 10 94
9 1 45
2 7 68
10 3 24
1 10 62
5 1 17
10 6 81
5 6 59
1 7 74
10
5
140
15
4 5 9
9 2 46
6 10 96
4 10 56
4 9 43
10 2 35
2 10 53
2 9 99
2 8 87
3 1 59
9 10 4
2 4 30
3 4 71
6 9 44
7 6 84
10
1
140
15
6 9 1
6 2 21
8 10 58
4 6 42
10 6 6
5 4 31
3 9 33
10 8 0
1 7 62
10 3 16
8 9 57
9 4 89
1 8 14
3 4 18
6 1 80
*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
typedef pair<int, int> ii;
const int INF = 1000000000;
vector<vector<ii> > adjList;
vector<int> dist;
priority_queue<ii, vector<ii>, greater<ii> > pq;


int main()
{
	int C, N, E, T, M, a, b, t, ans;
	cin >> C;
	while(C--)
	{
		cin >> N >> E >> T >> M;
		E--;
		adjList.clear();
		adjList.resize(N);
		while(M--)
		{
			cin >> a >> b >> t;
			a--; b--;
			adjList[b].push_back(ii(a, t));
		}

		dist.clear();
		dist.assign(N, INF);

		pq.push(ii(0, E));
		dist[E] = 0;

		ans = 0;

		while(!pq.empty())
		{
			ii front = pq.top(); pq.pop();
			int d = front.first, u = front.second;
			if(d > dist[u]) continue;
			for(int j=0;j<(int)adjList[u].size();j++)
			{
				ii v = adjList[u][j];
				if(dist[u] + v.second < dist[v.first])
				{
					dist[v.first] = dist[u] + v.second;
					pq.push(ii(dist[v.first], v.first));
				}
			}
		}

		for(int i=0;i<N;i++)
		{
			if(dist[i] <= T)
				ans++;
		}

		cout << ans << endl;
		if(C)
			cout << endl;
	}
	return 0;
}