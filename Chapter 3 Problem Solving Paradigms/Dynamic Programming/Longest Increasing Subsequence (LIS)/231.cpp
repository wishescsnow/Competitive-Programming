#include <cstdio>
#include <vector>

using namespace std;

int main()
{
	int height, counter = 0, ans, casenum = 0;
	vector<int> missles;
	while(scanf("%d\n", &height) == 1)
	{
		if(height == -1)
		{
			counter ++;
			casenum ++;
			if(!missles.empty())
			{
				ans = 1;
				int size = missles.size();
				vector<int> states(size+10, 1);

				for(int i=1;i<size;i++)
				{
					for(int j=0;j<i;j++)
					{
						//printf("Left : %d Right : %d\n", missles[j], missles[i]);
						if(missles[j] >= missles[i])
						{
							states[i] = max(states[i], 1+states[j]);
						}
					}
					if(states[i] > ans)
						ans = states[i];
				}

				//printf("States:\n");

				//for(int i=0;i<size;i++)
				//{
				//	printf("%d\n", states[i]);
				//}

				printf("Test #%d:\n  ", casenum);
				printf("maximum possible interceptions: %d\n", ans);
			}
			missles.clear();
			continue;
		}
		if(counter == 2)
			break;

		if(counter == 1)
		{
			printf("\n");
		}
		counter = 0;

		missles.push_back(height);
	}
	return 0;
}
