#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int

using namespace std;

const int MAXN = 46;

int n;
lli memo[MAXN][4][4];

lli DP(int id,int prev,int prev2){
	if(id==n) return prev!=2;
	if(memo[id][prev][prev2]!=-1) return memo[id][prev][prev2];
	if(prev==2) return memo[id][prev][prev2] = DP(id + 1, (prev2 == 1 ? 3 : 1), prev);
	lli r = 0ll;
	for(int i=1;i<=3;i++){
		if(prev!=i && i==2 && prev!=2 && prev!=0) r += DP(id + 1, i, prev);
		else if(prev!=i && i!=2) r += DP(id + 1, i, prev);
	}
	
	return memo[id][prev][prev2] = r;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(int i=0;i<n;i++)
		for(int j=0;j<=3;j++)
			for(int h=0;h<=3;h++)
				memo[i][j][h] = -1;

	cout<<DP(0,0,0)<<endl;
	return 0;
}