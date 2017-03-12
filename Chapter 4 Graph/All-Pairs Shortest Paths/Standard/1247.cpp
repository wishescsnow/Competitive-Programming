/*input
5 7
A B 1
B C 2
C D 3
D E 2
E A 1
A D 3
A C 4
3
B D
A D
E C
*/
#include <iostream>
#define INF 1000000000

using namespace std;
int adjMat[30][30];
int p[30][30];

void printPath(int i, int j){
	if(i!=j)
		printPath(i, p[i][j]);
	char temp = static_cast<char>(j+'A');
	if(i == j)
		cout << temp;
	else
		cout << " " << temp;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	for(int i=0;i<26;i++)
	{
		for(int j=0;j<26;j++)
		{
			p[i][j] = i;
			if(i == j)
				adjMat[i][j] = 0;
			else
				adjMat[i][j] = INF;
		}
	}
	int s, e, c, e3, e4, q;
	char e1, e2;
	cin >> s >> e;
	while(e--)
	{
		cin >> e1 >> e2 >> c;
		e3 = e1 - 'A';
		e4 = e2 - 'A';
		adjMat[e3][e4] = c;
		adjMat[e4][e3] = c;
	}

	for(int k=0;k<26;k++)
		for(int i=0;i<26;i++)
			for(int j=0;j<26;j++)
			{
				if(adjMat[i][k] + adjMat[k][j] < adjMat[i][j])
				{
					adjMat[i][j] = adjMat[i][k] + adjMat[k][j];
					p[i][j] = p[k][j];
				}
			}

	cin >> q;
	while(q--)
	{
		cin >> e1 >> e2;
		e3 = e1 - 'A';
		e4 = e2 - 'A';
		printPath(e3, e4);
		cout << endl;
	}
	return 0;
}