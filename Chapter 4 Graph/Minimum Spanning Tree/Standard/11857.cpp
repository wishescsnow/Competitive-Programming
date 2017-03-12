/*input
3 3
0 1 3
1 2 4
2 1 5
2 0
0 0
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
	int n, m, x, y, w, ans;
	while((cin >> n >> m) && !(n == 0 && m == 0))
	{
		UnionFind uf(n);
		EdgeList.clear();
		while(m--)
		{
			cin >> x >> y >> w;
			EdgeList.push_back(make_pair(w, make_pair(x, y)));
		}

		sort(EdgeList.begin(), EdgeList.end());

		ans = -1;
		for(int i=0;i<(int)EdgeList.size();i++)
		{
			pair<int, ii> front = EdgeList[i];
			if(!uf.isSameSet(front.second.first, front.second.second))
			{
				if(ans == -1)
					ans = front.first;
				else
				{
					if(front.first > ans)
						ans = front.first;
				}
				uf.unionSet(front.second.first, front.second.second);
			}
		}

		if(uf.numDisjointSets() == 1)
			cout << ans << endl;
		else
			cout << "IMPOSSIBLE" << endl;
	}
	return 0;
}