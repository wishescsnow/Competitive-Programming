#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main()
{
	int N;
	while(cin >> N && N != 0)
	{
		int temp;

		while(cin >> temp && temp != 0)
		{
			vector<int> A;
			vector<int> B;
			stack<int> S;

			B.push_back(temp);
			for(int i=0;i<N;i++)
			{
				if(i==0)
					A.push_back(i+1);
				else
				{
					cin >> temp;
					A.push_back(i+1);
					B.push_back(temp);
				}
			}

			while(true)
			{
				if(!S.empty() && S.top() == B[0])
				{
					S.pop();
					B.erase(B.begin());
					continue;
				}
				else if(!A.empty())
				{
					S.push(A[0]);
					A.erase(A.begin());
					continue;
				}

				if(A.empty())
					break;
			}

			if(S.empty())
				cout << "Yes" << endl;
			else
				cout << "No" << endl;
			A.clear();
			B.clear();
			while(!S.empty())
				S.pop();
		}
		cout << endl;
	}
	return 0;
}
