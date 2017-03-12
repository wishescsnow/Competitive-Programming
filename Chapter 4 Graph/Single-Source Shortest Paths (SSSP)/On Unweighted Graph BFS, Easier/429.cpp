/*input
2

aa
bb
ac
*
aa ac

aa
ab
bb
*
aa bb
*/
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <queue>

using namespace std;
vector<vector<int> > adjList;
map<string, int> dictionary;
vector<int> visited;
queue<int> BFS;

bool isNeighbor(string s1, string s2)
{
	if(s1 == s2)
		return false;

	if(s1.length() == s2.length())
	{
		int diff = 0;
		for(int i=0;i<s1.length();i++)
		{
			if(s1[i] != s2[i])
				diff++;

			if(diff > 1)
				return false;
		}

		if(diff == 1)
			return true;
	}

	return false;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N, idx;
	string word, s1, s2;
	cin >> N;
	for(int n=0;n<N;n++)
	{
		if(n)
			cout << endl;

		dictionary.clear();
		idx = 0;

		while(cin >> word && word[0] != '*')
		{
			if(dictionary.find(word) == dictionary.end())
				dictionary[word] = idx++;
		}

		adjList.clear();
		adjList.resize(idx);

		for(map<string, int>::iterator itsi = dictionary.begin(); itsi != dictionary.end(); itsi++)
		{
			for(map<string, int>::iterator itsi2 = itsi; itsi2 != dictionary.end(); itsi2++)
			{
				if(isNeighbor((*itsi).first, (*itsi2).first))
				{
					adjList[(*itsi).second].push_back((*itsi2).second);
					adjList[(*itsi2).second].push_back((*itsi).second);
				}
			}
		}

		while(!BFS.empty())
			BFS.pop();

		getline(cin, word);
		while(getline(cin, word))
		{
			visited.clear();
			visited.assign(idx, -1);
			if(word.length() == 0)
				break;
			stringstream strs(word);
			strs >> s1 >> s2;
			int i1 = dictionary[s1], i2 = dictionary[s2];
			BFS.push(i1);
			visited[i1] = 0;
			while(!BFS.empty())
			{
				int u = BFS.front(); BFS.pop();
				for(int i=0;i<(int)adjList[u].size();i++)
				{
					if(visited[adjList[u][i]] == -1)
					{
						visited[adjList[u][i]] = visited[u] + 1;
						if(adjList[u][i] == i2)
							break;
						BFS.push(adjList[u][i]);
					}
				}
			}

			cout << s1 << " " << s2 << " " << visited[i2] << endl;
		}
	}
	return 0;
}