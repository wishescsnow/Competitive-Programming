/*input
1
7 8
********
* * * **
* * *
* * ** *
* * * *
* * **
********
2 4
RRFLFF FFR
FF
RFFQ
*/
#include <stdio.h>
#include <string.h>

using namespace std;

char face;
bool grid[70][70];

int main()
{
	int N, r, c, a, b, num = 0;
	char temp[70][70];
	char ope;
	bool end;
	scanf("%d\n\n", &N);
	while(N--)
	{
		face = 'N';
		end = false;
		scanf("%d %d\n", &r, &c);

		for(int i = 0 ; i < r; i++)
		{
			gets(temp[i]);
			for (int j = 0; j < c; j++)
			{
				if(temp[i][j] == '*')
					grid[i+1][j+1] = false;

				else if(temp[i][j] == ' ')
					grid[i+1][j+1] = true;
			}
		}

		scanf("%d %d\n", &a, &b);
		while(scanf("%c", &ope) == 1 && !end)
		{
			if(ope == ' ' || ope == '\n' || ope == '\t')
				continue;

			switch(ope)
			{
				case 'R':
					switch(face)
					{
						case 'E':
							face = 'S';
							break;
						case 'S':
							face = 'W';
							break;
						case 'W':
							face = 'N';
							break;
						case 'N':
							face = 'E';
							break;
					}
					break;
				case 'L':
					switch(face)
					{
						case 'E':
							face = 'N';
							break;
						case 'S':
							face = 'E';
							break;
						case 'W':
							face = 'S';
							break;
						case 'N':
							face = 'W';
							break;
					}
					break;
				case 'F':
					switch(face)
					{
						case 'E':
							if(grid[a][b+1])
								b = b+1;
							break;
						case 'S':
							if(grid[a+1][b])
								a = a+1;
							break;
						case 'W':
							if(grid[a][b-1])
								b = b-1;
							break;
						case 'N':
							if(grid[a-1][b])
								a = a-1;
							break;
					}
					break;
				case 'Q':
					if(num++)
						printf("\n");
					printf("%d %d %c\n", a, b, face);
					end = true;
					break;
			}
		}
	}
	return 0;
}