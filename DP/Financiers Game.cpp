#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define pii pair<int,int>

using namespace std;

const int inf = 1e8;
const int MAXN = 4001;

int n;
int num[MAXN];
int memo[MAXN][180][91][2];

int S(int a,int b){
	return num[b] - ( a-1>=0 ? num[a-1] : 0 );
}

// N <= 4000
// id <= N
// dist <= k (Maxima distancia que se pueden separar)
// k <= sqrt(N) -> Facil de probar por sumatoria de 1 a N
// f = Turno en el juego

int DP(int id,int dist, int k, int f){
	int j = (n - id - 1) + (dist - 90);
	if(k>j-id+1) return 0;
	if(memo[id][dist][k][f]!=-1e9) return memo[id][dist][k][f];
	if(!f) {
		int a = DP( id + k, dist + k, k, 1 - f ) + S( id , id + k - 1 );
		if (k+1>j-id+1) return memo[id][dist][k][f] = a;
		int b = DP( id + k + 1, dist + k + 1, k + 1, 1 - f ) + S( id , id + k );
		return memo[id][dist][k][f] = max( a , b );
	} else {
		int a = DP( id, dist - k, k, 1 - f ) - S( j - k + 1 , j );
		if (k+1>j-id+1)  return memo[id][dist][k][f] = a;
		int b = DP( id, dist - k - 1, k + 1, 1 - f ) - S( j - k , j );
		return memo[id][dist][k][f] = min( a , b );
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>num[i];
		if(i) num[i] += num[i-1];
	}
	
	int raiz = sqrt(2*n);
	for(int i=0;i<n;i++)
		for(int j=0;j<=raiz+91;j++)
			for(int k=0;k<=raiz;k++)
				for(int h=0;h<2;h++)
					memo[i][j][k][h] = -1e9;
	
	cout<<DP(0, 90, 1, 0)<<endl;
	return 0;
}
