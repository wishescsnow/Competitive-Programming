#include <iostream>
#include <string.h>

using namespace std;

int coins[] = {1, 5, 10, 25, 50};
unsigned long long memo[30010];

int main()
{
	memset(memo, 0, sizeof memo);
	memo[0] = 1;

	for(int i=0;i<5;i++)
	{
		for(int j=coins[i];j<=30000;j++)
		{
			memo[j] += memo[j-coins[i]];
		}
	}

	int n;
	while(cin >> n)
	{
		if(memo[n] == 1)
		{
			cout << "There is only 1 way to produce " << n << " cents change." << endl;
		}
		else
			cout << "There are " << memo[n] << " ways to produce " << n << " cents change." << endl;
	}
	return 0;
}
