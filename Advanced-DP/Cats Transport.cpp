#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int

using namespace std;

typedef lli Dato;

const double EPS = 1e-8;
const lli inf = 1LL<<60;
const int MAXN = 100001;

lli tmp[MAXN]; // Minimum time required to leave the hill 1
lli dist[MAXN];
lli dp[101][MAXN];

int pointer;

// Ecuaciones de la forma y = m * x + b
struct ConvexHullTrick{
	vector<Dato> M; //Mantiene las pendientes del envelope
	vector<Dato> B; //Mantiene las intersecciones en y del envelope
	
	// If the ultimate is now made irrelevant between the penultimate
	// and the new line, returns true. Repeat as many times as necessary
	bool isIrrelevant(int l1,int l2,int l3){
		return 1.0 * (B[l1] - B[l3]) / (M[l3] - M[l1]) < 1.0 * (B[l1] - B[l2]) / (M[l2] - M[l1]) + EPS;
	}

	void addLine(Dato m,Dato b){
		//First, let's add it to the end
		M.push_back(m);
		B.push_back(b);
	
		while (M.size()>=3 && isIrrelevant(M.size()-3, M.size()-2, M.size()-1)){
			M.erase(M.end()-2);
			B.erase(B.end()-2);
		}
	}
	
	// Modify this function. Commonly for a binary search.
	Dato query(Dato x){
		pointer = min( pointer, (int) M.size() -1 );
		
		while(pointer + 1 < M.size() && M[pointer + 1] * x + B[pointer + 1] < M[pointer] * x + B[pointer] ) pointer++;
		
		return M[pointer] * x + B[pointer];
	}
};

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	lli t;
	int n,m,p,h;
	cin>>n>>m>>p;
	
	for(int i=1;i<n;i++) {
		cin>>dist[i];
		dist[i] += dist[i-1];
	}
	
	for(int i=1;i<=m;i++) {
		cin>>h>>t;
		tmp[i] = t - dist[h - 1];
	}
	
	sort(tmp + 1, tmp + m + 1);
	
	for(int i=1;i<=m;i++)
		tmp[i] += tmp[i-1];
	
	for(int i=1;i<=m;i++)
		dp[0][i] = inf;

	for(int i=1;i<=p;i++) {
		ConvexHullTrick C;
		C.addLine(0, 0);
		for(int j=1;j<=m;j++) {
			lli num = tmp[j] - tmp[j - 1];
			dp[i][j] = C.query(num) - tmp[j] + num * j;
			/*
			** Adding Convex Hull Trick
			for(int h=j-1;h>=0;h--)
				dp[i][j] = min( dp[i][j], dp[i-1][h] + num * j - num * h - tmp[j] + tmp[h] );
			*/
			C.addLine(-j, dp[i-1][j] + tmp[j]);
		}
	}
		
	cout<<dp[p][m]<<endl;
	return 0;
}