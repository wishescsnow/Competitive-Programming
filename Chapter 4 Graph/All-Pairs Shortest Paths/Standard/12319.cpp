/*input
5
1 2 3
2 1 5
3 4 5 1
4 3 5
5 2 3 4
1 2
2 5
3 1 4
4 5
5 3
1 2
5
1 2 3
2 1 5
3 4 5 1
4 3 5
5 2 3 4
1 2
2 5
3 1 4
4 5
5 3
2 0
3
1 2
2 1 3
3 1 2
1 2
2 3
3 1
0 2
0
*/
#include <iostream>
#include <sstream>
#define INF 1000000000

using namespace std;
int adjMat1[110][110];
int adjMat2[110][110];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, v, A, B;
	string lines;
	while(cin >> n && n != 0)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				if(i == j)
				{
					adjMat1[i][j] = 0;
					adjMat2[i][j] = 0;
				}
				else
				{
					adjMat1[i][j] = INF;
					adjMat2[i][j] = INF;
				}
			}
		}

		getline(cin, lines);
		for(int i=1;i<=n;i++)
		{
			getline(cin, lines);
			stringstream ss(lines);
			ss >> v;
			while(ss >> v)
				adjMat1[i][v] = 1;
		}

		for(int i=1;i<=n;i++)
		{
			getline(cin, lines);
			stringstream ss(lines);
			ss >> v;
			while(ss >> v)
				adjMat2[i][v] = 1;
		}

		for(int k=1;k<=n;k++)
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
				{
					adjMat1[i][j] = min(adjMat1[i][j], adjMat1[i][k] + adjMat1[k][j]);
					adjMat2[i][j] = min(adjMat2[i][j], adjMat2[i][k] + adjMat2[k][j]);
				}

		cin >> A >> B;
		bool ans = true;
		for(int i=1;i<=n;i++)
		{
			if(!ans)
				break;
			for(int j=1;j<=n;j++)
			{
				if(adjMat2[i][j] > ((A*adjMat1[i][j]) + B))
				{
					ans = false;
					break;
				}
			}
		}

		if(ans)
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
	return 0;
}