/*input
4
2 1155 2211
3 1111 1155 5511
3 1234 5678 9090
4 2145 0213 9113 8113
*/
#include <iostream>
#include <string.h>
#include <queue>

using namespace std;
typedef pair<int, int> ii;
vector<vector<ii> > adjList;
vector<bool> taken;
priority_queue<ii> pq;
char keys[510][10];

void process(int v)
{
	taken[v] = true;
	for(int i=0;i<(int)adjList[v].size();i++)
	{
		ii front = adjList[v][i];
		pq.push(make_pair(-front.second, -front.first));
	}
}

int calWeight(char s1[], char s2[])
{
	int weight = 0;
	int w1, w2;
	for(int i=0;i<4;i++)
	{
		w1 = (s1[i]-'0') - (s2[i]-'0');
		w2 = (s2[i]-'0') - (s1[i]-'0');
		if(w1 == 0)
			continue;
		if(w1 < 0)
			w1 = 10 + w1;
		else
			w2 = 10 + w2;
		weight += min(w1, w2);
	}
	return weight;
}

int main()
{
	int T, N, ans;
	char temp[10];
	cin >> T;
	while(T--)
	{
		cin >> N;

		for(int i=0;i<=N;i++)
		{
			if(i==0)
			{
				for(int j=0;j<4;j++)
					keys[i][j] = '0';
				keys[i][4] = '\0';
				continue;
			}

			cin >> temp;
			for(int j=0;j<4;j++)
				keys[i][j] = temp[j];
			keys[i][4] = '\0';
		}

		adjList.clear();
		taken.clear();
		adjList.assign(N+1, vector<ii>());
		taken.assign(N+1, false);

		for(int i=0;i<=N-1;i++)
		{
			if(i == 0)
			{
				int minW = -1, idx;
				for(int j=i+1;j<=N;j++)
				{
					int w = calWeight(keys[i], keys[j]);
					if(minW == -1)
					{
						minW = w;
						idx = j;
					}
					else if(w < minW)
					{
						minW = w;
						idx = j;
					}
				}
				adjList[i].push_back(make_pair(idx, minW));
			}
			else
			{
				for(int j=i+1;j<=N;j++)
				{
					int w = calWeight(keys[i], keys[j]);
					adjList[i].push_back(make_pair(j, w));
					adjList[j].push_back(make_pair(i, w));
				}
			}
		}

		process(0);

		ans = 0;
		while(!pq.empty())
		{
			ii front = pq.top(); pq.pop();
			int u = -front.second, w = -front.first;
			if(!taken[u])
			{
				ans += w;
				process(u);
			}
		}

		cout << ans << endl;
	}
	return 0;
}