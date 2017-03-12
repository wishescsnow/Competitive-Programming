/*input
2
87 35211
9263 -9865
-6374 680
9947 7021
-6335 5766
5003 5761
-4544 -493
6843 3305
6601 5419
-8436 -4239
1293 -9761
-4585 3826
5463 6981
-1185 -4686
-4044 4089
8641 5832
9689 -8293
6108 -8377
-7636 -2965
-7200 9775
9257 -3971
9258 -8477
4828 -5288
-9870 9821
-4419 1428
5389 -8305
9242 6874
7576 -9197
-162 8425
6234 111
-337 5794
-8778 4874
-9782 3072
-9894 7330
-9175 -7418
2333 -3372
1872 -9919
-1486 1590
5131 -3300
-8152 -1356
4060 -9289
-8694 7237
-8240 3302
1726 -7398
2713 1598
-2608 -2040
-3446 -7625
5448 -1386
-336 -3228
3076 9275
-377 489
4291 -4592
-9282 -8505
1916 -7196
5170 5849
6560 3764
4722 -771
-3749 -8414
-5812 6482
-1920 -8302
3379 -9379
-7003 9193
-2194 9933
426 -7835
-4840 -8810
1680 -6499
2630 4784
10000 -309
2496 3348
-804 1915
-601 -2335
-9386 -524
1063 -5880
-5677 -3134
-1436 8972
9594 6124
5316 -8058
-4405 -3689
-1524 -6879
-1968 6021
-6758 7357
5861 9712
3124 5872
2940 5860
1495 -660
-9275 -7865
5333 -9106
-1265 -8661
5 15174
-913 3058
-819 -9511
-3848 -1320
4991 -5504
1338 1748
*/
#include <iostream>
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
	int T, n, r, x, y, cityNum, caseNum = 1;
	double roads, railroads;
	cin >> T;
	while(T--)
	{
		cin >> n >> r;
		cityNum = 1;
		roads = 0.0;
		railroads = 0.0;
		PointList.clear();
		EdgeList.clear();
		UnionFind uf(n);
		for(int i=0;i<n;i++)
		{
			cin >> x >> y;
			PointList.push_back(make_pair(x, y));
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
				if(front.first > (double)r)
				{
					railroads += front.first;
					cityNum ++;
				}
				else
					roads += front.first;
				uf.unionSet(front.second.first, front.second.second);
			}
		}

		cout << "Case #" << caseNum++ << ": " << cityNum << " " << round(roads) << " " << round(railroads) << endl;
	}
	return 0;
}