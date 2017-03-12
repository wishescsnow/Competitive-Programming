/*input
4
1 1
9
2 2
0 0
0 0
20 20
1 4 5 7 8 9 7 5 3 4 6 7 4 3 6 8 4 3 5 9
2 4 0 9 7 5 4 6 7 8 4 3 1 4 6 7 8 9 6 5
1 2 3 4 6 6 8 9 9 0 0 0 0 0 3 4 5 4 3 1
1 4 5 7 8 9 7 5 3 4 6 7 4 3 6 8 4 3 5 9
2 4 0 9 7 5 4 6 7 8 4 3 1 4 6 7 8 9 6 5
1 2 3 4 5 6 7 8 9 9 0 6 4 3 2 4 5 6 7 8
8 5 9 2 4 5 6 7 8 9 2 1 2 3 4 5 6 8 9 0
9 9 9 0 0 0 0 0 1 2 3 4 6 7 8 9 0 5 4 3
1 2 3 4 5 6 7 8 9 9 0 6 4 3 2 4 5 6 7 8
1 4 5 7 8 9 7 5 3 4 6 7 4 3 6 8 4 3 5 9
1 3 5 7 8 9 2 2 2 2 3 4 4 4 4 5 6 7 8 9
0 9 9 8 7 6 9 9 9 9 9 9 9 0 0 0 0 0 9 9
1 2 3 4 5 6 7 8 9 9 0 6 4 3 2 4 5 6 7 8
8 5 9 2 4 5 6 7 8 9 2 1 2 3 4 5 6 8 9 0
1 2 3 4 6 6 8 9 9 0 0 0 0 0 3 4 5 4 3 1
1 4 5 7 8 9 7 5 3 4 6 7 4 3 6 8 4 3 5 9
1 2 3 4 5 6 7 8 9 5 3 2 4 5 6 7 8 9 9 6
1 2 3 4 5 6 7 8 9 9 0 6 4 3 2 4 5 6 7 8
0 0 0 0 0 0 1 1 1 1 2 3 3 3 3 3 4 4 4 4
3 3 3 1 1 1 1 1 3 4 5 6 7 8 9 0 5 4 3 1
22 20
1 4 5 7 8 9 7 5 3 4 6 7 4 3 6 8 4 3 5 9
2 4 0 9 7 5 4 6 7 8 4 3 1 4 6 7 8 9 6 5
1 2 3 4 6 6 8 9 9 0 0 0 0 0 3 4 5 4 3 1
1 4 5 7 8 9 7 5 3 4 6 7 4 3 6 8 4 3 5 9
2 4 0 9 7 5 4 6 7 8 4 2 2 2 2 2 8 9 6 5
1 2 3 4 5 6 7 8 9 9 0 6 4 3 2 4 0 6 7 8
1 5 9 2 4 5 6 7 8 9 2 1 2 3 4 5 6 8 9 0
9 9 9 0 0 0 0 0 1 2 3 4 6 7 8 9 0 5 4 3
1 2 3 4 5 6 7 8 9 9 0 6 4 0 0 0 5 6 7 8
1 4 5 7 8 9 7 5 3 4 6 7 4 0 0 0 4 3 5 9
1 3 5 7 8 9 2 2 0 2 3 4 4 0 0 0 6 4 8 9
0 9 9 8 7 6 9 9 9 9 9 9 9 0 0 0 2 0 9 9
1 2 3 4 5 6 7 8 9 9 0 6 4 3 2 4 5 6 7 8
8 5 9 2 4 5 6 7 8 9 2 1 2 3 4 5 6 8 9 0
1 2 3 4 6 6 8 9 0 0 0 0 0 0 3 4 5 4 3 1
1 4 5 7 8 9 7 5 3 4 6 7 4 3 6 8 4 3 5 9
1 2 3 4 5 6 7 8 9 5 3 2 4 5 6 7 8 9 9 6
1 2 3 4 5 6 7 8 9 9 0 6 4 3 2 4 5 6 7 8
0 0 0 0 0 0 1 1 1 1 2 3 3 3 3 3 4 4 4 4
3 3 3 1 1 1 1 1 3 4 5 6 7 8 9 0 5 4 3 1
8 5 9 2 4 5 6 7 8 9 2 1 2 3 4 5 6 8 9 0
1 2 3 4 6 6 8 9 9 0 0 0 0 0 3 4 5 4 3 1
*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
const int INF = 1000000000;
priority_queue<iii, vector<iii>, greater<iii> > pq;
int maze[1010][1010];
vector<int> dist;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int T, N, M;
	cin >> T;
	while(T--)
	{
		cin >> N >> M;
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<M;j++)
			{
				cin >> maze[i][j];
			}
		}

		dist.clear();
		dist.assign(N*M, INF);
		dist[0] = maze[0][0];
		pq.push(iii(0, ii(0, 0)));

		while(!pq.empty())
		{
			iii front = pq.top(); pq.pop();
			int d = front.first, r = front.second.first, c = front.second.second;
			if(d > dist[(r*M) + c]) continue;
			if(r-1 >= 0)
			{
				int newr = r-1, cost = maze[newr][c];
				if(dist[(r*M) + c] + cost < dist[(newr*M) + c])
				{
					dist[(newr*M) + c] = dist[(r*M) + c] + cost;
					pq.push(iii(dist[(newr*M) + c], ii(newr, c)));
				}
			}
			if(c-1 >= 0)
			{
				int newc = c-1, cost = maze[r][newc];
				if(dist[(r*M) + c] + cost < dist[(r*M) + newc])
				{
					dist[(r*M) + newc] = dist[(r*M) + c] + cost;
					pq.push(iii(dist[(r*M) + newc], ii(r, newc)));
				}
			}
			if(r+1 < N)
			{
				int newr = r+1, cost = maze[newr][c];
				if(dist[(r*M) + c] + cost < dist[(newr*M) + c])
				{
					dist[(newr*M) + c] = dist[(r*M) + c] + cost;
					pq.push(iii(dist[(newr*M) + c], ii(newr, c)));
				}
			}
			if(c+1 < M)
			{
				int newc = c+1, cost = maze[r][newc];
				if(dist[(r*M) + c] + cost < dist[(r*M) + newc])
				{
					dist[(r*M) + newc] = dist[(r*M) + c] + cost;
					pq.push(iii(dist[(r*M) + newc], ii(r, newc)));
				}
			}
		}

		cout << dist[(N*M)-1] << endl;
	}
	return 0;
}