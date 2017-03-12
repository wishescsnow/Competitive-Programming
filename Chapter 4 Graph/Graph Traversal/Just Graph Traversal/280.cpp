/*input
7
1 2 0
2 3 4 0
3 1 0
4 5 0
5 4 0
6 7 0
7 6 0
0
7 1 2 3 4 5 6 7
5
0
5 1 2 3 4 5
4
1 2 3 4 0
2 3 4 0
3 4 0
0
4 1 2 3 4
3
1 2 0
2 2 0
3 1 2 0
0
2 1 2
4
1 2 0
2 3 0
3 4 0
0
2 2 1
5
1 2 0
2 3 0
3 4 0
4 5 0
1 1 0
0
1 1
0
*/
#include <iostream>
#include <string.h>

using namespace std;

int N;
int count;
bool adjMat[110][110];
bool access[110];

void dfs(int k)
{
	for(int i=1;i<=N;i++)
		if(adjMat[k][i] && !access[i])
		{
			count ++;
			access[i] = true;
			dfs(i);
		}
}

int main()
{
	int i, j, num, k;
	while(cin >> N && N != 0)
	{
		memset(adjMat, false, sizeof adjMat);

		while(cin >> i && i != 0)
			while(cin >> j && j != 0)
				adjMat[i][j] = true;

		cin >> num;

		while(num--)
		{
			memset(access, false, sizeof access);
			count = 0;
			cin >> k;
			dfs(k);

			count = N-count;
			cout << count;
			if(count != 0)
				cout << " ";

			for(int a=1;a<=N;a++)
			{
				if(!access[a])
				{
					cout << a;
					if(--count)
						cout << " ";
				}
			}

			cout << endl;
		}
	}
	return 0;
}