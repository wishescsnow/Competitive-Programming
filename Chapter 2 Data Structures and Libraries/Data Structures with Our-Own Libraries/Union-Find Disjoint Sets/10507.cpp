/*input
6
11
HAB
AB
AC
AH
BD
BC
BF
CD
CF
CH
DF
FH
*/
#include <iostream>
#include <map>
#include <vector>

using namespace std;
typedef vector<int> vi;

vector<vi> adjList;
map<char, int> ci;
vi updateList;

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
	int num, numR, year, awakeCount, mapNum;
	char temp1, temp2, awake;
	bool update;

	while(cin >> num)
	{
		year = 0;
		mapNum = 0;
		awakeCount = 3;
		ci.clear();
		updateList.clear();
		adjList.clear();
		adjList.assign(num, vi());
		UnionFind uf(num);

		cin >> numR;

		cin >> temp1; cin >> temp2;
		if(ci.find(temp1) == ci.end())
			ci[temp1] = mapNum++;
		if(ci.find(temp2) == ci.end())
			ci[temp2] = mapNum++;

		uf.unionSet(ci[temp1], ci[temp2]);
		cin >> temp2;
		if(ci.find(temp2) == ci.end())
			ci[temp2] = mapNum++;

		uf.unionSet(ci[temp1], ci[temp2]);
		awake = temp1;

		for(int i=0;i<numR;i++)
		{
			cin >> temp1 >> temp2;
			if(ci.find(temp1) == ci.end())
				ci[temp1] = mapNum++;
			if(ci.find(temp2) == ci.end())
				ci[temp2] = mapNum++;
			adjList[ci[temp1]].push_back(ci[temp2]);
			adjList[ci[temp2]].push_back(ci[temp1]);
		}

		update  = true;
		while(update)
		{
			update = false;
			for(int i=0;i<num;i++)
			{
				if(!uf.isSameSet(i, ci[awake]))
				{
					int count = 0;
					for(vi::iterator itvi = adjList[i].begin();itvi != adjList[i].end();itvi++)
					{
						if(uf.isSameSet((*itvi), ci[awake]))
						{
							count ++;
							if(count >= 3)
							{
								updateList.push_back(i);
								if(!update)
								{
									year++;
									update = true;
								}
								break;
							}
						}
					}
				}
			}

			for(vi::iterator itvi = updateList.begin();itvi!=updateList.end();itvi++)
			{
				uf.unionSet((*itvi), ci[awake]);
				awakeCount++;
			}

			updateList.clear();
		}

		if(awakeCount == num)
			cout << "WAKE UP IN, " << year << ", YEARS" << endl;
		else
			cout << "THIS BRAIN NEVER WAKES UP" << endl;
	}
	return 0;
}