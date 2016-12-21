#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int

using namespace std;

typedef lli Dato;

const lli inf = 1LL<<60;
const double EPS = 1e-8;
const int MAXN = 100001;

lli h[MAXN];
lli calc[MAXN];
lli dp[11][MAXN];

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
	int n,p;
	cin>>n>>p;
	
	for(int i=1;i<=n;i++) {
		cin>>h[i];
		calc[i] = h[i] * i + calc[i - 1];
		h[i] += h[i - 1];
	}

	for(int i=0;i<=p;i++)
		for(int j=0;j<=n;j++)
			dp[i][j] = inf;
	dp[0][0] = 0ll;
	
	for(int i=1;i<=p;i++) {
		ConvexHullTrick C;
		C.addLine(0, 0);
		pointer = 0;
		for(int j=1;j<=n;j++) {
			// dp[i][j] = inf;
			// for(int k=j-1;k>=0;k--)
			//	dp[i][j] = min( dp[i][j], dp[i-1][k] + calc[j] - h[j] - calc[k] + h[k] - h[j] * k + h[k] * k );
			dp[i][j] = C.query( h[j] ) + calc[j] - h[j];
			C.addLine(-j, dp[i - 1][j] - calc[j] + h[j] + h[j] * j);
		}
	}
	
	cout<<dp[p][n]<<endl;
	return 0;
}