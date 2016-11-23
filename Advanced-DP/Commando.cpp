#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define pii pair<lli,lli>

using namespace std;

const int MAXN = 1000001;
const lli INF = numeric_limits<long> :: max();
const lli RINF = numeric_limits<long> :: min();

int pointer;
lli dp[MAXN];
lli num[MAXN];

typedef lli Dato;

// Ecuaciones de la forma y = m * x + b
struct ConvexHullTrick{
	vector<Dato> M; //Mantiene las pendientes del envelope
	vector<Dato> B; //Mantiene las intersecciones en y del envelope
	
	// If the ultimate is now made irrelevant between the penultimate
	// and the new line, returns true. Repeat as many times as necessary
	bool isIrrelevant(int l1,int l2,int l3){
		return (B[l3]-B[l1])*(M[l1]-M[l2])<(B[l2]-B[l1])*(M[l1]-M[l3]);
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
		pointer = min( pointer , (int) M.size() - 1 );
		while(pointer + 1 < M.size() && M[pointer + 1] * x + B[pointer+1] > M[pointer] * x + B[pointer]) pointer++;
		return M[pointer] * x + B[pointer];
	}
};

lli S(int x){
	return num[x];
}

lli E(int i,int j,lli a,lli b,lli c){
	return ( S(j) - S(i-1) ) * (S(j) - S(i-1)) * a + (S(j) - S(i-1)) * b + c;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t,n;
	lli a,b,c;
	cin>>t;
	
	while(t--){
		cin>>n;
		cin>>a>>b>>c;
		
		for(int i=1;i<=n;i++){
			cin>>num[i];
			num[i] += num[i-1];
			dp[i] = RINF;
		}

		/* Original DP function
		dp[0] = 0ll;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=i;j++)
				dp[i] = max( dp[i] , dp[j-1] + E(j, i, a, b, c) );
		*/

		pointer = 0;
		ConvexHullTrick C;
		dp[1] = a * S(1) * S(1) + b * S(1) + c;
		C.addLine( -2ll * a * S(1) , dp[1] + a * S(1) * S(1) - b * S(1) );
		// Using Convex Hull Trick
		for(int i=2;i<=n;i++){
			// Split the equation in E(i, j, a, b, c) to have an 
			// equation of the form y = m * x + p
			lli x = S(i);
			dp[i] = a * S(i) * S(i) + b * S(i) + c;
			dp[i] = max( dp[i] , C.query(x) + a * S(i) * S(i) + b * S(i) + c);
			C.addLine( -2ll * a * S(i) , dp[i] + a * S(i) * S(i) - b * S(i) );
		}
		cout<<dp[n]<<endl;
	}
	return 0;
}