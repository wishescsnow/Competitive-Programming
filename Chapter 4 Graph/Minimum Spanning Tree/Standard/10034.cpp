/*input
1
4
1.0 1.0
1.0 2.0
10.0 10.0
10.0 11.0
*/
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef pair<double, double> dd;
vector<pair<double, ii> > EdgeList;
vector<dd> PointList;

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

double euDistance(double x1, double x2, double y1, double y2)
{
	return sqrt(pow((x2-x1), 2) + (pow((y2-y1), 2)));
}

int main()
{
	int N, n, num = 0;
	double a, b, ans;
	cin >> N;
	while(N--)
	{
		if(num++)
			cout << endl;

		cin >> n;
		UnionFind uf(n);
		PointList.clear();
		EdgeList.clear();
		ans = 0.0;
		for(int i=0;i<n;i++)
		{
			cin >> a >> b;
			PointList.push_back(make_pair(a, b));
		}

		for(int i=0;i<n-1;i++)
		{
			for(int j=i+1;j<n;j++)
			{
				double d = euDistance(PointList[i].first, PointList[j].first, PointList[i].second, PointList[j].second);
				EdgeList.push_back(make_pair(d, make_pair(i, j)));
			}
		}

		sort(EdgeList.begin(), EdgeList.end());

		for(int i=0;i<(int)EdgeList.size();i++)
		{
			pair<double, ii> front = EdgeList[i];
			if(!uf.isSameSet(front.second.first, front.second.second))
			{
				ans += front.first;
				uf.unionSet(front.second.first, front.second.second);
			}
		}

		cout << setprecision(2) << fixed << ans << endl;
	}
	return 0;
}