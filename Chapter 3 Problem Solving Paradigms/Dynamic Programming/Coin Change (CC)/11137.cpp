#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long int64;
typedef unsigned long long uint64;

uint64 memo[10010];

int main()
{
	memo[0] = 1;

	for(int i=1;i<=21;i++)
	{
		int c = pow(i,3);
		for(int j = c;j<10000;j++)
		{
			memo[j] += memo[j-c];
		}
	}

	int x;
	while(cin >> x)
	{
		cout << memo[x] << endl;
	}
	return 0;
}
