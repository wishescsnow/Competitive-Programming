/*input
10
4 4 1
1 6 5
4 2 3
3 1 0
2 5 3
1 2 5
2 9 8
1 8 0
4 9 3
2 3 0
4 7 3
2 4 9
1 4 2
2 6 3
1 6 9
1 2 1
1 7 5
2 1 8
1 3 0
1 7 0
1 2 8
3 5 6
4 2 7
2 0 3
1 6 7
2 4 8
4 4 6
1 9 4
4 2 1
4 3 0
0 0 0
*/
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;
typedef vector<int> vi;

bool enemy[10100][10100];

class UnionFind{
private: vi p, rank, e;
public:
	UnionFind(int N){
		rank.assign(N, 0);
		p.assign(N, 0);
		e.assign(N, -1);
		for(int i=0;i<N;i++)
			p[i] = i;
	}

	int findSet(int i) {
		return (p[i] == i) ? i : (p[i] = findSet(p[i]));
	}

	bool isSameSet(int i, int j){
		return (findSet(i) == findSet(j));
	}

	bool isEnemySet(int i, int j){
		if(e[findSet(i)] == findSet(j) && e[findSet(j)] == findSet(i))
			return true;
		else
			return false;
	}

	bool unionS(int i, int j){
		if(isEnemySet(i, j))
			return false;

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
		return true;
	}

	bool unionSet(int i, int j){
		if(isEnemySet(i, j))
			return false;

		if(!isSameSet(i, j)){
			int x = findSet(i), y = findSet(j), z = -1;

			if(e[x] != -1 && e[y] != -1)
			{
				if(!unionS(e[x], e[y]))
					return false;
				z = findSet(e[x]);
			}
			else
				z = max(e[x], e[y]);

			if(rank[x] > rank[y])
				p[y] = x;
			else{
				p[x] = y;
				if(rank[x] == rank[y])
					rank[y]++;
			}

			if(z != -1)
			{
				e[findSet(x)] = z;
				e[z] = findSet(x);
			}
		}
		return true;
	}

	bool enemySet(int i, int j)
	{
		int x = findSet(i);
		int y = findSet(j);

		if(x == y)
			return false;

		if(e[x] != -1)
		{
			if(!unionS(e[x], y))
				return false;
		}

		if(e[y] != -1)
		{
			if(!unionS(e[y], x))
				return false;
		}
		y = findSet(j);
		x = findSet(i);

		e[x] = y;
		e[y] = x;
		return true;
	}
};

int main()
{
	int n, c, x, y;
	cin >> n;
	UnionFind uf(n);
	memset(enemy, false, sizeof enemy);

	while((cin >> c >> x >> y) && !(c ==0 && x == 0 && y == 0))
	{
		switch(c)
		{
			case 1:
				if(!uf.unionSet(x, y))
					cout << "-1" << endl;
				break;
			case 2:
				if(!uf.enemySet(x, y))
					cout << "-1" << endl;
				break;
			case 3:
				if(uf.isSameSet(x, y))
					cout << "1" << endl;
				else
					cout << "0" << endl;
				break;
			case 4:
				if(uf.isEnemySet(x, y))
					cout << "1" << endl;
				else
					cout << "0" << endl;
				break;
		}
	}
	return 0;
}