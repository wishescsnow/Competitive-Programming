#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
using namespace std;

const double INF = 10000000000000.0;
typedef pair<int, int> ii;
vector<ii> pointList;
double towns[110][110];

double euDistance(int x1, int x2, int y1, int y2)
{
	return sqrt(pow(((double)x1-(double)x2), 2) + pow(((double)y1-(double)y2), 2));
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N, n, x, y;
	cin >> N;
	for(int t=0;t<N;t++)
	{
		pointList.clear();
		cin >> n;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
			{
				if(i==j)
					towns[i][j] = 0;
				else
					towns[i][j] = INF;
			}

		for(int i=0;i<n;i++)
		{
			cin >> x >> y;
			pointList.push_back(ii(x, y));
		}
		for(int i=0;i<pointList.size()-1;i++)
		{
			for(int j=i+1;j<pointList.size();j++)
			{
				double distance = euDistance(pointList[i].first, pointList[j].first, pointList[i].second, pointList[j].second);
				if(distance <= 10.0)
				{
					towns[i][j] = distance;
					towns[j][i] = distance;
				}
			}
		}

		for(int k=0;k<n;k++)
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					towns[i][j] = min(towns[i][j], towns[i][k] + towns[k][j]);

		double ans = 0.0;
		bool check = false;
		for(int i=0;i<n-1;i++)
		{
			if(check)
				break;
			for(int j=i+1;j<n;j++)
			{
				if(towns[i][j] == INF)
				{
					check = true;
					break;
				}
				else if(towns[i][j] > ans)
				{
					ans = towns[i][j];
				}
			}
		}

		cout << "Case #" << t+1 << ":" << endl;
		if(check)
			cout << "Send Kurdy" << endl;
		else
			cout << setprecision(4) << fixed << ans << endl;
		cout << endl;
	}
	return 0;
}