#include <algorithm>
#include <bitset>
#include <deque>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#define lli long long int
#define pii pair<int,int>
#define ppi pair<pii,pii>
#define forn(i, n) for(int i=0;i<n;i++)
#define vi vector<int>
#define vvi vector<vi>
#define vpi vector<pii>
#define pb push_back
#define fi first
#define se second
#define endl '\n'

using namespace std;

const int MAXN = 1000001;

int gcd(int a, int b) { return b ? gcd(b, a%b) : a; }

vvi scc;
int t = 1;
int ans[MAXN];
int vis[MAXN];
vi lista[MAXN];
int processed[MAXN];

void add(pii a) {
	lista[a.fi].pb(a.se);
}

void dfs(int u) {
	vis[u] = t++;
	for(auto v: lista[u])
		if(!vis[v]) dfs(v);
	vis[u] = t++;
}

void getSCC(int u, vi& cur) {
	cur.pb(u);
	vis[u] = 1;
	for(auto v: lista[u]) {
		if(!vis[v])
			getSCC(v, cur);
	}
}

void Kosaraju(int n, vpi edges) {
	for(auto e: edges) add(e);
	forn(i, n) if(!vis[i]) dfs(i);
	forn(i, n) processed[ vis[i] ] = i + 1;
	

	fill(vis, vis + n, 0);
	forn(i, n) lista[i].clear();
	for(auto e: edges) {
		swap(e.fi, e.se);
		add(e);
	}

	for(int i=t-1;i>=1;i--) {
		int u = processed[i] - 1;
		if(u != -1 && !vis[u]) {
			vi cur;
			getSCC(u, cur);
			scc.pb(cur);
		}
	}
}

// Problem found in: https://www.hackerearth.com/practice/algorithms/graphs/strongly-connected-components/practice-problems/algorithm/a-walk-to-remember-qualifier2/
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n,m,a,b;
	cin>>n>>m;

	vpi edges;
	forn(i, m) {
		cin>>a>>b;
		a--,b--;
		edges.pb(pii(a, b));
	}
	Kosaraju(n, edges);

	for(auto comp: scc)
		if(comp.size() > 1)
			for(auto u: comp)
				ans[u] = 1;
	
	forn(i, n) {
		if(i) cout<<" ";
		cout<<ans[i];
	}
	cout<<endl;
	return 0;
}
