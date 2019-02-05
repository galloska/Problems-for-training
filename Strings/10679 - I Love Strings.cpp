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
#define pb push_back
#define fi first
#define se second
#define finl '\n'

using namespace std;

const int MAXN = 1000001;

int gcd(int a, int b) { return b ? gcd(b, a%b) : a; }

int sz = 1;
vi fin[MAXN];
int ans[MAXN];
int sup[MAXN];
char enter[MAXN];
int parent[MAXN];
int created[MAXN];
int mat[MAXN][52];

void clear() {
	forn(i, sz) {
		forn(j, 52) mat[i][j] = 0;
		created[i] = 0;
		fin[i].clear();
	}
	sz = 1;
}

int mapea(char a) {
	if(islower(a)) return a - 'a';
	return a - 'A' + 26;
}

void insert(int& id, const string& s) {
	int u = 0;
	forn(i, s.size()) {
		if(!created[ mat[u][ mapea(s[i]) ] ]) {
			mat[u][ mapea(s[i]) ] = sz;
			created[sz++] = 1;
		}
		sup[u] = -2;
		u = mat[u][ mapea(s[i]) ];
		enter[u] = mapea(s[i]);
	}
	fin[u].pb(id);
}

int suf(int u);
int go(int u,int c) {
	if(created[ mat[u][c] ]) return mat[u][c];
	if(!u) return u;
	return go(suf(u), c);
}

int suf(int u) {
	if(!parent[u]) return 0;
	return go(suf(parent[u]), enter[u]);
}

int isPattern(int u) {
	return fin[u].size() > 0;
}

int super(int u) {
	if(sup[u] != -2) return sup[u];
	if(isPattern( suf(u) )) return sup[u] = suf(u);
	if(!suf(u)) return sup[u] = -1;
	return sup[u] = super(suf(u));
}

void buildAhoCorasick() {
	queue<int> q;
	q.push(0);
	parent[0] = 0;
	int cont = 0;

	while(!q.empty()) {
		int u = q.front();
		super(u);
		q.pop();

		forn(c, 52) {
			int v = mat[u][c];
			if(!created[v]) continue;
			parent[v] = u;
			q.push(v);
		}
	}
}

void search(const string& s) {
	int u = 0;
	forn(i, s.size()) {
		u = go(u, mapea(s[i]));
		int v = u;
		while(super(v) != -1) {
			for(auto it: fin[v]) ans[it] = 1;
			v = super(v);
		}
	}
}

// Link to the problem: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1620
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t,q;
	string s,p;
	cin>>t;
	while(t--) {
		cin>>s>>q;
		clear();
		forn(i, q) {
			cin>>p;
			ans[i] = 0;
			insert(i, p);
		}
		buildAhoCorasick();
		search(s);
		forn(i, q)
			if(ans[i]) cout<<"y"<<endl;
			else cout<<"n"<<endl;
	}
	return 0;
}
