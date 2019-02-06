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
#define eb emplace_back
#define fi first
#define se second
#define endl '\n'

using namespace std;

const int alpha = 63;
const int MAXN = 2500001;

int gcd(int a, int b) { return b ? gcd(b, a%b) : a; }

int sz = 1;
int pos[501];
int sup[MAXN];
int suff[MAXN];
int value[MAXN];
int enter[MAXN];
int parent[MAXN];
int exists[MAXN];
int pattern[MAXN];
int child[MAXN][alpha];

int mapea(char a) {
	if(islower(a)) return a - 'a';
	if(isupper(a)) return a - 'A' + 26;
	if(isdigit(a)) return a - '0' + 52;
	return 62;
}

void insert(int& id, const string& s) {
	int u = 0;
	sup[u] = suff[u] = -2;
	forn(i, s.size()) {
		if(!exists[ child[u][ mapea(s[i]) ] ]) {
			child[u][ mapea(s[i]) ] = sz;
			exists[sz++] = 1;
		}
		u = child[u][ mapea(s[i]) ];
		sup[u] = suff[u] = -2;
		enter[u] = mapea(s[i]);
	}
	pos[id] = u;
	pattern[u] = 1;
}

int suf(int u);
int go(int u,int c) {
	if(exists[ child[u][c] ]) return child[u][c];
	if(!u) return u;
	return go(suf(u), c);
}

int suf(int u) {
	if(suff[u] != -2) return suff[u];
	if(!parent[u]) return suff[u] = 0;
	return suff[u] = go(suf(parent[u]), enter[u]);
}

int isPattern(int u) {
	return pattern[u];
}

int super(int u) {
	if(sup[u] != -2) return sup[u];
	if(isPattern( suf(u) )) return sup[u] = suf(u);
	if(!suf(u)) return sup[u] = -1;
	return sup[u] = super(suf(u));
}

vi order;

void buildAhoCorasick() {
	queue<int> q;
	q.push(0);
	order.eb(0);
	parent[0] = 0;

	while(!q.empty()) {
		int u = q.front();
		q.pop();

		forn(c, alpha) {
			int v = child[u][c];
			if(exists[v]) {
				parent[v] = u;
				order.eb(v);
				q.push(v);
			}
		}
	}
}

void search(const string& s) {
	int u = 0;
	forn(i, s.size()) {
		u = go(u, mapea(s[i]));
		value[u]++;
	}
}

// Link to the problem: https://www.codechef.com/problems/LYRC
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n,m;
	string s,p;
	cin>>n;
	forn(i, n) {
		cin>>p;
		insert(i, p);
	}

	buildAhoCorasick();
	cin>>m;
	forn(i, m) {
		cin>>s;
		search(s);
	}

	for(int i=order.size()-1;i>=0;i--) {
		int u = order[i];
		value[ super(u) ] += value[u];
	}

	forn(i, n)
		cout<<value[ pos[i] ]<<endl;
	return 0;
}
