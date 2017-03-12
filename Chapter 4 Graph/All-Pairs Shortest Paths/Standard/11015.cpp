/*input
4 3
timotius
harry
richard
januar
1 2 10
1 3 8
1 4 6
4 3
rocky
herwin
gaston
jefry
1 2 5
1 3 5
1 4 5
0 0
*/
#include <iostream>
#include <map>
#define INF 1000000000

using namespace std;
int adjMat[30][30];
map<int, string> mapper;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N, M, I, J, K, t = 1, ans, minTemp, idx;
	string temp;
	while(cin >> N >> M && N != 0)
	{
		mapper.clear();
		for(int i=1;i<=N;i++)
			for(int j=1;j<=N;j++)
			{
				if(i == j)
					adjMat[i][j] = 0;
				else
					adjMat[i][j] = INF;
			}

		for(int n=1;n<=N;n++)
		{
			cin >> temp;
			mapper[n] = temp;
		}

		while(M--)
		{
			cin >> I >> J >> K;
			adjMat[I][J] = K;
			adjMat[J][I] = K;
		}

		for(int k=1;k<=N;k++)
			for(int i=1;i<=N;i++)
				for(int j=1;j<=N;j++)
					adjMat[i][j] = min(adjMat[i][j], adjMat[i][k]+adjMat[k][j]);

		ans = -1;
		for(int i=1;i<=N;i++)
		{
			minTemp = 0;
			for(int j=1;j<=N;j++)
			{
				if(i != j)
					minTemp += adjMat[i][j];
			}
			if(ans == -1)
			{
				ans = minTemp;
				idx = i;
			}
			else if(minTemp < ans)
			{
				ans = minTemp;
				idx = i;
			}
		}

		cout << "Case #" << t++ << " : " << mapper[idx] << endl;
	}
	return 0;
}