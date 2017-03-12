/*input
7 9 3
1 2 50
1 3 60
2 4 120
2 5 90
3 6 50
4 6 80
4 7 70
5 7 40
6 7 140
1 7
2 6
6 2
7 6 3
1 2 50
1 3 60
2 4 120
3 6 50
4 6 80
5 7 40
7 5
1 7
2 4
0 0 0
*/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
vector<pair<int, ii> > EdgeList;
vector<vector<ii> > MST;
bool found;

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

int dfs(int prev, int cur, int dst, int cost)
{
	if(cur == dst)
	{
		found = true;
		return cost;
	}

	int maxCost = -1;

	for(int i=0;i<(int)MST[cur].size();i++)
	{
		if(MST[cur][i].first != prev && !found)
			maxCost = dfs(cur, MST[cur][i].first, dst, max(MST[cur][i].second, cost));
	}

	return maxCost;
}

int main()
{
	int C, S, Q, c1, c2, d, caseNum = 0;
	while((cin >> C >> S >> Q) && !(C == 0 && S == 0 && Q == 0))
	{
		if(caseNum)
			cout << endl;

		EdgeList.clear();
		UnionFind uf(C);
		MST.clear();
		MST.assign(C, vector<ii>());
		while(S--)
		{
			cin >> c1 >> c2 >> d;
			EdgeList.push_back(make_pair(d, make_pair(c1-1, c2-1)));
		}

		sort(EdgeList.begin(), EdgeList.end());

		for(int i=0;i<(int)EdgeList.size();i++)
		{
			pair<int, ii> front = EdgeList[i];
			if(!uf.isSameSet(front.second.first, front.second.second))
			{
				uf.unionSet(front.second.first, front.second.second);
				MST[front.second.first].push_back(make_pair(front.second.second, front.first));
				MST[front.second.second].push_back(make_pair(front.second.first, front.first));
			}
		}

		cout << "Case #" << ++caseNum << endl;
		while(Q--)
		{
			cin >> c1 >> c2;
			found = false;
			int ans = dfs(-1, c1-1, c2-1, -1);
			if(ans == -1)
				cout << "no path" << endl;
			else
				cout << ans << endl;
		}
	}
	return 0;
}