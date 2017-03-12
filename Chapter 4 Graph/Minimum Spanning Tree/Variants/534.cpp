/*input
2
0 0
3 4
3
17 4
19 4
18 5
0
*/
#include <iostream>
#include <iomanip>
#include <math.h>
#include <algorithm>
#include <vector>

using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
vector<pair<double, ii> > EdgeList;
vector<ii> PointList;
vector<vector<pair<int, double> > > MST;
bool found;

class UnionFind{
private: vi p, rank, size; int numSet;
public:
	UnionFind(int N){
		numSet = N;
		size.assign(N, 1);
		rank.assign(N, 0);
		p.assign(N, 0);
		for(int i=0;i<N;i++)
			p[i] = i;
	}

	int findSet(int i) {
		return (p[i] == i) ? i : (p[i] = findSet(p[i]));
	}

	bool isSameSet(int i, int j){
		return (findSet(i) == findSet(j));
	}

	void unionSet(int i, int j){
		if(!isSameSet(i, j)){
			numSet--;
			int x = findSet(i), y = findSet(j);
			if(rank[x] > rank[y])
			{
				size[x] += size[y];
				p[y] = x;
			}
			else{
				size[y] += size[x];
				p[x] = y;
				if(rank[x] == rank[y])
					rank[y]++;
			}
		}
	}

	int numDisjointSets(){
		return numSet;
	}

	int sizeOfSet(int i){
		return size[findSet(i)];
	}
};

double dfs(int prev, int cur, int dst, double cost)
{
	if(cur == dst)
	{
		found = true;
		return cost;
	}

	double maxCost = -1.0;

	for(int i=0;i<(int)MST[cur].size();i++)
	{
		if(MST[cur][i].first != prev && !found)
			maxCost = dfs(cur, MST[cur][i].first, dst, max(MST[cur][i].second, cost));
	}

	return maxCost;
}

double euDistance(int x1, int x2, int y1, int y2)
{
	return sqrt(pow(((double)x2-(double)x1), 2) + (pow(((double)y2-(double)y1), 2)));
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, x, y, caseNum = 1;
	while(cin >> n && n != 0)
	{
		MST.clear();
		MST.resize(n);
		EdgeList.clear();
		PointList.clear();
		UnionFind uf(n);
		found = false;
		while(n--)
		{
			cin >> x >> y;
			PointList.push_back(ii(x, y));
		}

		for(int i=0;i<(int)PointList.size()-1;i++)
		{
			for(int j=i+1;j<(int)PointList.size();j++)
			{
				double d = euDistance(PointList[i].first, PointList[j].first, PointList[i].second, PointList[j].second);
				EdgeList.push_back(make_pair(d, ii(i, j)));
			}
		}

		sort(EdgeList.begin(), EdgeList.end());

		for(int i=0;i<(int)EdgeList.size();i++)
		{
			pair<double, ii> front = EdgeList[i];
			if(!uf.isSameSet(front.second.first, front.second.second))
			{
				MST[front.second.first].push_back(make_pair(front.second.second, front.first));
				MST[front.second.second].push_back(make_pair(front.second.first, front.first));
				uf.unionSet(front.second.first, front.second.second);
			}
		}

		double ans = dfs(-1, 0, 1, -1.0);

		cout << "Scenario #" << caseNum++ << endl;
		cout << "Frog Distance = " << setprecision(3) << fixed << ans << endl << endl;
	}
	return 0;
}