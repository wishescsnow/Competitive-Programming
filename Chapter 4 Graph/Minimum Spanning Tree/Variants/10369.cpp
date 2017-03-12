/*input
1
3 6
0 1
0 2
0 4
0 5
0 7
0 8
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
	int N, S, P, x, y;
	double ans;
	cin >> N;
	while(N--)
	{
		EdgeList.clear();
		PointList.clear();
		cin >> S >> P;
		UnionFind uf(P);
		ans = -1.0;
		while(P--)
		{
			cin >> x >> y;
			PointList.push_back(make_pair(x, y));
		}

		for(int i=0;i<(int)PointList.size()-1;i++)
		{
			for(int j=i+1;j<(int)PointList.size();j++)
			{
				double w = euDistance(PointList[i].first, PointList[j].first, PointList[i].second, PointList[j].second);
				EdgeList.push_back(make_pair(w, make_pair(i, j)));
			}
		}

		sort(EdgeList.begin(), EdgeList.end());

		for(int i=0;i<(int)EdgeList.size();i++)
		{
			if(uf.numDisjointSets() == S)
				break;

			pair<double, ii> front = EdgeList[i];
			if(!uf.isSameSet(front.second.first, front.second.second))
			{
				if(front.first > ans)
					ans = front.first;
				uf.unionSet(front.second.first, front.second.second);
			}
		}

		cout << setprecision(2) << fixed << ans << endl;
	}
	return 0;
}