#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int

using namespace std;

const lli inf = 1LL<<60;
const int MAXN = 1000001;

int pointer;
lli P[MAXN];
lli dp[MAXN];

typedef lli Dato;
const double EPS = 1e-8;

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
	int n;
	lli c;
	cin>>n>>c;
	for(int i=1;i<=n;i++)
		cin>>P[i];
	
	// dp[0] = 0;
	ConvexHullTrick C;
	C.addLine(-2ll * P[1], P[1] * P[1] + dp[0]);
	for(int i=1;i<=n;i++){
		/*
		 * Original DP function
		 *
		dp[i] = inf;
		for(int j=0;j<i;j++)
			dp[i] = min( dp[i] , dp[j] + c + P[i] * P[i] + P[j+1] * P[j+1] - 2ll * P[i] * P[j+1]);
		*/
		
		
		dp[i] = C.query(P[i]) + c + P[i] * P[i];
		if(i<n) C.addLine(-2ll * P[i+1], dp[i] + P[i+1] * P[i+1]);
	}
	
	cout<<dp[n]<<endl;
	return 0;
}