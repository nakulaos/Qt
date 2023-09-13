#include<vector>
#include<iostream>

using namespace std;

int main()
{
	vector<vector<int>> ve(8,vector<int>(8,3));
	int sum=0;
	for(auto it=ve.begin();it!=ve.end();it++)
	{
		for(auto it1=it->begin();it1!=it->end();it1++)
			sum+=*it1;
	}
	cout<<sum;
}

