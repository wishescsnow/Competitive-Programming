/*input
5 4
4 2 3
4 1 2
3 4 1
1 3 0
0 0
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
vector<pair<int, ii> > EdgeList;
priority_queue<int> HeavyEdge;

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
	int n, m, u, v, w, count;
	while((cin >> n >> m) && !(n == 0 && m == 0))
	{
		EdgeList.clear();
		count = 0;
		UnionFind uf(n);
		while(m--)
		{
			cin >> u >> v >> w;
			EdgeList.push_back(make_pair(w, make_pair(u, v)));
		}

		sort(EdgeList.begin(), EdgeList.end());

		for(int i=0;i<(int)EdgeList.size();i++)
		{
			pair<int, ii> front = EdgeList[i];
			if(!uf.isSameSet(front.second.first, front.second.second))
				uf.unionSet(front.second.first, front.second.second);
			else
				HeavyEdge.push(-front.first);
		}

		if(HeavyEdge.empty())
			cout << "forest";
		else
		{
			while(!HeavyEdge.empty())
			{
				if(count++)
					cout << " ";
				cout << (-HeavyEdge.top());
				HeavyEdge.pop();
			}
		}
		cout << endl;
	}
	return 0;
}