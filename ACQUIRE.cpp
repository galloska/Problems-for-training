#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define pii pair<lli,lli>
 
using namespace std;
 
const int MAXN = 50001;
const lli INF = numeric_limits<long> :: max();
 
int pointer;
lli dp[MAXN];
pii num[MAXN];
pii plots[MAXN];
 
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
		cin>>num[i].first>>num[i].second;
	sort( num, num + n );
	
	int m = 0;
	for(int i=0;i<n;i++){
		while(m>0 && plots[m-1].second <= num[i].second) m--;
		plots[m++] = num[i];
	}
	
	ConvexHullTrick C;
	C.addLine( plots[0].second , 0ll );
	for(int i=0;i<m;i++){
		lli x = plots[i].first;
		lli r = C.query(x);
		
		/*
		for(int j=0;j<=i;j++){
			lli b_i = 0;
			if(j>0) b_i = dp[j-1];
			lli m_i = plots[j].second;
			r = min( r , m_i * x + b_i  );
		}
		*/
		
		dp[i] = r;
		if(i<n) C.addLine( plots[i+1].second , dp[i] );
	}
	
	cout<<dp[m-1]<<endl;
	return 0;
} 
