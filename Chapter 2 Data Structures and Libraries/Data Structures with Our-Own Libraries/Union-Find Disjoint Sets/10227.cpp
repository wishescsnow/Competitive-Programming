/*input
2

3 4
1 2
3 3
1 3
2 2
3 2
2 4

3 4
1 2
3 3
1 3
2 2
3 2
2 4
*/
#include <cstdio>
#include <string.h>
#include <vector>

using namespace std;
typedef vector<int> vi;

int adjMat[110][110];

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
	int n, T, P, i, j;
	bool isSame;
	char s[256];
	scanf("%d\n\n", &n);
	while(n--)
	{
		scanf("%d %d\n", &P, &T);
		memset(adjMat, 0, sizeof adjMat);
		UnionFind uf(P);
		while(gets(s))
        {
            if(strlen(s)==0)
                break;
            sscanf(s, "%d %d", &i, &j);
			adjMat[i-1][j-1] = 1;
		}

		for(int i=0;i<P-1;i++)
		{
			for(int j=i+1;j<P;j++)
			{
				isSame = true;
				for(int k=0;k<T;k++)
				{
					if(adjMat[i][k] != adjMat[j][k])
					{
						isSame = false;
						break;
					}
				}

				if(isSame)
				{
					uf.unionSet(i, j);
				}
			}
		}

		printf("%d\n", uf.numDisjointSets());
		if(n)
			printf("\n");
	}
	return 0;
}