#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int

using namespace std;

const int MAXN = 15;

lli dp[MAXN][90];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int s;
	cin>>s;
	dp[9][s] = 1ll;
	for(int id=8;id>=0;id--)
		for(int sum=s;sum>=0;sum--)
			for(int j=0;j<=9;j++)
				if(sum+j<=s)
					dp[id][sum] += dp[id+1][sum+j];
	if(s==1) dp[0][0]++;
	cout<<dp[0][0]<<endl;
	return 0;
}