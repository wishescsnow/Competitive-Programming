#include <iostream>
#include <algorithm>

using namespace std;

bool stringsort(string s1, string s2)
{
	int c1 = 0, c2 = 0;
	for(int i=0;i<s1.length()-1;i++)
	{
		for(int j=i+1;j<s1.length();j++)
		{
			if(s1.at(i) > s1.at(j))
				c1++;
			if(s2.at(i) > s2.at(j))
				c2++;
		}
	}
	if(c1 < c2)
		return true;
	else
		return false;
}

int main()
{
	int M;
	cin >> M;
	while(M--)
	{
		string strings[105];
		int n, m;
		cin >> n >> m;
		for(int i=0;i<m;i++)
		{
			cin >> strings[i];
		}

		stable_sort(strings, strings + m, stringsort);

		for(int i=0;i<m;i++)
		{
			cout << strings[i] << endl;
		}

		if(M)
			cout << endl;
	}
	return 0;
}
