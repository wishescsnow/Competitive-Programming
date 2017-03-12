#include <iostream>
#include <iomanip>
#include <map>

using namespace std;

int main()
{
	int N;
	cin >> N;
	string species;
	getline(cin, species);
	getline(cin, species);

	while(N--)
	{
		map<string, int> mapSpe;
		int total = 0;
		while(getline(cin, species) && species != "ECHO is on.")
		{
			total ++;
			if(mapSpe.find(species) == mapSpe.end())
			{
				mapSpe[species] = 1;
			}
			else
			{
				mapSpe[species] ++;
			}
		}

		cout << fixed;
		for(map<string, int>::iterator i = mapSpe.begin(); i != mapSpe.end(); i++)
		{
			cout << i->first << " " << setprecision(4) << double(i->second)/total*100 << endl;
		}

		if(N)
			cout << endl;
	}
	return 0;
}
