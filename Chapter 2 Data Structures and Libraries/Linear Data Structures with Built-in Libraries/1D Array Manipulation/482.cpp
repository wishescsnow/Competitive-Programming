#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int main()
{
	string buf;
	int n;
	cin >> n;
	getline(cin, buf);
	while(n--)
	{
		vector<int> per;
		vector<string> arr;
		int tempi;
		string tempd;
		string line;
		getline(cin, buf);
		getline(cin, line);
		stringstream buf1(line);
		while(buf1 >> tempi)
		{
			per.push_back(tempi);
		}

		getline(cin, line);
		stringstream buf2(line);
		while(buf2 >> tempd)
		{
			arr.push_back(tempd);
		}

		for(int i=0;i<per.size();i++)
		{
			cout << arr[find(per.begin(), per.end(), i+1) - per.begin()] << endl;
		}
		if(n!=0)
			cout << endl;
	}
	return 0;
}
