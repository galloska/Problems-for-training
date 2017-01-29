#include <bits/stdc++.h>
#define endl '\n'
#define MOD 1000000007
#define lli long long int

using namespace std;

const int MAXN = 100001;

lli memo[MAXN][2][2][2];
vector<int> lista[MAXN];
vector<int> grafo[MAXN];


void dfs(int u,int p) {
	if(p != -1) lista[p].push_back(u);
	for(int i=0;i<grafo[u].size();i++) {
		int v = grafo[u][i];
		if(v != p) dfs(v, u);
	}
}

lli DP(int u,int color,int ally);

lli Subset(int u,int color, int ally,int id,int taken) {
	if(id == lista[u].size()) return 1ll;
	int v = lista[u][id];
	if(memo[v][color][ally][taken] != -1ll) return memo[v][color][ally][taken];
	lli r = ( DP(lista[u][id], color, 1) * Subset(u, color, ally, id + 1, 1) ) % MOD;
	if(ally || id != lista[u].size() - 1 || taken) r = ( r + ( DP(lista[u][id], 1 - color, 0) * Subset(u, color, ally, id + 1, taken) ) % MOD ) % MOD;
	return memo[v][color][ally][taken] = r;
}

lli DP(int u,int color,int ally) {
	if(!lista[u].size()) return ally;
	return Subset(u, color, ally, 0, 0);
}


int main(){
    ios_base::sync_with_stdio(0);
	cin.tie(0);
    int n,u,v;
    cin >> n;
    for(int a0 = 0; a0 < n-1; a0++){
        cin >> u >> v;
		u--,v--;
        grafo[u].push_back(v);
        grafo[v].push_back(u);
    }
	dfs(0, -1);
	
	for(int i=0;i<n;i++)
		for(int j=0;j<2;j++)
			for(int h=0;h<2;h++)
				for(int k=0;k<2;k++)
					memo[i][j][h][k] = -1ll;
			
	cout<<( DP(0, 0, 0) + DP(0, 1, 0) ) % MOD<<endl;
    return 0;
}