/*input
3 0
a
b
c
5 4
a
b
c
d
e
b a
c a
b c
c b
4 4
a
b
c
d
a b
b c
c a
d b
2 2
a
b
a b
b a
9 10
a
b
c
d
e
f
g
h
i
b a
c b
d c
e d
c e
f e
g f
e g
a h
i c
5 5
a b c d e
a c
b d
e a
c d
b c
10 3
a b c d e f g h i j
a j
a f
j f
3 1
a b c
c b
5 3
a b c d e
a b
a c
a d
4 2
a
b
c
d
a c
b d
3 3
a
b
c
a b
c b
a c
8 7
a b c d e f g h
a b
a c
a d
a e
a f
a h
a g
9 0
a b c d e f g h i
1 0
a
4 6
a b c d
a b
a c
a d
a b
a c
c d
7 3
a
b
c
d
e
f
g
c e
e f
d e
2 1
a
f
a f
10 9
a b c d e f g h i j
b a
c a
d a
e a
f a
g a
h a
i a
j a
0 0
*/
#include <iostream>
#include <string.h>
#include <vector>
#include <map>

using namespace std;
typedef vector<int> vi;
map<string, int> creatures;

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
	int C, R, num, ans;
	string temp1, temp2;
	while((cin >> C >> R) && !(C == 0 && R == 0))
	{
		creatures.clear();
		num = 0;
		ans = 1;
		UnionFind uf(C);
		for(int i=0;i<C;i++)
		{
			cin >> temp1;
			if(creatures.find(temp1) == creatures.end())
				creatures[temp1] = num++;
		}

		for(int i=0;i<R;i++)
		{
			cin >> temp1 >> temp2;
			uf.unionSet(creatures[temp1], creatures[temp2]);
			ans = max(ans, uf.sizeOfSet(creatures[temp1]));
		}

		cout << ans << endl;
	}
	return 0;
}