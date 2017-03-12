/*input
3
4 4 100
1 2 10
4 3 12
4 1 41
2 3 23
5 3 1000
1 2 20
4 5 40
3 2 30
5 5 10
1 2 3
2 3 5
3 4 13
3 5 2
5 4 13
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
	int T, N, M, A, X, Y, C, cost;
	cin >> T;
	for(int a = 1;a<=T;a++)
	{
		cin >> N >> M >> A;
		UnionFind uf(N);
		EdgeList.clear();

		while(M--)
		{
			cin >> X >> Y >> C;
			EdgeList.push_back(make_pair(C, make_pair(X-1, Y-1)));
		}

		sort(EdgeList.begin(), EdgeList.end());

		cost = 0;

		for(int i=0;i<(int)EdgeList.size();i++)
		{
			pair<int, ii> front = EdgeList[i];
			if(!uf.isSameSet(front.second.first, front.second.second))
			{
				if(front.first < A)
				{
					cost += front.first;
					uf.unionSet(front.second.first, front.second.second);
				}
			}
		}

		cout << "Case #" << a << ": " << cost + (A*uf.numDisjointSets()) << " " << uf.numDisjointSets() << endl;
	}
	return 0;
}