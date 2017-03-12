#include <iostream>
#include <string.h>

using namespace std;

int coins[] = {1, 5, 10, 25, 50};
long long memo[8000];
int MAXN = 7489;

int main()
{
	int amount;
	memset(memo, 0, sizeof memo);
	memo[0] = 1;

	for(int i=0;i<5;i++)
	{
		for(int j=coins[i];j<=MAXN;j++)
		{
			memo[j] += memo[j-coins[i]];
		}
	}

	while(cin >> amount)
	{
		cout << memo[amount] << endl;
	}
	return 0;
}
