/*input
0000 9999 1
1000
0000 9999 1
0001
5234 1212 3
1023 0101 0001
0 0 0
*/
#include <iostream>
#include <string.h>
#include <queue>

using namespace std;
vector<int> buttons;
int visited[10000];
queue<int> BFS;

int sum(int i1, int i2)
{
	int ans = i1 + i2;
	if(ans > 9999)
		ans = ans - 10000;
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int L, U, R, button, caseNum = 1;
	while((cin >> L >> U >> R) && !(L == 0 && U == 0 && R == 0))
	{
		memset(visited, -1, sizeof visited);
		buttons.clear();
		while(R--)
		{
			cin >> button;
			buttons.push_back(button);
		}

		while(!BFS.empty())
			BFS.pop();

		BFS.push(L);
		visited[L] = 0;
		while(!BFS.empty())
		{
			int code = BFS.front(); BFS.pop();
			for(int i=0;i<(int)buttons.size();i++)
			{
				int newCode = sum(code, buttons[i]);
				if(visited[newCode] == -1)
				{
					BFS.push(newCode);
					visited[newCode] = visited[code] + 1;
					if(newCode == U)
						break;
				}
			}
		}

		cout << "Case " << caseNum++ << ": ";
		if(visited[U] == -1)
			cout << "Permanently Locked" << endl;
		else
			cout << visited[U] << endl;
	}
	return 0;
}