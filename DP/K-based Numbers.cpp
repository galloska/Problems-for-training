#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int

using namespace std;

const int MAXN = 20;

lli memo[MAXN][MAXN];

lli DP(int id, int last,int& n,int& k){
	if(id==n) return 1;
	if(memo[id][last]!=-1ll) return memo[id][last];
	lli r = 0ll;
	if(last) r += DP(id + 1, 0, n, k);

	for(int i=1;i<=k;i++)
		r += DP(id + 1, i, n, k);
	
	return memo[id][last] = r;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,k;
	cin>>n>>k;
	for(int i=0;i<MAXN;i++)
		fill(memo[i], memo[i] + MAXN, -1ll);
	k--;
	cout<<DP(0, 0, n, k)<<endl;
	return 0;
}