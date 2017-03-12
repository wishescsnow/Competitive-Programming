/*input
5
1 2 5
1 3 5
1 4 5
1 5 5
1
2 3 2
6
1 2 5
1 3 5
1 4 5
1 5 5
3 4 8
4 5 8
5
1 2 5
1 3 5
1 4 5
1 5 5
1
2 3 2
6
1 2 5
1 3 5
1 4 5
1 5 5
3 4 8
4 5 8
5
1 2 5
1 3 5
1 4 5
1 5 5
1
2 3 2
6
1 2 5
1 3 5
1 4 5
1 5 5
3 4 8
4 5 8
8
6 2 4197
1 3 2268
8 4 8340
2 8 2066
7 1 6433
7 8 2449
6 5 1860
9
8 4 3005
3 5 9972
2 3 3564
1 3 8795
2 3 3763
8 2 8715
8 7 2492
6 3 3511
7 6 4476
7
1 3 2268
6 2 4197
7 1 6433
2 8 2066
7 8 2449
6 5 1860
8 4 8340
7
1 7 3006
7 6 2393
4 6 1813
5 6 1330
3 2 3083
6 2 3000
2
3 1 4610
1 2 5349
9
6 2 3000
5 2 3152
4 6 1813
3 2 3083
1 7 3006
1 6 6937
7 6 2393
5 6 1330
2 1 4294
8
6 2 4197
1 3 2268
8 4 8340
2 8 2066
7 1 6433
7 8 2449
6 5 1860
9
8 4 3005
3 5 9972
2 3 3564
1 3 8795
2 3 3763
8 2 8715
8 7 2492
6 3 3511
7 6 4476
7
1 3 2268
6 2 4197
7 1 6433
2 8 2066
7 8 2449
6 5 1860
8 4 8340
*/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
vector<pair<int, ii> > EdgeList;

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

int main()
{
	int N, a, b, C, K, M, oriC, newC, num = 0;
	while(cin >> N)
	{
		if(num++)
			cout << endl;

		UnionFind uf(N);
		oriC = 0; newC = 0;
		EdgeList.clear();
		for(int i=0;i<N-1;i++)
		{
			cin >> a >> b >> C;
			oriC += C;
		}

		cout << oriC << endl;
		cin >> K;
		for(int i=0;i<K;i++)
		{
			cin >> a >> b >> C;
			a--;b--;
			EdgeList.push_back(make_pair(C, make_pair(a, b)));
		}

		cin >> M;
		for(int i=0;i<M;i++)
		{
			cin >> a >> b >> C;
			a--;b--;
			EdgeList.push_back(make_pair(C, make_pair(a, b)));
		}

		sort(EdgeList.begin(), EdgeList.end());

		for(int i=0;i<(K+M);i++)
		{
			pair<int, ii> front = EdgeList[i];
			if(!uf.isSameSet(front.second.first, front.second.second)){
				newC += front.first;
				uf.unionSet(front.second.first, front.second.second);
			}
		}

		cout << newC << endl;
	}
	return 0;
}