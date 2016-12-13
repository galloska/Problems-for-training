#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define pii pair<int,int>

using namespace std;

const int MAXN = 100001;

int dp[MAXN];
pii num[MAXN];

int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>num[i].first>>num[i].second;
	sort(num, num + n);
	
	for(int i=n-1;i>=0;i--){
		int id = lower_bound( num, num + n, pii(num[i].second + 1, -1) ) - num;
		dp[i] = max( dp[i + 1], dp[id] + 1 );
	}
	cout<<dp[0]<<endl;
	return 0;
}