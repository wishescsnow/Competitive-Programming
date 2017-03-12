/*input
1
3625 10202 4414 26477
9314 25824 29334 25874 24372 20159 11833 28070 7487 28297 7518 8177 17773 32270 1763 2668 17192 13985 3102 8480 -1 -1
29213 7627 4802 4099 30527 2625 1543 1924 11023 29972 13061 14181 31003 27432 17505 27593 22725 13031 8492 142 -1 -1
17222 31286 13064 7900 19187 8360 22413 30974 14270 29170 235 30833 19711 25760 18896 4667 7285 12550 140 13694 -1 -1
*/
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include <math.h>
#include <map>

using namespace std;
typedef pair<int, int> ii;
typedef pair<double, ii> dii;
const double INF = 1000000000000;
priority_queue<dii, vector<dii>, greater<dii> > pq;
map<ii, vector<ii> > subway;
map<ii, double> state;
vector<ii> walk;

double euDistance(int x1, int x2, int y1, int y2)
{
	return sqrt(pow(((double)x2-(double)x1), 2) + (pow(((double)y2-(double)y1), 2)));
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int T, xh, yh, xs, ys, s1, s2;
	string temp;
	cin >> T;
	while(T--)
	{
		walk.clear();
		subway.clear();
		state.clear();
		cin >> xh >> yh >> xs >> ys;
		state[ii(xs, ys)] = INF;
		walk.push_back(ii(xs, ys));
		getline(cin, temp);
		while(getline(cin, temp))
		{
			if(temp.length() == 0)
				break;

			stringstream strs(temp);
			int prevx, prevy;
			strs >> prevx >> prevy;
			walk.push_back(ii(prevx, prevy));
			state[ii(prevx, prevy)] = INF;
			while((strs >> s1 >> s2) && !(s1 == -1 && s2 == -1))
			{
				walk.push_back(ii(s1, s2));
				state[ii(s1, s2)] = INF;
				subway[ii(prevx, prevy)].push_back(ii(s1, s2));
				subway[ii(s1, s2)].push_back(ii(prevx, prevy));
				prevx = s1; prevy = s2;
			}
		}

		pq.push(dii(0.0, ii(xh, yh)));
		state[ii(xh, yh)] = 0.0;

		while(!pq.empty())
		{
			dii front = pq.top(); pq.pop();
			double time = front.first;
			int x = front.second.first, y = front.second.second;
			if(time > state[ii(x, y)]) continue;
			for(int i=0;i<(int)walk.size();i++)
			{
				ii coor = walk[i];
				int xt = coor.first, yt = coor.second;
				double distance = euDistance(x, xt, y, yt);
				double ttime = distance/10000.0;
				if(state[ii(x, y)] + ttime < state[ii(xt, yt)])
				{
					state[ii(xt, yt)] = state[ii(x, y)] + ttime;
					pq.push(dii(state[ii(xt, yt)], ii(xt, yt)));
				}
			}

			if(subway.find(ii(x, y)) != subway.end())
			{
				for(int i=0;i<(int)subway[ii(x, y)].size();i++)
				{
					ii coor = subway[ii(x, y)][i];
					int xt = coor.first, yt = coor.second;
					double distance = euDistance(x, xt, y, yt);
					double ttime = distance/40000.0;
					if(state[ii(x, y)] + ttime < state[ii(xt, yt)])
					{
						state[ii(xt, yt)] = state[ii(x, y)] + ttime;
						pq.push(dii(state[ii(xt, yt)], ii(xt, yt)));
					}
				}
			}
		}

		cout << round(state[ii(xs, ys)]*60.0) << endl;
		if(T)
			cout << endl;
	}
	return 0;
}