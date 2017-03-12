/*input
1 2
3 4
3 5
3 1
2 3
4 1
2 6
6 5
-1
1 2
3 4
3 5
3 1
2 3
4 1
2 6
6 5
-1
*/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef vector<int> vi;

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
	int num1, num2, ans = 0;
	UnionFind uf(100000);
	while(cin >> num1)
	{
		if(num1 == -1)
		{
			uf = UnionFind(100000);
			cout << ans << endl;
			ans = 0;
			continue;
		}

		cin >> num2;
		if(!uf.isSameSet(num1, num2))
			uf.unionSet(num1, num2);
		else
			ans++;
	}
	return 0;
}