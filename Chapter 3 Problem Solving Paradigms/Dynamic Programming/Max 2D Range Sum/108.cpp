#include <iostream>
#include <cmath>

using namespace std;

int arr[110][110];

int main()
{
	int N;
	cin >> N;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			cin >> arr[i][j];
			if(i == 0 && j != 0)
				arr[i][j] += arr[i][j-1];
			else if(j == 0 && i != 0)
				arr[i][j] += arr[i-1][j];
			else if(i != 0 && j != 0)
			{
				arr[i][j] += arr[i-1][j];
				arr[i][j] += arr[i][j-1];
				arr[i][j] -= arr[i-1][j-1];
			}
		}
	}

	int maxsub = -127*100*100;

	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			for(int x=i;x<N;x++)
			{
				for(int y=j;y<N;y++)
				{
					int temp = arr[x][y];
					if(i-1 >= 0)
						temp -= arr[i-1][y];
					if(j-1 >= 0)
						temp -= arr[x][j-1];
					if(i-1 >= 0 && j-1 >=0)
						temp += arr[i-1][j-1];

					maxsub = max(maxsub, temp);
				}
			}
		}
	}

	cout << maxsub << endl;
	return 0;
}
