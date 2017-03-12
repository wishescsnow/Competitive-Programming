/*input
2
2
5
10
2
1000
5
F 0 17
I 0 5
S 1 10
E 4 9
S 2 10
3
3
1
4
0
2
0
2
I 0 2
S 0 8
*/
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef vector<char> vc;

class SegmentTree{
	private: vi st, lazy; vc A;
	int n;
	int left (int p) { return p << 1; }
	int right (int p) { return (p << 1) + 1; }

	void build(int p, int L, int R){
		if(L == R)
			st[p] = A[L] - '0';
		else
		{
			build(left(p), L, (L+R)/2);
			build(right(p), (L+R)/2+1, R);

			st[p] = st[left(p)] + st[right(p)];
		}
	}

	int inverse(int lazy_value)
	{
		if(lazy_value == 0) return 3;
		if(lazy_value == 1) return 2;
		if(lazy_value == 2) return 1;
		return 0;
	}

	int rsq(int p, int L, int R, int i, int j){
		propagate(p, L, R);

		if(i > R || j < L) return -1;
		if(L>=i && R<= j) return st[p];

		int p1 = rsq(left(p), L, (L+R)/2, i, j);
		int p2 = rsq(right(p), (L+R)/2+1, R, i, j);

		if(p1 == -1) return p2;
		if(p2 == -1) return p1;
		return p1 + p2;
	}

	void range_update(int p, int L, int R, int i, int j, char new_value) {
		propagate(p, L, R);

    	if (i > R || j < L)
      		return;

      	if(L == R)
      	{
      		switch(new_value)
      		{
      			case '0':
      				st[p] = 0;
      				break;
      			case '1':
      				st[p] = 1;
      				break;
      			case '2':
      				st[p] = st[p] == 1? 0 : 1;
      				break;
      		}
      		return;
      	}

      	if(L>=i && R<=j)
      	{
      		switch(new_value)
      		{
      			case '0':
      				st[p] = 0;
      				lazy[left(p)] = lazy[right(p)] = 1;
      				break;
      			case '1':
      				st[p] = R-L+1;
      				lazy[left(p)] = lazy[right(p)] = 2;
      				break;
      			case '2':
      				st[p] = (R-L+1)-st[p];
      				lazy[left(p)] = inverse(lazy[left(p)]);
      				lazy[right(p)] = inverse(lazy[right(p)]);
      				break;
      		}
      		return;
      	}

    	range_update(left(p) , L, (L + R) / 2, i, j, new_value);
    	range_update(right(p), (L + R) / 2 + 1, R, i, j, new_value);

    	st[p] = st[left(p)] + st[right(p)];
    	return;
	}

	void propagate(int p, int L, int R)
	{
		if(lazy[p] == 0) return;
		if(lazy[p] == 1)
			st[p] = 0;
		else if(lazy[p] == 2)
			st[p] = R-L+1;
		else if(lazy[p] == 3)
			st[p] = (R-L+1)-st[p];

		if(L != R)
		{
			if(lazy[p] == 1 || lazy[p] == 2)
				lazy[left(p)] = lazy[right(p)] = lazy[p];
			else
			{
				lazy[left(p)] = inverse(lazy[left(p)]);
      			lazy[right(p)] = inverse(lazy[right(p)]);
			}
		}
		lazy[p] = 0;
      	return;
	}

public:
	SegmentTree(const vc &_A){
		A = _A; n = (int)A.size();
		st.assign(4*n, 0);
		lazy.assign(4*n, 0);
		build(1, 0, n-1);
	}

	int rsq(int i, int j) {return rsq(1, 0, n-1, i, j);}

	void range_update(int i, int j, char new_value) {
    	range_update(1, 0, n - 1, i, j, new_value);
    	return; }
};

int main()
{
	int T, M, t, Q, i, j, ans, qNum, count;
	char s[55], temp[1024100], ope;
	scanf("%d\n", &T);
	for(int n=1;n<=T;n++)
	{
		qNum = 0;
		scanf("%d\n", &M);
		count = 0;
		while(M--)
		{
			scanf("%d\n", &t);
			scanf("%s\n", &s);
			while(t--)
			{
				//Concatenation is slower than for loop style!!!
				for(int k=0;k<strlen(s);k++, count++)
					temp[count] = s[k];
			}
		}

		temp[count] = '\0';
		vc arr(temp, temp+strlen(temp));
		SegmentTree st(arr);

		scanf("%d\n", &Q);
		while(Q--)
		{
			scanf("%c %d %d\n", &ope, &i, &j);
			switch(ope)
			{
				case 'F':
					st.range_update(i, j, '1');
					break;
				case 'E':
					st.range_update(i, j, '0');
					break;
				case 'I':
					st.range_update(i, j, '2');
					break;
				case 'S':
					ans = st.rsq(i, j);
					if(qNum == 0)
						printf("Case %d:\n", n);
					printf("Q%d: %d\n", ++qNum, ans);
					break;
			}
		}
	}
	return 0;
}