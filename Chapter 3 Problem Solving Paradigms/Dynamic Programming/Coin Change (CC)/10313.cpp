#include <iostream>
#include <sstream>
#include <string.h>

using namespace std;

unsigned long long memo[310][310];

int main()
{
	memset(memo, 0, sizeof memo);
	memo[0][0] = 1;

	for(int i=1;i<=300;i++)
	{
		for(int j=i;j<=300;j++)
		{
			if(j - i >= i)
				memo[i][j] = memo[i-1][j] + memo[i][j - i];
			else
				memo[i][j] = memo[i-1][j] + memo[j - i][j - i];
		}
	}

	int count, N, L1, L2;
	string buf;
	while(getline(cin, buf))
	{
		count = 0;
		stringstream ss(buf);
		if(ss >> N)
			count ++;
		if(ss >> L1)
			count ++;
		if(ss >> L2)
			count ++;

		if(count == 1)
		{
			cout << memo[N][N] << endl;
		}
		else if(count == 2)
		{
			if(L1 > N)
				cout << memo[N][N] << endl;
			else
				cout << memo[L1][N] << endl;
		}
		else if(count == 3)
		{
			if(L2 > N && L1 > N)
				cout << 0 << endl;
			else if(L2 > N)
			{
				if(L1 - 1 < 0)
					cout << memo[N][N] << endl;
				else
					cout << memo[N][N] - memo[L1-1][N] << endl;
			}
			else
			{
				if(L1 - 1 < 0)
					cout << memo[L2][N] << endl;
				else
					cout << memo[L2][N] - memo[L1-1][N] << endl;
			}
		}
		else
			break;
	}
	return 0;
}
