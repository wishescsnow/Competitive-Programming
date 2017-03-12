/*input
1
100
w n
r l
b b
q m
h b
d c
r a
o z
k w
y k
i h
d d
s q
d c
r x
m j
w o
r f
s x
y j
l b
b d
f e
a s
c r
y b
e n
d c
g y
x g
p x
l k
r o
l e
n l
p m
p a
f q
k w
o h
k p
c m
q o
n h
n w
u k
w e
s h
m q
b g
u b
c q
j l
i j
s v
m w
k d
t q
x b
x i
v m
r t
b r
j l
t p
s n
f n
z w
f q
m j
f a
d a
r r
s w
f o
b s
n c
v u
h q
f f
s b
q a
w x
q p
a c
e c
c h
z h
f v
k r
l m
o n
j z
p k
p q
r x
x j
i k
z t
x y
*/
#include <iostream>
#include <vector>
#include <map>

using namespace std;
typedef vector<int> vi;

map<string, int> nameList;

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
	int n, F, num;
	string name1, name2;
	cin >> n;
	while(n--)
	{
		nameList.clear();
		num = 0;
		UnionFind uf(100000);
		cin >> F;
		for(int i=0;i<F;i++)
		{
			cin >> name1 >> name2;
			if(nameList.find(name1) == nameList.end())
				nameList[name1] = num++;

			if(nameList.find(name2) == nameList.end())
				nameList[name2] = num++;

			uf.unionSet(nameList[name1], nameList[name2]);
			cout << uf.sizeOfSet(nameList[name1]) << endl;
		}
	}
	return 0;
}