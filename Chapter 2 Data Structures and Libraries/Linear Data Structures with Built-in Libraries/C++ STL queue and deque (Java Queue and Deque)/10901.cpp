#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
	int c, n, t, m;
	cin >> c;
	for(int i=0;i<c;i++)
	{
		if(i)
			cout << endl;
		cin >> n >> t >> m;

		queue<pair<int, int> > left;
		queue<pair<int, int> > right;
		vector<int> output(m);
		queue<pair<int, int> >ferry;

		int temp;
		string lr;

		for(int j=0;j<m;j++)
		{
			cin >> temp >> lr;

			if(lr == "left")
				left.push(pair<int, int>(j, temp));
			else
				right.push(pair<int, int>(j, temp));
		}

		bool l = true;
		int time = min(left.front().second, right.front().second);
		int count = 0;

		while(!(left.empty() && right.empty() && ferry.empty()))
		{
			int limit = n;

			while(!ferry.empty())
			{
				output[ferry.front().first] = time;
				ferry.pop();
			}

			while(l && !left.empty() && left.front().second <= time && limit--)
			{
				ferry.push(left.front());
				left.pop();
			}

			while(!l && !right.empty() && right.front().second <= time && limit--)
			{
				ferry.push(right.front());
				right.pop();
			}

			if(!ferry.empty() || (l && !right.empty() && right.front().second <= time) || (!l && !left.empty() && left.front().second <= time))
			{
				l = !l;
				time += t;
				continue;
			}

			int earliest;
			if(!left.empty())
				earliest = left.front().second;
			if(!right.empty())
				earliest = min(earliest, right.front().second);

			time = max(time, earliest);
		}

		for(int j=0;j<m;j++)
		{
			cout << output[j] << endl;
		}
	}
	return 0;
}
