#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int

using namespace std;

const int MAXN = 100001;

typedef lli Dato;
const double EPS = 1e-8;

int pointer;
lli A[MAXN];
lli B[MAXN];
lli dp[MAXN];

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
	lli query(Dato x){
		pointer = min( pointer, (int) M.size() -1 );
		
		while(pointer + 1 < M.size() && M[pointer + 1] * x + B[pointer + 1] < M[pointer] * x + B[pointer] ) pointer++;
		
		return M[pointer] * x + B[pointer];
	}
};

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>A[i];
	
	for(int i=0;i<n;i++)
		cin>>B[i];
	
	ConvexHullTrick C;
	C.addLine( B[0], 0ll );
	for(int i=1;i<n;i++){
		dp[i] = C.query( A[i] );
		C.addLine( B[i], dp[i] );
	}
	
	cout<<dp[n-1]<<endl;
	return 0;
}