#include <iostream>
#include <queue>
using namespace std;

queue<int> anslist;
int track[15][110];
int dp[15][110];
int input[15][110];

int main() {
	int m, n, ans, row;
	while(cin >> m && cin >> n)
	{
		for(int i=0;i<m;i++)
		{
			for(int j=0;j<n;j++)
			{
				cin >> input[i][j];
			}
		}

		for(int j=n-1;j>=0;j--)
		{
			for(int i=0;i<m;i++)
			{
				if(j==n-1)
				{
					dp[i][j] = input[i][j];
				}
				else
				{
					int minus = i-1 < 0? m-1:i-1;
					int plus = i+1 > m-1? 0:i+1;
					int minval = min(dp[i][j+1], min(dp[minus][j+1], dp[plus][j+1]));

					if(plus == 0)
					{
						if(minval == dp[i][j+1])
						{
							track[i][j] = i;
						}
						if(minval == dp[minus][j+1])
						{
							track[i][j] = minus;
						}
						if(minval == dp[plus][j+1])
						{
							track[i][j] = plus;
						}
					}
					else if(minus == m-1)
					{
						if(minval == dp[minus][j+1])
						{
							track[i][j] = minus;
						}
						if(minval == dp[plus][j+1])
						{
							track[i][j] = plus;
						}
						if(minval == dp[i][j+1])
						{
							track[i][j] = i;
						}
					}
					else
					{
						if(minval == dp[plus][j+1])
						{
							track[i][j] = plus;
						}
						if(minval == dp[i][j+1])
						{
							track[i][j] = i;
						}
						if(minval == dp[minus][j+1])
						{
							track[i][j] = minus;
						}
					}

					dp[i][j] = minval + input[i][j];
				}
			}
		}

		ans = 2147483647;

		for(int i=0;i<m;i++)
		{
			if(dp[i][0] < ans)
			{
				ans = dp[i][0];
				row = i;
			}
		}

		for(int j=0;j<n;j++)
		{
			anslist.push(row+1);
			row = track[row][j];
		}

		for(int j=0;j<n;j++)
		{
			cout << anslist.front();
			if(j != n-1)
				cout << " ";
			anslist.pop();
		}
		cout << endl << ans << endl;
	}
	return 0;
}
