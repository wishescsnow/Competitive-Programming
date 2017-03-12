/*input
1
1
1 1
99999 99999
-1
*/
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
vector<pair<double, ii> > EdgeList;
vector<pair<int, int> > PointList;

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
	int w, k, X, Y;
	double ans;
	cin >> w;
	while(w--)
	{
		PointList.clear();
		EdgeList.clear();
		ans = 0.0;
		cin >> k;
		while(cin >> X && X != -1)
		{
			cin >> Y;
			PointList.push_back(make_pair(X, Y));
		}

		for(int i=0;i<(int)PointList.size()-1;i++)
		{
			for(int j=i+1;j<(int)PointList.size();j++)
			{
				double d = euDistance(PointList[i].first, PointList[j].first, PointList[i].second, PointList[j].second);
				EdgeList.push_back(make_pair(d, make_pair(i, j)));
			}
		}

		UnionFind uf((int)PointList.size());
		sort(EdgeList.begin(), EdgeList.end());

		for(int i=0;i<(int)EdgeList.size();i++)
		{
			if(uf.numDisjointSets() == k)
				break;

			pair<double, ii> front = EdgeList[i];
			if(!uf.isSameSet(front.second.first, front.second.second))
			{
				if(front.first > ans)
					ans = front.first;
				uf.unionSet(front.second.first, front.second.second);
			}
		}

		cout << setprecision(0) << fixed << ceil(ans) << endl;
	}
	return 0;
}