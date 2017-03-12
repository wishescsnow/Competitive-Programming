#include <iostream>
#include <string.h>
#include <cmath>

using namespace std;

int coins[110];
bool memo[110][50010];
int n, m, total;

int main()
{
	cin >> n;
	while(n--)
	{
		memset(coins, 0, sizeof coins);
		memset(memo, 0, sizeof memo);
		total = 0;

		cin >> m;

		for(int i=0;i<m;i++)
		{
			cin >> coins[i];
			total += coins[i];
		}

		int ideal = total/2;

		memo[0][0] = 1;
		for(int i=0; i<m; i++){
			for(int j=0; j<=ideal; j++){
				if(memo[i][j]==1){

					memo[i+1][j] = 1;

					if(j+coins[i] <= ideal){
						memo[i+1][j+coins[i]] = 1;
					}
				}
			}
		}

		int left = 0;
		int right = 0;
		for(int i=ideal;i>=0;i--)
		{
			if(memo[m][i] == 1)
			{
				left = i;
				right = abs(total - i);
				break;
			}
		}

		cout << abs(right-left) << endl;
	}
	return 0;
}
