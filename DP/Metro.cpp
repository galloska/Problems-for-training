#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

const int MAXN = 1003;
double inf = double(1LL<<50);
const double diag = 141.421356;

int mat[MAXN][MAXN];
double dp[MAXN][MAXN];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,m,k,a,b;
	cin>>m>>n>>k;
	m++,n++;
	while(k--){
		cin>>a>>b;
		mat[b - 1][a - 1] = 1;
	}
	
	for(int i=0;i<=m;i++)
		dp[n][i] = inf;
	for(int i=0;i<=n;i++)
		dp[i][m] = inf;
	
	for(int i=n-1;i>=0;i--)
		for(int j=m-1;j>=0;j--){
			if(i==n-1 && j==m-1) continue;
			dp[i][j] = min( dp[i+1][j], dp[i][j+1] ) + 100.0;
			if(mat[i][j]) dp[i][j] = min( dp[i][j], dp[i+1][j+1] + diag );
		}
	
	cout<<(int) (dp[0][0] + 0.5)<<endl;
	return 0;
}