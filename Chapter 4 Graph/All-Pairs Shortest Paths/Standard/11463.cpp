/*input
3
4
3
0 1
2 1
1 3
0 3
2
1
0 1
1 0
4
3
0 1
2 1
1 3
0 0
*/
#include <iostream>
#define INF 1000000000

using namespace std;
int adjMat[110][110];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int T, N, R, u, v, s, d;
	cin >> T;
	for(int t=1;t<=T;t++)
	{
		cin >> N >> R;
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
			{
				if(i == j)
					adjMat[i][j] = 0;
				else
					adjMat[i][j] = INF;
			}

		while(R--)
		{
			cin >> u >> v;
			adjMat[u][v] = 1;
			adjMat[v][u] = 1;
		}

		cin >> s >> d;
		for(int k=0;k<N;k++)
			for(int i=0;i<N;i++)
				for(int j=0;j<N;j++)
					adjMat[i][j] = min(adjMat[i][j], adjMat[i][k] + adjMat[k][j]);

		int ans = -1;
		for(int i=0;i<N;i++)
			ans = max(ans, adjMat[s][i] + adjMat[i][d]);

		cout << "Case " << t << ": " << ans << endl;
	}
	return 0;
}