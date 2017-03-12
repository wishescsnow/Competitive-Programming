#include <iostream>
#define INF 1000000000

using namespace std;
int adjMat[25][25];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, J, I = 0, N, A, B, T = 1;
	while(cin >> n)
	{
		I++;
		if(I == 1)
		{
			for(int i=1;i<=20;i++)
				for(int j=1;j<=20;j++)
				{
					if(i == j)
						adjMat[i][j] = 0;
					else
						adjMat[i][j] = INF;
				}
		}
		while(n--)
		{
			cin >> J;
			adjMat[I][J] = 1;
			adjMat[J][I] = 1;
		}
		if(I == 19)
		{
			for(int k=1;k<=20;k++)
				for(int i=1;i<=20;i++)
					for(int j=1;j<=20;j++)
						adjMat[i][j] = min(adjMat[i][j], adjMat[i][k] + adjMat[k][j]);
			cin >> N;
			for(int c=0;c<N;c++)
			{
				if(c == 0)
					cout << "Test Set #" << T++ << endl;
				cin >> A >> B;
				if(A < 10)
					cout << " " << A;
				else
					cout << A;
				cout << " to ";
				if(B < 10)
					cout << " " << B;
				else
					cout << B;
				cout << ": " << adjMat[A][B] << endl;
			}
			cout << endl;
			I = 0;
		}
	}
	return 0;
}