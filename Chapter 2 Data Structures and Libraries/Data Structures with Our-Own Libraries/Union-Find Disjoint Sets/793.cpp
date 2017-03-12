#include <cstdio>
#include <string.h>
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
	int n, num, i, j, s, u;
	char cs[256], temp;
	scanf("%d\n\n", &n);
	while(n--)
	{
		s = 0;
		u = 0;
		scanf("%d\n", &num);
		UnionFind uf(num);
		while(gets(cs))
		{
			if(strlen(cs) == 0)
				break;

			sscanf(cs, "%c %d %d", &temp, &i, &j);
			switch(temp)
			{
				case 'c':
					uf.unionSet(i-1, j-1);
					break;
				case 'q':
					if(uf.isSameSet(i-1, j-1))
						s++;
					else
						u++;
					break;
			}
		}

		printf("%d,%d\n", s, u);

		if(n)
			printf("\n");
	}
	return 0;
}