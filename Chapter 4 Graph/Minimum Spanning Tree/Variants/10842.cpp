/*input
6
2 3
0 1 10
0 1 20
0 0 30
4 5
0 1 1
3 1 2
1 2 3
2 3 4
0 2 5
1 3
0 0 900
0 0 800
0 0 950
3 2
1 0 100
2 0 115
7 9
0 1 50
0 2 60
1 3 120
1 4 90
2 5 50
3 5 80
3 6 70
4 6 40
5 6 140
4 8
0 1 50
0 2 60
1 1 20
1 2 59
1 2 65
1 3 60
2 3 62
3 0 45
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
	int N, n, m, u, v, c, ans;
	cin >> N;
	for(int a=1;a<=N;a++)
	{
		EdgeList.clear();
		ans = -1;
		cin >> n >> m;
		UnionFind uf(n);
		while(m--)
		{
			cin >> u >> v >> c;
			EdgeList.push_back(make_pair(c, make_pair(u, v)));
		}

		sort(EdgeList.begin(), EdgeList.end());

		for(int i=(int)EdgeList.size()-1;i>=0;i--)
		{
			pair<int, ii> front = EdgeList[i];
			if(!uf.isSameSet(front.second.first, front.second.second))
			{
				uf.unionSet(front.second.first, front.second.second);
				if(ans == -1)
					ans = front.first;
				else
				{
					if(front.first < ans)
						ans = front.first;
				}
			}
		}

		cout << "Case #" << a << ": " << ans << endl;
	}
	return 0;
}