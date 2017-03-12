/*input
5
2  3 3   4 6
3  1 2   3 7   5 6
1  4 5
0
1  4 7
2 4
2
1   2 5
1   1 6
1 2
7
4   2 5   3 13   4 8   5 18
2   3 7   6 14
1   6 6
2   3 5   5 9
3   6 2   7 9    4 6
1   7 2
0
1 7
0
*/
#include <iostream>
#include <string.h>
#define INF 1000000000

using namespace std;
int adjMat[15][15];
int path[15][15];

void print_path(int s, int e)
{
	if(path[s][e] == s)
	{
		cout << path[s][e];
		return;
	}

	else
	{
		print_path(s, path[s][e]);
		cout << " " << path[s][e];
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int V, n, u, d, t = 1;
	while(cin >> V && V != 0)
	{
		for(int i=1;i<=V;i++)
		{
			for(int j=1;j<=V;j++)
			{
				path[i][j] = 0;
				if(i == j)
					adjMat[i][j] = 0;
				else
					adjMat[i][j] = INF;
			}
		}

		for(int i=1;i<=V;i++)
		{
			cin >> n;
			while(n--)
			{
				cin >> u >> d;
				adjMat[i][u] = d;
			}
		}

		for(int i=1; i<=V; i++)
		{
			for(int j=1; j<=V; j++)
			{
				if(adjMat[i][j] != INF && i != j)
					path[i][j] = i;
			}
		}

		for(int k=1;k<=V;k++)
			for(int i=1;i<=V;i++)
				for(int j=1;j<=V;j++)
				{
					int temp = adjMat[i][k]+adjMat[k][j];
					if(adjMat[i][j] > temp)
					{
						adjMat[i][j] = temp;
						path[i][j] = path[k][j];
					}
				}

		cin >> u >> d;
		cout << "Case " << t++ << ": Path = ";
		print_path(u, d);
		cout << " " << d << "; " << adjMat[u][d] << " second delay" << endl;
	}
	return 0;
}