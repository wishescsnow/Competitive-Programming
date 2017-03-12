/*input
7 10
1 2 30
1 3 15
1 4 10
2 4 25
2 5 60
3 4 40
3 6 20
4 7 35
5 7 20
6 7 30
1 7 99
0 0
*/
#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;
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

	int minCost = -1;

	for(int i=0;i<(int)MST[cur].size();i++)
	{
		if(MST[cur][i].first != prev && !found)
		{
			int temp;
			if(MST[cur][i].second > cost && cost != -1)
				temp = cost;
			else
				temp = MST[cur][i].second;

			minCost = dfs(cur, MST[cur][i].first, dst, temp);
		}
	}

	return minCost;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N, R, C1, C2, P, S, D, T, ans, caseNum = 1;
	while((cin >> N >> R) && !(N == 0 && R == 0))
	{
		MST.clear();
		MST.resize(N);
		EdgeList.clear();
		UnionFind uf(N);
		found = false;
		while(R--)
		{
			cin >> C1 >> C2 >> P;
			EdgeList.push_back(make_pair(P, ii(C1-1, C2-1)));
		}

		cin >> S >> D >> T;
		sort(EdgeList.begin(), EdgeList.end());

		for(int i=(int)EdgeList.size()-1;i>=0;i--)
		{
			pair<int, ii> front = EdgeList[i];
			if(!uf.isSameSet(front.second.first, front.second.second))
			{
				MST[front.second.first].push_back(ii(front.second.second, front.first));
				MST[front.second.second].push_back(ii(front.second.first, front.first));
				uf.unionSet(front.second.first, front.second.second);
			}
		}

		ans = dfs(-1, S-1, D-1, -1);
		ans = ceil((double)T/(double)(ans-1));

		cout << "Scenario #" << caseNum++ << endl;
		cout << "Minimum Number of Trips = " << ans << endl << endl;
	}
	return 0;
}