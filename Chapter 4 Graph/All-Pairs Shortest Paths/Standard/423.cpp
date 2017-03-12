/*input
5
50
30 5
100 20 50
10 x x 10
*/
#include <iostream>
#include <sstream>
#define INF 1000000000

using namespace std;
int adjMat[110][110];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	string temp;
	cin >> n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i == j)
				adjMat[i][j] = 0;
			if(i > j)
			{
				cin >> temp;
				if(temp[0] == 'x')
				{
					adjMat[i][j] = INF;
					adjMat[j][i] = INF;
				}
				else
				{
					int c;
					stringstream ss(temp);
					ss >> c;
					adjMat[i][j] = c;
					adjMat[j][i] = c;
				}
			}
		}
	}

	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				adjMat[i][j] = min(adjMat[i][j], adjMat[i][k]+adjMat[k][j]);

	int ans = 0;
	for(int j=2;j<=n;j++)
	{
		if(adjMat[1][j] > ans && adjMat[1][j] != INF)
			ans = adjMat[1][j];
	}

	cout << ans << endl;
	return 0;
}