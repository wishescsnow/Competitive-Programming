#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

int main()
{
	int num;
	vector<int> list, past, curr, currin;
	vector<int>::iterator it;
	stack<int> ans;

	while(scanf("%d\n", &num) == 1)
	{
		list.push_back(num);
		past.push_back(-1);
	}

	currin.push_back(0);
	curr.push_back(list[0]);

	for(int i = 1; i < list.size(); i++)
	{
		if(list[i] > curr.back())
		{
			curr.push_back(list[i]);
			past[i] = currin.back();
			currin.push_back(i);
		}
		else
		{
			it = lower_bound(curr.begin(), curr.end(), list[i]);
			*it = list[i];
			currin[it-curr.begin()] = i;
			past[i] = currin[it-curr.begin()-1];
		}
	}

	printf("%d\n-\n", curr.size());

	int k = currin.back();

	for(int i=0;i<curr.size();i++)
	{
		ans.push(k);
		k = past[k];
	}

	for(int i=0;i<curr.size();i++)
	{
		printf("%d\n", list[ans.top()]);
		ans.pop();
	}
	return 0;
}
