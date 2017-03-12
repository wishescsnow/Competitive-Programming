/*input
3 6 5
NEESWE
WWWESS
SNWWWW
4 5 1
SESWE
EESNW
NWEEN
EWSEN
0 0 0
*/
#include <iostream>
#include <string.h>

using namespace std;

int r, c, idx;
int check[20][20];
int grid[20][20];

void move(int steps, int x, int y)
{
	if(x == 0 || y == 0 || x > r || y > c)
	{
		cout << steps << " step(s) to exit" << endl;
		return;
	}

	if(check[x][y] != -1)
	{
		cout << check[x][y] << " step(s) before a loop of " << steps-check[x][y] << " step(s)" << endl;
		return;
	}

	check[x][y] = steps;

	switch(grid[x][y])
	{
		case 0:
			move(steps+1, x, y+1);
			break;
		case 1:
			move(steps+1, x+1, y);
			break;
		case 2:
			move(steps+1, x, y-1);
			break;
		case 3:
			move(steps+1, x-1, y);
			break;
	}
}

int main()
{
	char temp;
	while((cin >> r >> c >> idx) && r != 0 && c != 0 && idx != 0)
	{
		memset(check, -1, sizeof check);
		for(int i=1;i<=r;i++)
			for(int j=1;j<=c;j++)
			{
				cin >> temp;
				switch(temp)
				{
					case 'E':
						grid[i][j] = 0;
						break;
					case 'S':
						grid[i][j] = 1;
						break;
					case 'W':
						grid[i][j] = 2;
						break;
					case 'N':
						grid[i][j] = 3;
						break;
				}
			}

		move(0, 1, idx);
	}
	return 0;
}