/*input
3 3
Picadilly
Victoria
Queensway
Picadilly Victoria 2
Queensway Victoria 10
Queensway Picadilly 20
Picadilly
4 2
Picadilly
Victoria
Queensway
Temple
Picadilly Victoria 2
Temple Queensway 100
Temple
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
map<string, int> mapper;

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
	int s, c, count, cost, ans;
	string name1, name2;
	while((cin >> s >> c) && !(s == 0 && c == 0))
	{
		UnionFind uf(s);
		count = 0;
		mapper.clear();
		EdgeList.clear();
		while(s--)
		{
			cin >> name1;
			mapper[name1] = count++;
		}

		while(c--)
		{
			cin >> name1 >> name2 >> cost;
			EdgeList.push_back(make_pair(cost, make_pair(mapper[name1], mapper[name2])));
		}

		cin >> name2;

		sort(EdgeList.begin(), EdgeList.end());

		ans = 0;
		for(int i=0;i<(int)EdgeList.size();i++)
		{
			pair<int, ii> front = EdgeList[i];
			if(!uf.isSameSet(front.second.first, front.second.second))
			{
				ans += front.first;
				uf.unionSet(front.second.first, front.second.second);
			}
		}

		if(uf.numDisjointSets() == 1)
			cout << ans << endl;
		else
			cout << "Impossible" << endl;
	}
	return 0;
}