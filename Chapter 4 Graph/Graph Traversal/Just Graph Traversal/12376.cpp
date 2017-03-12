/*input
5
6 6
0 8 9 2 7 5
5 4
5 3
1 5
0 1
0 2
2 1
6 5
0 8 9 2 7 5
5 4
5 3
1 5
0 1
0 2
6 5
0 20 30 40 50 60
0 1
0 2
0 3
0 4
0 5
6 3
0 20 30 40 50 60
0 1
1 5
5 4
2 1
0 1000
0 1
*/
#include <iostream>
#include <string.h>

using namespace std;

int caseNum, n, m, ans;
int learning[110];
bool graph[110][110];

void traverse(int id)
{
	int max = 0, idx = -1;
	for(int i=0;i<n;i++)
	{
		if(graph[id][i] == true && learning[i] > max)
		{
			idx = i;
			max = learning[i];
		}
	}

	if(max == 0 && idx == -1)
	{
		cout << "Case " << caseNum++ << ": " << ans << " " << id << endl;
		return;
	}

	ans += max;
	traverse(idx);
}

int main()
{
	caseNum = 1;
	int T, u, v;
	cin >> T;
	while(T--)
	{
		ans = 0;
		memset(graph, false, sizeof graph);
		cin >> n >> m;
		for(int i=0;i<n;i++)
			cin >> learning[i];

		for(int i=0;i<m;i++)
		{
			cin >> u >> v;
			graph[u][v] = true;
		}

		traverse(0);
	}
	return 0;
}