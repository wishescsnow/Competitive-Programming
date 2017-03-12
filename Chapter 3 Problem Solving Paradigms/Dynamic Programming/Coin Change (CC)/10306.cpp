#include <iostream>
#include <cstdlib>
#include <cstring>
#include <limits.h>

using namespace std;

int memo[301][301];
pair<int, int> coins[45];

int main()
{
	int n, m, S, cv, iv;
	cin >> n;
	while(n--)
	{
		cin >> m >> S;
		for(int i=0;i<m;i++)
		{
			cin >> cv >> iv;
			coins[i].first = cv;
			coins[i].second = iv;
		}

		for(int i =0;i<=S;i++)
        {
        	for(int j = 0;j<=S;j++)
        	{
        		memo[i][j] = INT_MAX;
        	}
        }

		memo[0][0] = 0;

		for (int i = 0; i < m; ++i)
            for (int x = coins[i].first; x <= S; x++)
                for (int y = coins[i].second; y <= S; y++)
                    if (memo[x-coins[i].first][y-coins[i].second] != INT_MAX)
                        memo[x][y] = min(memo[x][y], memo[x-coins[i].first][y-coins[i].second] + 1);

        int ans = INT_MAX;
        int t = S * S;
        for (int i = 0; i <= S; ++i)
            for (int j = 0; j <= S; ++j)
                if (i * i + j * j == t && memo[i][j] != INT_MAX)
                    if (ans > memo[i][j])
                        ans = memo[i][j];

        if (ans != INT_MAX)
            cout << ans << endl;
        else
            cout << "not possible" << endl;
	}
	return 0;
}
