#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int main()
{
	char code[60];
	while(cin >> code)
	{
		if(strcmp(code, "#") == 0)
			break;
		else
		{
			if(next_permutation(code, code + strlen(code)))
				cout << code << endl;
			else
				cout << "No Successor" << endl;
		}
	}
	return 0;
}
