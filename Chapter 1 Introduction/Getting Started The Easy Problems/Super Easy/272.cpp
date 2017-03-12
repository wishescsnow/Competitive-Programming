#include <iostream>

using namespace std;

int main()
{
	string temp;
	bool flag = true;
	while(getline(cin, temp))
	{
		for (int i=0; i<temp.length(); ++i)
  		{
    		if(temp.at(i) == '"')
			{
				if(flag)
				{
					cout << "``";
					flag = false;
				}
				else
				{
					cout << "''";
					flag = true;
				}
			}
			else if(temp.at(i) == '&')
			{
				cout << endl;
				i += 5;
			}
			else
				cout << temp.at(i);
  		}
  		cout << endl;
	}
	return 0;
}
