#include <iostream>

using namespace std;

int main()
{
	int N;
	cin >> N;
	while(N--)
	{
		int L, ans = 0, car[55];
		cin >> L;
		for(int i=0;i<L;i++)
		{
			cin >> car[i];
		}

		for(int i=0;i<L-1;i++)
		{
			for(int j=i+1;j<L;j++)
			{
				if(car[i] > car[j])
				{
					int temp = car[i];
					car[i] = car[j];
					car[j] = temp;
					ans ++;
				}
			}
		}
		cout << "Optimal train swapping takes " << ans << " swaps." << endl;
	}
	return 0;
}
