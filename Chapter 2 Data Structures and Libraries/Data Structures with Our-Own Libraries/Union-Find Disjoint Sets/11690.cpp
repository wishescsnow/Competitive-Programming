/*input
3
5 3
100
-75
-25
-42
42
0 1
1 2
3 4
4 2
15
20
-10
-25
0 2
1 3
5 4
1
1
1
1
-4
0 1
2 3
1 2
3 4
*/
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;
typedef vector<int> vi;

int owe[10100];
int group[10100];

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
	int N, n, m, a, b;
	bool ans;
	cin >> N;
	while(N--)
	{
		memset(group, 0, sizeof group);
		cin >> n >> m;
		UnionFind uf(n);
		for(int i=0;i<n;i++)
			cin >> owe[i];

		for(int i=0;i<m;i++)
		{
			cin >> a >> b;
			uf.unionSet(a, b);
		}

		for(int i=0;i<n;i++)
			group[uf.findSet(i)] += owe[i];

		ans = true;
		for(int i=0;i<n;i++)
		{
			if(group[i] != 0)
			{
				ans = false;
			}
		}

		if(ans)
			cout << "POSSIBLE" << endl;
		else
			cout << "IMPOSSIBLE" << endl;
	}
}