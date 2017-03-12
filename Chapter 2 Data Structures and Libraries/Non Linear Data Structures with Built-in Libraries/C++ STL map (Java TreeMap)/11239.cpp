#include <iostream>
#include <cctype>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

bool compareProject(pair<string, int> a, pair<string, int> b)
{
    if(a.second < b.second)
    	return false;
    else if(a.second > b.second)
    	return true;
    else
    	return a.first < b.first;
}

int main()
{
	string temp;
	string currentProject;
	map<string, set<string> > projects;
	map<string, int> students;
	set<string> blacklist;

	while(getline(cin, temp) && temp != "0")
	{
		if(temp == "1")
		{
			vector<pair<string, int> > projectsV;

			for(map<string, set<string> >::iterator i=projects.begin();i!=projects.end();i++)
			{
				int size = i->second.size();
				for(set<string>::iterator j=blacklist.begin();j!=blacklist.end();j++)
				{
					if(i->second.find(*j) != i->second.end())
						size --;
				}
				projectsV.push_back(pair<string, int>(i->first, size));
				//cout << i->first << " " << size << endl;
				i->second.clear();
			}

			sort(projectsV.begin(), projectsV.end(), compareProject);

			for(vector<pair<string, int> >::iterator i=projectsV.begin();i!=projectsV.end();i++)
			{
				cout << i->first << " " << i->second << endl;
			}
			projects.clear();
			students.clear();
			blacklist.clear();
			continue;
		}

		if(isupper(temp[0]))
		{
			currentProject = temp;
			set<string> temp2;
			projects.insert(pair<string, set<string> >(temp, temp2));
			continue;
		}
		else
		{
			if(projects[currentProject].find(temp) == projects[currentProject].end())
			{
				if(students.find(temp) == students.end())
				{
					students[temp] = 1;
					projects[currentProject].insert(temp);
				}
				else
				{
					blacklist.insert(temp);
				}
			}
		}

	}
	return 0;
}
