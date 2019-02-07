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
#define endl '\n'
#define mapea(a) (a - '0')

using namespace std;

const int alpha = 2;
const int MAXLOG = 19;
const int MAXN = 100001;

int gcd(int a, int b) { return b ? gcd(b, a%b) : a; }

set<int> ans;

struct AhoCorasick {
	int sz;
	int fin[MAXN];
	int sup[MAXN];
	int suff[MAXN];
	int parent[MAXN];
	bool enter[MAXN];
	bool exists[MAXN];
	int trie[MAXN][2];
	vector<string> cad;

	AhoCorasick(): sz(1) {}

	void reset() {
		cad.clear();
		parent[0] = 0;
		sup[0] = suff[0] = -2;
		forn(i, sz) {
			forn(j, alpha) trie[i][j] = 0;
			fin[i] = 0;
			exists[i] = false;
		}
		sz = 1;
	}

	void insert(const string& s) {
		int u = 0;
		forn(i, s.size()) {
			if(!exists[ trie[u][ mapea(s[i]) ] ]) {
				parent[sz] = u;
				exists[sz] = 1;
				trie[u][ mapea(s[i]) ] = sz++;
			}
			u = trie[u][ mapea(s[i]) ];
			suff[u] = sup[u] = -2;
			enter[u] = mapea(s[i]);
		}
		cad.pb(s);
		fin[u] = 1;
	}

	int found(const string& s) {
		int u = 0;
		forn(i, s.size()) {
			if(!exists[ trie[u][ mapea(s[i]) ] ]) return 0;
			u = trie[u][ mapea(s[i]) ];
		}
		return fin[u];
	}

	int isPattern(int u) {
		return fin[u] > 0;
	}
	
	int go(int u, int c) {
		if(exists[ trie[u][c] ]) return trie[u][c];
		if(!u) return 0;
		return go(suf(u), c);
	}

	int suf(int u) {
		if(suff[u] != -2) return suff[u];
		if(!parent[u]) return suff[u] = 0;
		return suff[u] = go(suf(parent[u]), enter[u]);
	}

	int super(int u) {
		if(sup[u] != -2) return sup[u];
		if(isPattern( suf(u) )) return sup[u] = suf(u);
		if(!suf(u)) return sup[u] = -1;
		return sup[u] = super(suf(u));
	}

	int search(const string& s) {
		int u = 0, ans = 0;
		forn(i, s.size()) {
			u = go(u, mapea(s[i]));

			int v = u;
			while(v != -1) {
				ans += fin[v];
				v = super(v);
			}
		}
		return ans;
	}
};

int used[MAXLOG];
AhoCorasick aho[MAXLOG];

void go(int id) {
	forn(i, aho[id].cad.size())
		aho[id + 1].insert(aho[id].cad[i]);
	
	if(!used[id + 1]) used[id + 1] = 1;
	else go(id + 1);

	used[id] = 0;
	aho[id].reset();
}

void recover(int k, string &cad) {
	string aux = cad;
	forn(i, aux.size()) cad[i] = aux[(i + k) % aux.size()];
}

// Link to the problem: https://icpcarchive.ecs.baylor.edu/index.php?option=onlinejudge&page=show_problem&problem=4552
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t,n,caso=1;
	char c;
	string cad;
	cin>>t;
	while(t--) {
		forn(i, MAXLOG) aho[i].reset();
		cin>>n;
		cout<<"Case #"<<caso++<<":"<<endl;
		int off = 0;
		forn(i, n) {
			cin>>c>>cad;
			recover(off, cad);
			if(c == '+') {
				if(aho[18].found(cad)) continue;
				aho[18].insert(cad);
				if(!used[0]) {
					aho[0].insert(cad);
					used[0] = 1;
				}
				else {
					aho[0].insert(cad);
					go(0);
				}
			} else {
				int ans = 0;
				forn(j, MAXLOG)
					if(used[j])
						ans += aho[j].search(cad);
				cout<<ans<<endl;
				off = ans;
			}
		}
	}
	return 0;
}
