#include <iostream>
#include <string.h>

using namespace std;

bool map[110][110];
int height[110][110];
int left1[110][110];
int right1[110][110];
int left2[110][110];
int right2[110][110];

int main()
{
	int M, N, ans;
	while(cin >> M && cin >> N && M !=0 && N != 0)
	{
		ans = 0;
		memset(map, 1, sizeof map);
		memset(height, 0, sizeof height);
		memset(left1, 0, sizeof left1);
		memset(right1, 0, sizeof right1);
		memset(left2, 0, sizeof left2);
		memset(right2, 0, sizeof right2);

		for(int i=1;i<=M;i++)
		{
			for(int j=1;j<=N;j++)
			{
				cin >> map[i][j];
			}
		}

		for(int i=1;i<=M;i++)
		{
			for(int j=1;j<=N;j++)
			{
				height[i][j] = map[i][j] ? 0 : height[i-1][j] + 1;
				left1[i][j] = map[i][j-1] ? j : left1[i][j-1];
			}

			map[i][N+1] = 1;

			for(int j=N;j>=1;j--)
			{
				right1[i][j] = map[i][j+1] ? j : right1[i][j+1];

				if(height[i][j] == 1)
				{
					right2[i][j] = right1[i][j];
					left2[i][j] = left1[i][j];
				}
				else
				{
					right2[i][j] = min(right1[i][j], right2[i-1][j]);
					left2[i][j] = max(left1[i][j], left2[i-1][j]);
				}

				int area = height[i][j] * (right2[i][j] - left2[i][j] + 1);
				if (area > ans)
					ans = area;
			}
		}

		cout << ans << endl;
	}
	return 0;
}
