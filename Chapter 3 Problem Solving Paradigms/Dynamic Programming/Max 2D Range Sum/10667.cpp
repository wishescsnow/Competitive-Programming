#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;

bool board[110][110];
int height[110][110];
int left1[110][110];
int right1[110][110];
int left2[110][110];
int right2[110][110];

int main() {
	int p, s, n, r1, c1, r2, c2, ans;
	cin >> p;

	while(p--)
	{
	    ans = 0;
	    cin >> s >> n;

	    memset(board, 0, sizeof board);
	    memset(height, 0, sizeof height);
	    memset(left1, 0, sizeof left1);
	    memset(right1, 0, sizeof right1);
	    memset(left2, 0, sizeof left2);
	    memset(right2, 0, sizeof right2);

	    while(n--)
	    {
	        cin >> r1 >> c1 >> r2 >> c2;
	        for(int i=r1;i<=r2;i++)
	        {
	            for(int j=c1;j<=c2;j++)
	            {
	                board[i][j] = 1;
	            }
	        }
	    }

	    for(int i=0;i<=s;i++)
	    {
	    	for(int j=0;j<=s;j++)
	    	{
	    		if(i == 0 || j == 0)
	    		{
	    			board[i][j] = 1;
	    			continue;
	    		}
	    		height[i][j] = ((board[i][j] == 0) ? (height[i-1][j] + 1) : 0);
	            left1[i][j] = ((board[i][j-1] == 1) ? j : left1[i][j-1]);
	    	}

	    	board[i][s+1] = 1;

	        for(int j=s;j>=1;j--)
	        {
	        	if(i == 0)
	        		continue;
	        	right1[i][j] = ((board[i][j+1] == 1) ? j : right1[i][j+1]);

	            if(height[i][j] == 1)
	            {
					left2[i][j] = left1[i][j];
					right2[i][j] = right1[i][j];
				}
				else
				{
					left2[i][j] = max(left1[i][j], left2[i-1][j]);
					right2[i][j] = min(right1[i][j], right2[i-1][j]);
				}

	            int width = right2[i][j] - left2[i][j] + 1;
	            int area = height[i][j] * width;

	            if(area > ans)
	            	ans = area;
	        }
	    }

	    cout << ans << endl;
	}
	return 0;
}
