/*input
10 3
-1 -1 1 1 1 1 3 10 10 10
2 3
1 10
5 10
0
*/
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

typedef vector<int> vi;

int fre[200010];
int start[200010];

class SegmentTree{
	private: vi st, A;
	int n;
	int left (int p) { return p << 1; }
	int right (int p) { return (p << 1) + 1; }

	void build(int p, int L, int R){
		if(L == R)
			st[p] = L;
		else
		{
			build(left(p), L, (L+R)/2);
			build(right(p), (L+R)/2+1, R);

			int p1 = st[left(p)], p2 = st[right(p)];
			st[p] = (fre[A[p1]] >= fre[A[p2]]) ? p1 : p2;
		}
	}

	int rmq(int p, int L, int R, int i, int j){
		if(i > R || j < L) return -1;
		if(L>=i && R<= j) return st[p];

		int p1 = rmq(left(p), L, (L+R)/2, i, j);
		int p2 = rmq(right(p), (L+R)/2+1, R, i, j);

		if(p1 == -1) return p2;
		if(p2 == -1) return p1;
		return (fre[A[p1]] >= fre[A[p2]]) ? p1 : p2;
	}

public:
	SegmentTree(const vi &_A){
		A = _A; n = (int)A.size();
		st.assign(4*n, 0);
		build(1, 0, n-1);
	}

	int rmq(int i, int j) {return rmq(1, 0, n-1, i, j);}
};

int main()
{
	int n, q, temp1, temp2, ans;
	int arr[100010];
	while(cin >> n && n != 0)
	{
		memset(fre, 0, sizeof fre);
		memset(start, -1, sizeof start);
		cin >> q;
		for(int i=0;i<n;i++)
		{
			cin >> arr[i];
			arr[i] += 100000;
			fre[arr[i]] ++;
			if(fre[arr[i]] == 1)
				start[arr[i]] = i;
		}

		vi arr2(arr, arr+n);
		SegmentTree st(arr2);

		while(q--)
		{
			cin >> temp1 >> temp2;
			temp1--; temp2--;
			if(arr[temp1] == arr[temp2])
				cout << (temp2-temp1+1) << endl;
			else
			{
				int max1 = start[arr[temp1]]+fre[arr[temp1]]-temp1;
				int max2 = temp2-start[arr[temp2]]+1;
				ans = max(max1, max2);
				int max3 = st.rmq(temp1+max1, temp2-max2);
				ans = max(ans, fre[arr[max3]]);

				cout << ans << endl;
			}
		}
	}

	return 0;
}