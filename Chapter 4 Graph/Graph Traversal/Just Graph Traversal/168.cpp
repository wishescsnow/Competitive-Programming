/*input
A:BCD;B:ACD;C:ABD;D:ABC. A B 5
A:BCD;B:AD;D:BG;F:H;G:DEH;E:FGH;H:EG;C:AD;Z. A C 3
A:BCD;B:AD;D:BG;F:H;G:DEH;E:FGH;H:EG;C:AD;Z:. A C 3
A:BCD;B:AD;D:BG;F:H;G:DEH;E:FGH;H:EG;C:AD. A C 3
A:BCD;B:AD;D:BG;F:H;G:DEH;E:FGH;H:EG;C:ADZ;Z. A C 3
A:BCD;B:AD;D:BG;F:H;G:DEH;E:FGH;H:EG;C:ADZ;Z:. A C 3
A:BCD;B:AD;D:BG;F:H;G:DEH;E:FGH;H:EG;C:ADZ. A C 3
A:BCD;B:ACD;C:ABD;D:ABCG;G:DEFH;E:GFH;F:GEH;H:EFG. A C 1
A:BCD;B:ACD;C:ABD;D:ABCG;G:DEFH;E:GFH;F:GEH;H:EFG. A C 6
A:BCD;B:ACD;C:ABD;D:ABCG;G:DEFH;E:GFH;F:GEH;H:EFG. A C 7
A:B;B:A. B A 3
A:B;B:C;C:A. B A 6
C:A;A:B. A C 999999999
A:BCD;B:AD;D:BG;F:H;G:DEH;E:FGH;H:EG;C:AD. A C 3
A:BCD;B:AD;D:BG;F:H;G:DEH;E:FGH;H:EG;C:AD. A C 1
A:DBC;B. A B 20
A:DBC;B. A B 1
A:BC;B. A B 1
A:BCD;B:AD;D:BG;F:H;G:DEH;E:FGH;H:EG;C:AD. A C 1
A:BCD;B:AD;D:BG;F:H;G:DEH;E:FGH;H:EG;C:AD. A C 1001
A:BCD;B:AD;D:BG;F:H;G:DEH;E:FGH;H:EG;C:AD. A C 1002
A:BCD;B:AD;D:BG;F:H;G:DEH;E:FGH;H:EG;C:AD. A C 1004
A:BCD;B:AD;D:BG;F:H;G:DEH;E:FGH;H:EG;C:AD. A C 1007
B:A;A:B;C. A C 88888
A:BCD;B:AD;C;D:BG;F:H;G:DEH;E:FGH;H:EG;C:AD. A C 3
A:BCD;B:AD;C;D:BG;F:H;G:DEH;E:FGH;H:EG;C:AD. A C 1
A:BC;B:CA;C:AB. A B 9
A:B;B:C;C:D;D:BA. A D 7
A:B;B:C;C:D;D:BA. A D 8
A:B;B:C;C:D;D:BA. A D 9
A:B;B:C;C:D;D:BA. A D 10
A:;B;C:D;D:EGH;Z:;Y. D C 1
A:BCD;B:AD;D:BG;F:H;G:DEH;E:FGH;H:EG;C:AD. A C 1000
A:BC;B:CA;C:AB. A B 99999
A:B;B:C;C:D;D:BA. A D 9999
A:B;B:C;C:D;D:BA. A D 999999
A:B;B:C;C:D;D:BA. A D 99999
A:B;B:C;C:D;D:BA. A D 10000
A:B;Z:E. A C 1
A:BC;C:E;F:A;B:D;D:EF;E:DF. A F 600
A:BC;C:E;F:A;B:D;D:EF;E:DF. A F 599
A:BC;C:E;F:A;B:D;D:EF;E:DF. A F 598
A:BC;C:E;F:A;B:D;D:EF;E:DF. A F 597
A:BC;C:E;F:A;B:D;D:EF;E:DF. A F 1
A:BC;C:E;F:A;B:D;D:EF;E:DF. A F 2
A:BC;C:E;F:A;B:D;D:EF;E:DF. A F 3
A:BC;C:E;F:A;B:D;D:EF;E:DF. A F 4
A:BC;C:E;F:A;B:D;D:EF;E:DF. A F 5
A:BC;C:E;F:A;B:D;D:EF;E:DF. A F 6
A:BC;C:E;F:A;B:D;D:EF;E:DF. A F 7
A:BC;C:E;F:A;B:D;D:EF;E:DF. A F 8
A:BC;C:E;F:A;B:D;D:EF;E:DF. A F 9
A:BC;C:E;F:A;B:D;D:EF;E:DF. A F 10
#
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
#include <map>

using namespace std;

typedef vector<char> vc;
typedef vector<vc> vvc;

int k;
string input;
vvc adjList;
bool lights[26];
map<char, int> mapper, mapper2;

void simulate(int count, char minotaur, char theseus)
{
	char prev = minotaur;

	if(mapper.find(minotaur) != mapper.end())
	for(vc::iterator itvc = adjList[mapper[minotaur]].begin();itvc != adjList[mapper[minotaur]].end();itvc++)
	{
		if((*itvc) != theseus && !lights[mapper2[(*itvc)]])
		{
			minotaur = (*itvc);
			break;
		}
	}

	if(minotaur == prev)
	{
		cout << "/" << minotaur << endl;
		return;
	}

	theseus = prev;
	count--;

	if(count == 0)
	{
		cout << theseus << " ";
		lights[mapper2[theseus]] = true;
		count = k;
	}

	simulate(count, minotaur, theseus);
}

int main()
{
	int index;
	char mapChar = 'A', cavern, temp, theseus, minotaur;
	vc cavernsList;
	bool first;

	for(int i=0;i<26;i++)
	{
		mapper2[mapChar] = i;
		mapChar = static_cast<char>(mapChar + 1);
	}

	while(cin >> input && input.at(0) != '#')
	{
		first = true;
		index = 0;
		memset(lights, false, sizeof lights);

		for(string::iterator it=input.begin(); it != input.end(); it++)
		{
			temp = (*it);

			if(temp == ':')
			{
				first = false;
				continue;
			}
			else if(temp == ';')
			{
				first = true;
				if(!cavernsList.empty())
				{
					adjList.push_back(cavernsList);
					cavernsList.clear();
					mapper[cavern] = index++;
				}
				continue;
			}
			else if(temp == '.')
			{
				if(!cavernsList.empty())
				{
					adjList.push_back(cavernsList);
					cavernsList.clear();
					mapper[cavern] = index++;
				}
				break;
			}

			if(first)
				cavern = temp;
			else if(!first)
				cavernsList.push_back(temp);
		}

		cin >> minotaur >> theseus >> k;

		simulate(k, minotaur, theseus);

		adjList.clear();
		mapper.clear();
	}
	return 0;
}