#include <iostream>
#include <queue>

using namespace std;

int main()
{
	int c;
	cin >> c;
	while(c--)
	{
		int l, m, ans = 0;
		cin >> l >> m;
		l *= 100;
		queue<int> left;
		queue<int> right;
		queue<int> ferry;

		while(m--)
		{
			int temp;
			string lr;

			cin >> temp >> lr;
			if(lr == "left")
				left.push(temp);
			else
				right.push(temp);
		}

		bool isLeft = true;
		while(!(left.empty() && right.empty() && ferry.empty()))
		{
			int length = l;

			while(!ferry.empty())
				ferry.pop();

			while(isLeft && !left.empty() && left.front() <= length)
			{
				ferry.push(left.front());
				length -= left.front();
				left.pop();
			}

			while(!isLeft && !right.empty() && right.front() <= length)
			{
				ferry.push(right.front());
				length -= right.front();
				right.pop();
			}

			if(!ferry.empty() || (isLeft && ferry.empty() && !right.empty()) || (!isLeft && ferry.empty() && !left.empty()))
			{
				isLeft = !isLeft;
				ans ++;
			}
		}

		cout << ans << endl;
	}
	return 0;
}
