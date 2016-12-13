#include <bits/stdc++.h>
#define endl '\n'
#define MOD 1000000007

using namespace std;

const int MAXN = 50001;

int n,a,b;
int dp[2][301][3];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>a>>b;
	for(int id=n;id>=0;id--)
		for(int cont=max(a,b);cont>=0;cont--)
			for(int prev=1;prev>=0;prev--){
				int r = 0;
				if(id==n) r = 1;
				else if(!id) r = (dp[(id + 1) & 1][1][0] + dp[(id + 1) & 1][1][1]) % MOD;
				else{
					if((!prev && cont+1<=a) || (prev && cont+1<=b)) r += dp[(id + 1) & 1][cont + 1][prev];
					r = ( r % MOD + dp[(id + 1) & 1][1][1 - prev] ) % MOD;
				}
				dp[id&1][cont][prev] = r;
			}
	cout<<dp[0][0][0]<<endl;
	return 0;
}