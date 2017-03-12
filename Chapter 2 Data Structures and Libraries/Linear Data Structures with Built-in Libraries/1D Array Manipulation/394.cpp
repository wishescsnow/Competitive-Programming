#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int constantAtD(int cur, int d, vector<int> &integer, int size)
{
	if(cur == d-1)
		return size;
	else
		return constantAtD(cur+1, d, integer, size)*(integer[(cur+1)*2+1]-integer[(cur+1)*2]+1);
}

int mapAdd(vector<int>& access, int dimen, int base, int size, vector<int> &integer)
{
	int physical = base;
	//cout << "Physical Base : " << physical << endl;
	for(int i=0;i<dimen;i++)
	{
		int constant = constantAtD(i, dimen, integer, size);
		//cout << "Constant : " << constant << endl;
		physical += constant * access[i];
		//cout << "Physical Plus : " << physical << endl;
		physical -= constant * integer[i*2];
		//cout << "Physical Minus : " << physical << endl;
	}
	//cout << endl;
	return physical;
}

int main()
{
	int n, r;
	cin >> n >> r;
	vector<string> name;
	vector<string>::iterator it;

	vector<int> base, size, d;
	vector< vector<int> > integers;
	while(n--)
	{
		string inStr;
		int inbase, insize, ind;
		vector<int> temp;
		cin >> inStr;
		name.push_back(inStr);
		cin >> inbase >> insize >> ind;
		base.push_back(inbase);
		size.push_back(insize);
		d.push_back(ind);

		for(int i=0;i<ind*2;i++)
		{
			int tmp;
			cin >> tmp;
			temp.push_back(tmp);
		}
		integers.push_back(temp);
	}

	while(r--)
	{
		string reference;
		cin >> reference;
		it = find(name.begin(), name.end(), reference);
		int pos = it - name.begin();
		int dimen = d[pos];
		vector<int> access;
		for(int i=0;i<dimen;i++)
		{
			int tmp;
			cin >> tmp;
			access.push_back(tmp);
		}

		int physical = mapAdd(access, dimen, base[pos], size[pos], integers.at(pos));

		cout << name[pos] << "[";
		for(int i=0;i<dimen;i++)
		{
			if(i == dimen-1)
				cout << access[i] << "] = ";
			else
				cout << access[i] << ", ";
		}

		cout << physical << endl;
	}
	return 0;
}
