/*input
100
3
25 50 75
10
4
4 5 7 8
0
*/
#include <iostream>
#include <string.h>

using namespace std;

int dp[55][55];
int cuts[55];

int recursive(int left, int right)
{
	if(dp[left][right] != -1)
		return dp[left][right];

	if(right == left + 1)
		return dp[left][right] = 0;

	int sol = 1000000;

	for(int i=left+1;i<right;i++)
	{
		sol = min(sol, recursive(left, i) + cuts[i] - cuts[left] + recursive(i, right) + cuts[right] - cuts[i]);
	}

	return dp[left][right] = sol;
}

int main()
{
	int l, n;
	while(cin >> l && l != 0)
	{
		cin >> n;
		for(int i=1;i<=n;i++)
			cin >> cuts[i];
		cuts[0] = 0;
		cuts[n+1] = l;

		int row = n+10;
		memset(dp, -1, sizeof dp);

		int ans = recursive(0, n+1);

		cout << "The minimum cutting is " << ans << "." << endl;
	}
	return 0;
}