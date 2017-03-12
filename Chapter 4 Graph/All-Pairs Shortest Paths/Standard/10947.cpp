/*input
1 1
0 0 1
0 3 1
0
1 1
0 0 1
0 5 1
0
1 1
0 0 1
0 6 1
1
0 3 1
*/
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;
const double INF = 1000000000000.0;
typedef pair<int, int> ii;
vector<pair<int, ii> > pointList;
double adjMat[110][110];

double euDistance(int x1, int x2, int y1, int y2)
{
	return sqrt(pow(((double)x1-(double)x2), 2) + pow(((double)y1-(double)y2), 2));
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int K, M, x, y, r, N;
	while(cin >> K >> M)
	{
		pointList.clear();
		cin >> x >> y >> r;
		pointList.push_back(make_pair(r, ii(x, y)));
		cin >> x >> y >> r;
		pointList.push_back(make_pair(r, ii(x, y)));
		cin >> N;
		for(int n=0;n<N;n++)
		{
			cin >> x >> y >> r;
			pointList.push_back(make_pair(r, ii(x, y)));
		}

		for(int i=0;i<N+2;i++)
		{
			for(int j=0;j<N+2;j++)
			{
				if(i==j)
					adjMat[i][j] = 0.0;
				else
					adjMat[i][j] = INF;
			}
		}

		for(int i=0;i<(int)pointList.size()-1;i++)
		{
			for(int j=i+1;j<(int)pointList.size();j++)
			{
				double dist = euDistance(pointList[i].second.first,
					pointList[j].second.first, pointList[i].second.second, pointList[j].second.second);
				dist -= (double)pointList[i].first;
				dist -= (double)pointList[j].first;
				adjMat[i][j] = dist;
				adjMat[j][i] = dist;
			}
		}

		for(int k=0;k<N+2;k++)
			for(int i=0;i<N+2;i++)
				for(int j=0;j<N+2;j++)
					adjMat[i][j] = min(adjMat[i][j], max(adjMat[i][k], adjMat[k][j]));

		double expected = (double)(K*M);
		if(adjMat[0][1] <= expected)
			cout << "Larry and Ryan will escape!" << endl;
		else
			cout << "Larry and Ryan will be eaten to death." << endl;
	}
	return 0;
}