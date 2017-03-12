/*input
1
60 165
16 21 298
40 5 805
11 59 81
37 40 823
35 19 180
33 28 874
25 43 85
18 39 215
10 37 307
29 42 393
41 4 585
45 34 394
35 13 27
14 58 380
33 52 872
52 55 69
26 5 869
5 37 206
33 9 973
15 60 711
18 55 960
44 57 83
48 46 901
45 29 942
28 49 398
15 42 435
11 52 448
48 18 922
48 1 538
39 45 663
33 58 108
29 43 482
6 4 658
34 8 27
22 18 103
56 59 67
47 32 792
5 30 742
57 24 753
42 50 512
39 31 412
13 21 728
16 46 853
16 6 504
33 2 372
31 10 708
54 40 582
15 13 863
38 24 445
28 31 301
50 7 833
2 8 689
47 36 953
44 54 525
45 45 346
55 57 195
26 49 817
30 27 660
54 1 334
16 23 69
14 35 527
21 8 506
57 54 488
50 47 511
26 47 912
22 11 483
10 5 603
28 45 133
28 40 124
51 12 640
17 3 262
24 35 714
9 60 411
47 11 899
25 5 680
35 27 817
40 44 708
24 26 934
3 29 358
6 18 114
60 21 505
26 30 362
25 8 756
27 25 637
23 32 842
50 55 785
33 40 282
50 27 530
18 33 187
27 6 590
40 22 876
9 45 192
16 24 734
33 12 680
4 38 849
58 28 844
30 45 146
56 41 50
28 53 379
25 59 256
46 10 13
31 21 221
46 50 283
57 43 302
34 2 175
54 36 273
38 7 412
19 2 300
11 46 871
9 40 862
10 60 698
23 51 573
12 50 851
46 5 977
39 44 586
15 18 903
13 50 19
7 50 599
52 38 791
23 44 162
14 15 303
4 32 89
54 2 92
50 26 666
26 39 560
43 17 242
32 48 247
22 56 411
51 15 473
34 43 502
49 4 446
20 34 626
13 26 645
39 21 94
9 1 347
25 19 889
12 44 682
59 21 137
13 12 247
48 38 882
43 27 593
16 30 768
33 28 670
53 11 149
45 43 874
55 33 118
30 13 95
50 24 895
1 41 115
39 55 547
57 43 43
26 11 908
45 50 609
47 42 549
30 11 774
54 33 843
6 26 999
21 15 487
1 2 411
48 45 932
22 16 552
33 20 718
14 40 744
55 23 586
58 51 717
*/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
vector<pair<int, ii> > EdgeList;
vector<int> MST;

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
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int T, v, e, start, end, cost, ans3, temp;
	bool found;
	cin >> T;
	for(int t=1;t<=T;t++)
	{
		cin >> v >> e;
		EdgeList.clear();
		MST.clear();
		UnionFind uf(v);
		found = false;
		ans3 = -1;
		while(e--)
		{
			cin >> start >> end >> cost;
			EdgeList.push_back(make_pair(cost, ii(start-1, end-1)));
		}

		sort(EdgeList.begin(), EdgeList.end());

		for(int i=0;i<(int)EdgeList.size();i++)
		{
			pair<int, ii> front = EdgeList[i];
			if(!uf.isSameSet(front.second.first, front.second.second))
			{
				MST.push_back(i);
				uf.unionSet(front.second.first, front.second.second);
			}
		}

		if(uf.numDisjointSets() != 1)
		{
			cout << "Case #" << t << " : No way" << endl;
			continue;
		}

		for(int i=0;i<(int)MST.size();i++)
		{
			UnionFind uf2(v);
			temp = 0;
			for(int j=0;j<(int)EdgeList.size();j++)
			{
				if(j == MST[i])
					continue;
				pair<int, ii> front = EdgeList[j];
				if(!uf2.isSameSet(front.second.first, front.second.second))
				{
					temp += front.first;
					uf2.unionSet(front.second.first, front.second.second);
				}
			}

			if(uf2.numDisjointSets() == 1)
			{
				if(ans3 == -1)
					ans3 = temp;
				else
					ans3 = min(temp, ans3);
				found = true;
			}
		}

		if(!found)
			cout << "Case #" << t << " : No second way" << endl;
		else
			cout << "Case #" << t << " : " << ans3 << endl;
	}
	return 0;
}