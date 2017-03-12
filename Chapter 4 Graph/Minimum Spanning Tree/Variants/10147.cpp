/*input
2
1
1 1
0
9
1 5
0 0
3 2
4 5
5 1
0 4
5 2
1 2
5 3
3
1 3
9 7
1 2
*/
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;
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
	int t, N, x, y, M;
	cin >> t;
	while(t--)
	{
		cin >> N;
		UnionFind uf(N);
		PointList.clear();
		EdgeList.clear();
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

		if(uf.numDisjointSets() == 1)
		{
			cout << "No new highways need" << endl;
			if(t)
				cout << endl;
			continue;
		}

		for(int i=0;i<(int)PointList.size()-1;i++)
		{
			for(int j=i+1;j<(int)PointList.size();j++)
			{
				if(uf.isSameSet(i, j))
					continue;
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
				cout << (front.second.first+1) << " " << (front.second.second+1) << endl;
				uf.unionSet(front.second.first, front.second.second);
			}
		}

		if(t)
			cout << endl;
	}
	return 0;
}