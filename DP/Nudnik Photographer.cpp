#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int

using namespace std;

const int MAXN = 60;

int num[60] = {1, 1, 2, 4, 6};

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin>>n;
	for(int i=5;i<n;i++)
		num[i] = num[i-1] + num[i-2] - num[i-5];
	cout<<num[n-1]<<endl;
	return 0;
}