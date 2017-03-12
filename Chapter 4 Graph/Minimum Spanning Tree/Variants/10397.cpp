/*input
4
103 104
104 100
104 103
100 100
1
4 2
4
103 104
104 100
104 103
100 100
1
4 2
*/
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
vector<pair<double, ii> > EdgeList;
vector<ii> PointList;

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

double euDistance(int x1, int x2, int y1, int y2)
{
	return sqrt(pow(((double)x2-(double)x1), 2) + (pow(((double)y2-(double)y1), 2)));
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N, x, y, M;
	while(cin >> N)
	{
		EdgeList.clear();
		PointList.clear();
		UnionFind uf(N);
		while(N--)
		{
			cin >> x >> y;
			PointList.push_back(ii(x, y));
		}

		cin >> M;

		while(M--)
		{
			cin >> x >> y;
			uf.unionSet(x-1, y-1);
		}

		for(int i=0;i<(int)PointList.size()-1;i++)
		{
			for(int j=0;j<(int)PointList.size();j++)
			{
				if(uf.isSameSet(i, j))
					continue;
				double d = euDistance(PointList[i].first, PointList[j].first, PointList[i].second, PointList[j].second);
				EdgeList.push_back(make_pair(d, ii(i, j)));
			}
		}

		sort(EdgeList.begin(), EdgeList.end());

		double ans = 0.0;
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