#include <cstdio>
#include <cctype>
#include <stack>
#include <vector>
#include <iostream>

using namespace std;

void express()
{
	string temp;
	stack<string> s;
	bool muldiv = false;

	while(getline( cin, temp ) && temp != "ECHO is on.")
	{
		if(isdigit(temp[0]))
		{
			cout << temp;
			if(!s.empty() && muldiv)
			{
				cout << s.top();
				s.pop();
				muldiv = false;
			}
		}
		else
		{
			if(temp == "+" || temp == "-")
			{
				if(!s.empty())
				{
					cout << s.top();
					s.pop();
				}
				s.push(temp);
				muldiv = false;
			}
			if(temp == "*" || temp == "/")
			{
				s.push(temp);
				muldiv = true;
			}
			if(temp == "(")
			{
				express();
				if(!s.empty() && muldiv)
				{
					cout << s.top();
					s.pop();
					muldiv = false;
				}
			}
			if(temp == ")")
			{
				break;
			}
		}
	}

	while(!s.empty())
	{
		cout << s.top();
		s.pop();
	}
}

int main()
{
	int N;
	scanf("%d\nECHO is on.", &N);
	for(int i=0;i<N;i++)
	{
		if(i)
			cout << endl;

		express();
		cout << endl;
	}
	return 0;
}
