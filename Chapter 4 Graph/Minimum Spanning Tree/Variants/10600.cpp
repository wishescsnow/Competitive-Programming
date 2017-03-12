/*input
2
5 8
1 3 75
3 4 51
2 4 19
3 2 95
2 5 42
5 4 31
1 2 9
3 5 66
9 14
1 2 4
1 8 8
2 8 11
3 2 8
8 9 7
8 7 1
7 9 6
9 3 2
3 4 7
3 6 4
7 6 2
4 6 14
4 5 9
5 6 10
*/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
vector<pair<int, ii> > EdgeList;
vector<int> EdgeIdx;

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
	int T, N, M, A, B, C, f, s;
	cin >> T;
	while(T--)
	{
		EdgeIdx.clear();
		EdgeList.clear();
		f = 0; s = -1;
		cin >> N >> M;

		while(M--)
		{
			cin >> A >> B >> C;
			EdgeList.push_back(make_pair(C, make_pair(A-1, B-1)));
		}

		sort(EdgeList.begin(), EdgeList.end());

		UnionFind uf(N);
		for(int j=0;j<(int)EdgeList.size();j++)
		{
			pair<int, ii> front = EdgeList[j];
			if(!uf.isSameSet(front.second.first, front.second.second))
			{
				EdgeIdx.push_back(j);
				f += front.first;
				uf.unionSet(front.second.first, front.second.second);
			}
		}

		for(int i=0;i<(int)EdgeIdx.size();i++)
		{
			UnionFind uf2nd(N);
			int temp = 0;
			for(int j=0;j<(int)EdgeList.size();j++)
			{
				if(j == EdgeIdx[i])
					continue;

				pair<int, ii> front = EdgeList[j];
				if(!uf2nd.isSameSet(front.second.first, front.second.second))
				{
					temp += front.first;
					uf2nd.unionSet(front.second.first, front.second.second);
				}
			}

			if(uf2nd.numDisjointSets() == 1)
			{
				if(s == -1)
					s = temp;
				else
				{
					if(temp < s)
						s = temp;
				}
			}
		}

		cout << f << " " << s << endl;
	}
	return 0;
}