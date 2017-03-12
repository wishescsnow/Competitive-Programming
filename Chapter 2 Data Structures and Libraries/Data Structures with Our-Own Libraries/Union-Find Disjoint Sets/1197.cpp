/*input
100 4
2 1 2
5 10 13 11 12 14
2 0 1
2 99 2
200 2
1 5
5 1 2 3 4 5
1 0
0 0
*/
#include <iostream>
#include <vector>

using namespace std;
typedef vector<int> vi;

class UnionFind{
private: vi p, rank;
public:
	UnionFind(int N){
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
			int x = findSet(i), y = findSet(j);
			if(rank[x] > rank[y])
				p[y] = x;
			else{
				p[x] = y;
				if(rank[x] == rank[y])
					rank[y]++;
			}
		}
	}
};

int main()
{
	int n, m, k, temp, prev, ans;
	while((cin >> n >> m) && !(n == 0 && m == 0))
	{
		ans = 0;
		UnionFind uf(n);
		for(int i=0;i<m;i++)
		{
			cin >> k;
			prev = -1;
			for(int j=0;j<k;j++)
			{
				cin >> temp;
				if(prev != -1)
					uf.unionSet(prev, temp);
				prev = temp;
			}
		}

		for(int i=0;i<n;i++)
		{
			if(uf.findSet(i) == uf.findSet(0))
				ans ++;
		}

		cout << ans << endl;
	}
}