/*input
1
10 5 5
2, 5, 5, 3, 2, 2, 1, 3, 5, 2
*/
#include <iostream>
#include <string.h>
#include <cmath>
#include <cstdlib>

using namespace std;

int dp[210][210][10300];
int songs[10300];
string input;

int main()
{
	int N, n, t, m;
	cin >> N;
	while(N--)
	{
		cin >> n >> t >> m;

		for(int i=1;i<=n;i++)
		{
			if(i==n)
				cin >> songs[i];
			else
			{
				cin >> input;
				songs[i] = atoi(input.substr(0, input.find(',')).c_str());
			}
		}

		memset(dp, 0, sizeof(dp[0][0][0])*m*t*n);

		for(int i=1;i<=m;i++)
		{
			for(int j=0;j<=t;j++)
			{
				for(int k=1;k<=n;k++)
				{
					if(j==0)
						dp[i][j][k] = dp[i-1][t][k];

					else if (songs[k] <= j)
						dp[i][j][k] = max(dp[i][j][k-1], dp[i][j-songs[k]][k-1]+1);

    				else if (songs[k] > j)
    					dp[i][j][k] = max(dp[i-1][t][k], dp[i][j][k-1]);
				}
			}
		}

		cout << dp[m][t][n] << endl;
		if(N)
			cout << endl;
	}
	return 0;
}