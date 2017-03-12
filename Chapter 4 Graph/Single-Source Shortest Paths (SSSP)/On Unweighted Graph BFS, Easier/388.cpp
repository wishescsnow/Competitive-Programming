/*input
7
A 3.64 BCD*
B 3.77 A
C 6.9 ADE
D 8.84 ACG
E 3.52 C*
G 0.97 D
H 2.38 *
5
A 4.76 MX
M 9.63 *AG
G 1.59 MD
X 6.78 A*D
D 6.04 GX
2
B 4.4 *A
A 4.4 *B
1
C 0.01 *
4
A 8.99 BCD
B 6.98 *ACD
C 0.73 DBA
D 6.88 ABC
*/
#include <iostream>
#include <algorithm>
#include <queue>
#include <math.h>
#include <string.h>
#include <vector>

using namespace std;
vector<vector<int> > adjList;
vector<double> valueList;
vector<int> visited;
queue<int> BFS;

int main()
{
	int N, idx, dst;
	double value;
	char temp[30], ans;
	while(cin >> N)
	{
		value = -1.0;
		adjList.clear();
		adjList.resize(30);
		valueList.clear();
		valueList.assign(30, -1);
		visited.clear();
		visited.assign(30, -1);
		while(N--)
		{
			cin >> temp;
			idx = temp[0]-'A';
			cin >> valueList[idx];
			cin >> temp;
			for(int i=0;i<strlen(temp);i++)
			{
				if(temp[i] == '*')
				{
					adjList[idx].push_back(26);
					adjList[26].push_back(idx);
				}
				else
				{
					dst = temp[i]-'A';
					adjList[idx].push_back(dst);
				}
			}
			sort(adjList[idx].begin(), adjList[idx].end());
		}

		sort(adjList[26].begin(), adjList[26].end());

		BFS.push(26);
		visited[26] = 0;
		while(!BFS.empty())
		{
			int u = BFS.front(); BFS.pop();
			for(int i=0;i<(int)adjList[u].size();i++)
			{
				if(visited[adjList[u][i]] == -1)
				{
					visited[adjList[u][i]] = visited[u] + 1;
					BFS.push(adjList[u][i]);
				}
			}
		}

		for(int i=0;i<26;i++)
		{
			if(visited[i] == -1)
				continue;

			if(valueList[i] * pow(0.95, visited[i]-1) > value)
			{
				value = valueList[i] * pow(0.95, visited[i]-1);
				ans = i+'A';
			}
		}

		cout << "Import from " << ans << endl;
	}
	return 0;
}