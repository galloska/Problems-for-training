#include <bits/stdc++.h>
#define endl '\n'
#define pii pair<int,int>

using namespace std;

const int inf = 1e8;
const int MAXN = 101;

int k;
vector<pii> grafo[MAXN];
vector<pii> lista[MAXN];
int memo[MAXN][MAXN];

int DP(int u,int s);

int Sibling(int u,int s,int id) {
	if(id == lista[u].size()) return 0;
	int v = lista[u][id].first;
	if(memo[v][s] != -1) return memo[v][s];
	int c = lista[u][id].second;
	int res = DP(v, k) + Sibling(u, s, id + 1) + 1;
	for(int i=0;i+c<=s;i++)
		res = min(res, DP(v, i) + Sibling(u, s - i - c, id + 1));
	return memo[v][s] = res;
}

int DP(int u,int s) {
	if(!lista[u].size()) return 0;
	return Sibling(u, s, 0);
}

void dfs(int u,int p) {
	for(int i=0;i<grafo[u].size();i++) {
		int v = grafo[u][i].first;
		if(v != p) {
			lista[u].push_back(pii(v, grafo[u][i].second));
			dfs(v, u);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t,n,a,b,c;
	cin>>t;
	
	for(int u=1;u<=t;u++) {
		cin>>n>>k;
		
		for(int i=0;i<n;i++) {
			lista[i].clear();
			grafo[i].clear();
		}
		
		for(int i=0;i<n-1;i++) {
			cin>>a>>b>>c;
			a--,b--;
			grafo[a].push_back(pii(b, c));
			grafo[b].push_back(pii(a, c));
		}
		dfs(0, -1);
		
		for(int i=0;i<n;i++)
			for(int j=0;j<=k;j++)
				memo[i][j] = -1;
		
		cout<<"Case "<<u<<": "<<DP(0, k) + 1<<endl;
	}
	return 0;
}