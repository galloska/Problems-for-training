#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define pii pair<int,lli>

using namespace std;

const int MAXN = 5001;
const lli INF = 1LL<<60;

lli r;
lli A[MAXN];
lli B[MAXN];
lli dist[MAXN];
lli dp[MAXN][MAXN];
vector<pii> lista[2][MAXN];

void Dijkstra(int s,int n,int f,int b){
	fill(dist, dist + n, INF);
	priority_queue<pii, vector<pii>, greater<pii> > q;
	q.push( pii(0ll, s) );
	dist[s] = 0ll;
	
	while(!q.empty()){
		int u = q.top().second;
		lli d = q.top().first;
		q.pop();

		if(d>dist[u]) continue;
		for(int i=0;i<lista[f][u].size();i++){
			int v = lista[f][u][i].first;
			d = lista[f][u][i].second;
			if(dist[u] + d < dist[v]){
				dist[v] = dist[u] + d;
				q.push( pii( dist[v], v ) );
			}
		}
	}
	
	for(int i=0;i<b && f;i++)
		A[i] = dist[i];
	for(int i=0;i<b && !f;i++)
		B[i] = dist[i] + A[i];
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int u,v;
	lli c;
	int n,b,s,m;
	cin>>n>>b>>s>>m;
	while(m--){
		cin>>u>>v>>c;
		u--,v--;
		lista[1][u].push_back(pii(v, c));
		lista[0][v].push_back(pii(u, c));
	}
	
	Dijkstra(b, n, 1, b);
	Dijkstra(b, n, 0, b);
	B[b] = 0;
	sort(B, B + b + 1);

	for(int i=1;i<=b;i++)
		B[i] += B[i-1];
	
	//for(int i=0;i<=b;i++)
	//	cout<<B[i] - (i-1>=0 ? B[i-1] : 0ll)<<" ";
	//cout<<endl;
	
	for(int i=1;i<=b;i++)
		dp[i][0] = INF;
	
	for(int i=1;i<=b;i++)
		dp[i][1] = B[i] * (lli) (i - 1);
	
	for(int g=2;g<=s;g++)
		for(int id=g+1;id<=b;id++){
			dp[id][g] = INF;
			int ini = id / g;
			for(int j=0;j<=ini && id-j-1>=0;j++)
				dp[id][g] = min( dp[id][g] , dp[id-j-1][g - 1] + (B[id] - B[id - j - 1]) * (lli) j );
		}
	cout<<dp[b][s]<<endl;
	return 0;
}