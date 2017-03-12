/*input
5 3
1 1 E
RFRFRFRF
3 2 N
FRRFLLFFRRFLL
0 3 W
LLFFFLFLFL
*/
#include <iostream>
#include <string.h>

using namespace std;

typedef pair<int, int> ii;
typedef pair<char, ii> cii;

bool grid[55][55];

int main()
{
	int x, y;
	int curx, cury;
	char direc;
	bool out;
	string operations;

	cin >> x >> y;
	memset(grid, false, sizeof grid);

	while(cin >> curx >> cury >> direc >> operations)
	{
		cii curRobot = make_pair(direc, make_pair(curx, cury));
		for(string::iterator it = operations.begin(); it != operations.end(); it++)
		{
			out = false;
    		char ope = (*it);
    		if(ope == 'L')
    		{
    			switch(curRobot.first)
    			{
    				case 'E':
    					curRobot.first = 'N';
    					break;
    				case 'S':
    					curRobot.first = 'E';
    					break;
    				case 'W':
    					curRobot.first = 'S';
    					break;
    				case 'N':
    					curRobot.first = 'W';
    					break;
    			}
    		}
    		else if(ope == 'R')
    		{
    			switch(curRobot.first)
    			{
    				case 'E':
    					curRobot.first = 'S';
    					break;
    				case 'S':
    					curRobot.first = 'W';
    					break;
    				case 'W':
    					curRobot.first = 'N';
    					break;
    				case 'N':
    					curRobot.first = 'E';
    					break;
    			}
    		}
    		else
    		{
    			ii oldpos = curRobot.second;
    			switch(curRobot.first)
    			{
    				case 'E':
    					curRobot.second.first += 1;
    					break;
    				case 'S':
    					curRobot.second.second -= 1;
    					break;
    				case 'W':
    					curRobot.second.first -= 1;
    					break;
    				case 'N':
    					curRobot.second.second += 1;
    					break;
    			}

    			if(curRobot.second.first < 0 || curRobot.second.second < 0 ||
    				curRobot.second.first > x || curRobot.second.second > y)
    			{
    				if(grid[oldpos.first][oldpos.second])
    				{
    					curRobot.second = oldpos;
    					continue;
    				}

    				grid[oldpos.first][oldpos.second] = true;
    				curRobot.second = oldpos;
    				out = true;
    				break;
    			}
    		}
		}

		cout << curRobot.second.first << " " << curRobot.second.second << " " << curRobot.first;
		if(out)
			cout << " LOST" << endl;
		else
			cout << endl;
	}
	return 0;
}