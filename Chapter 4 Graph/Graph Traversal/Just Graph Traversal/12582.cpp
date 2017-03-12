/*input
7
AEFFGGEBDDCCBA
ZAAFFZ
AA
AEFFGGEBDDCCBA
AA
AEFFGGEBDDCCBA
ZAAZ
*/
#include <iostream>
#include <map>
#include <stack>

using namespace std;
stack<char> s;
map<char, int> mapper;
string sprinklers;

void dfs(int i)
{
	if(i >= sprinklers.length())
		return;

	if(s.empty())
	{
		s.push(sprinklers[i]);
		mapper[sprinklers[i]] = -1;
		dfs(i+1);
		return;
	}

	if(sprinklers[i] == s.top())
	{
		mapper[sprinklers[i]] ++;
		s.pop();
	}
	else
	{
		mapper[s.top()] ++;
		s.push(sprinklers[i]);
	}

	dfs(i+1);
}

int main()
{
	int n;
	cin >> n;
	for(int i=1;i<=n;i++)
	{
		sprinklers.clear();
		mapper.clear();

		cout << "Case " << i << endl;
		cin >> sprinklers;
		dfs(0);
		for(map<char, int>::iterator itci = mapper.begin();itci!=mapper.end();itci++)
		{
			if((*itci).second != 0)
				cout << (*itci).first << " = " << (*itci).second << endl;
		}
	}
	return 0;
}