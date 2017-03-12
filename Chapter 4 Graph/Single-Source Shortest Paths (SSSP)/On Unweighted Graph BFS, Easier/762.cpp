/*input
9
JV PT
JV TA
JV DA
PT KA
KA HP
DA TA
DA HP
HP AP
AP TA
JV DA
9
JV PT
JV TA
JV DA
PT KA
KA HP
DA TA
DA HP
HP AP
AP TA
JV AP
9
JV PT
JV TA
JV DA
PT KA
KA HP
DA TA
DA HP
HP AP
AP TA
JV HP
8
JV PT
JV TA
PT KA
KA HP
DA TA
DA HP
HP AP
AP TA
JV HP
*/
#include <iostream>
#include <queue>
#include <map>
#include <vector>

using namespace std;
vector<vector<int> > adjList;
vector<bool> visited;
vector<int> parent;
queue<int> BFS;
map<string, int> mapper;
map<int, string> reverse;

void printRoute(int index)
{
	if(parent[parent[index]] != -1)
		printRoute(parent[index]);
	cout << reverse[parent[index]] << " " << reverse[index] << endl;
}

int main()
{
	int N, i1, i2, idx, caseNum = 0;
	string s1, s2;
	while(cin >> N)
	{
		if(caseNum++)
			cout << endl;

		idx = 0;
		reverse.clear();
		mapper.clear();
		adjList.clear();
		adjList.resize(1000);
		visited.clear();
		visited.assign(1000, false);
		parent.clear();
		parent.assign(1000, -1);
		while(N--)
		{
			cin >> s1 >> s2;
			if(mapper.find(s1) == mapper.end())
			{
				mapper[s1] = i1 = idx++;
				reverse[idx-1] = s1;
			}
			else
				i1 = mapper[s1];

			if(mapper.find(s2) == mapper.end())
			{
				mapper[s2] = i2 = idx++;
				reverse[idx-1] = s2;
			}
			else
				i2 = mapper[s2];

			adjList[i1].push_back(i2);
			adjList[i2].push_back(i1);
		}
		cin >> s1 >> s2;
		if(mapper.find(s1) == mapper.end())
		{
			cout << "No route" << endl;
			continue;
		}
		else
			i1 = mapper[s1];

		if(mapper.find(s2) == mapper.end())
		{
			cout << "No route" << endl;
			continue;
		}
		else
			i2 = mapper[s2];

		BFS.push(i1);
		visited[i1] = true;
		while(!BFS.empty())
		{
			int u = BFS.front(); BFS.pop();
			for(int i=0;i<(int)adjList[u].size();i++)
			{
				if(!visited[adjList[u][i]])
				{
					visited[adjList[u][i]] = true;
					parent[adjList[u][i]] = u;
					BFS.push(adjList[u][i]);
				}
			}
		}

		if(parent[i2] == -1)
		{
			cout << "No route" << endl;
			continue;
		}
		else
			printRoute(i2);
	}
	return 0;
}