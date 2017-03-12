/*input
4 3
Karlsruhe Stuttgart 100
Stuttgart Ulm 80
Ulm Muenchen 120
Karlsruhe Muenchen
5 5
Karlsruhe Stuttgart 100
Stuttgart Ulm 80
Ulm Muenchen 120
Karlsruhe Hamburg 220
Hamburg Muenchen 170
Muenchen Karlsruhe
0 0
*/
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
vector<pair<int, ii> > EdgeList;
vector<vector<ii> > MST;
map<string, int> mapper;
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

	int minCost = 1000000;

	for(int i=0;i<(int)MST[cur].size();i++)
	{
		if(MST[cur][i].first != prev && !found)
			minCost = dfs(cur, MST[cur][i].first, dst, min(MST[cur][i].second, cost));
	}

	return minCost;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, r, i1, i2, w, idx, caseNum = 0;
	string s1, s2;
	while((cin >> n >> r) && !(n == 0 && r == 0))
	{
		EdgeList.clear();
		UnionFind uf(n);
		mapper.clear();
		MST.clear();
		MST.resize(n);
		idx = 0;
		found = false;
		while(r--)
		{
			cin >> s1 >> s2 >> w;
			if(mapper.find(s1) == mapper.end())
				mapper[s1] = i1 = idx++;
			else
				i1 = mapper[s1];

			if(mapper.find(s2) == mapper.end())
				mapper[s2] = i2 = idx++;
			else
				i2 = mapper[s2];

			EdgeList.push_back(make_pair(w, make_pair(i1, i2)));
		}

		sort(EdgeList.begin(), EdgeList.end());

		for(int i=(int)EdgeList.size()-1;i>=0;i--)
		{
			pair<int, ii> front = EdgeList[i];
			if(!uf.isSameSet(front.second.first, front.second.second))
			{
				MST[front.second.first].push_back(make_pair(front.second.second, front.first));
				MST[front.second.second].push_back(make_pair(front.second.first, front.first));
				uf.unionSet(front.second.first, front.second.second);
			}
		}

		cin >> s1 >> s2;
		int ans = 1000000;
		if(!(mapper.find(s1) == mapper.end() || mapper.find(s2) == mapper.end()))
			ans = dfs(-1, mapper[s1], mapper[s2], ans);

		cout << "Scenario #" << ++caseNum << endl;
		cout << ans << " tons" << endl << endl;
	}
	return 0;
}