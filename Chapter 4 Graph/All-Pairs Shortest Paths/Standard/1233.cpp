/*input
31
18 5
2 1 4
1 3 2
1 1 3
2 2 0 1 4
1 3 5
1 5 0
22 5
2 1 4
1 3 2
1 1 3
2 2 0 1 4
1 3 5
1 5 0
24 5
2 1 4
1 3 2
1 1 3
2 2 0 1 4
1 3 5
1 5 0
14 3
1 1
2 7 2 2 3
1 2 0
1 3 2
7 3
1 1
2 7 2 2 3
1 2 0
1 3 2
8 3
1 1
2 7 2 2 3
1 2 0
1 3 2
20 3
1 1
2 7 2 2 3
1 2 0
1 3 2
19 3
1 1
2 7 2 2 3
1 2 0
1 3 2
5 2
1 1
1 5 2
0
5 2
1 1
1 4 2
0
5 2
1 1
1 5 2
1 3 0
10 1
1 1
1 2 0
9 1
1 1
1 2 0
8 1
1 1
1 2 0
5 1
1 1
1 6 0
10 1
1 1
1 8 0
10 3
2 1 2
1 8 0
1 2 3
1 2 2
21 7
2 1 4
1 2 2
1 5 3
2 2 1 4 0
1 2 5
1 2 4
0
0
22 7
2 1 4
1 2 2
1 5 3
2 2 1 4 0
1 2 5
1 2 4
0
0
1000000 1
1 1
1 2 0
8 2
2 1 2
2 4 0 2 2
2 4 0 2 1
100 5
1 1
0
1 2 3
1 2 2
0
0
11 8
2 1 8
1 2 2
1 3 3
3 7 0 2 4 3 5
2 10 2 2 5
1 5 6
3 3 7 6 0 9 3
1 2 0
1 2 7
11 10
3 1 8 9
1 2 2
1 3 3
3 7 0 2 4 3 5
2 10 2 2 5
1 5 6
3 3 7 6 0 9 3
1 2 0
1 2 7
1 2 10
1 2 0
16 10
3 1 8 9
1 2 2
1 3 3
3 7 0 2 4 3 5
2 10 2 2 5
1 5 6
3 3 7 6 0 9 3
1 4 0
1 4 7
1 4 10
1 4 0
100 1
1 1
1 99 0
100 1
1 1
1 100 0
100 9
2 1 2
1 99 0
1 2 3
1 2 4
1 2 5
1 2 6
1 2 7
1 2 8
1 2 9
1 2 0
500 3
1 1
1 2 2
1 2 3
1 2 2
20 7
2 1 4
1 2 2
1 2 3
1 2 1
1 2 5
0
3 2 7 2 0 2 2
1 2 6
8 2
1 1
2 2 2 5 2
1 2 0
0
*/
#include <iostream>
#define INF 1000000000

using namespace std;
int adjMat[510][510];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int c, b, p, n, g, v;
	cin >> c;
	while(c--)
	{
		cin >> b >> p;
		for(int i=0;i<=p;i++)
			for(int j=0;j<=p;j++)
			{
				adjMat[i][j] = INF;
				if(i == j && i != 0)
					adjMat[i][j] = 0;
			}

		cin >> n;
		while(n--)
		{
			cin >> v;
			adjMat[0][v] = 0;
		}

		for(int i=1;i<=p;i++)
		{
			cin >> n;
			while(n--)
			{
				cin >> g >> v;
				adjMat[i][v] = min(g, adjMat[i][v]);
			}
		}

		for(int k=0;k<=p;k++)
			for(int i=0;i<=p;i++)
				for(int j=0;j<=p;j++)
					adjMat[i][j] = min(adjMat[i][j], adjMat[i][k]+adjMat[k][j]);

		int cur = 0, ans = 0;
		while(true)
		{
			cur += adjMat[0][0];
			if(cur >= b)
				break;
			ans++;
			cur--;
		}

		cout << ans << endl;
	}
	cin >> c;
	return 0;
}