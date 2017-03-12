#include <iostream>

using namespace std;

int cycleLength(int n, int count)
{
	if(n == 1)
		return count;
	else
	{
		if(n%2 == 1)
			n = (3*n)+1;
		else
			n = n/2;
		return cycleLength(n, ++count);
	}
}

int main()
{
	int i, j, temp;
	while(cin >> i && cin >> j)
	{
		int ans = 0;
		if(i < j)
		{
			for(int a=i;a<=j;a++)
			{
				temp = cycleLength(a, 1);
				if(temp > ans)
					ans = temp;
			}
		}
		else
		{
			for(int a=j;a<=i;a++)
			{
				temp = cycleLength(a, 1);
				if(temp > ans)
					ans = temp;
			}
		}
		cout << i << " " << j << " " << ans << endl;
	}
	return 0;
}
