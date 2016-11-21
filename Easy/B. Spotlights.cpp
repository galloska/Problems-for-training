#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int

using namespace std;

const int MAXN = 1001;

int c[MAXN][MAXN];
int s[MAXN][MAXN];
int mat[MAXN][MAXN];

int S(int a,int b,int n,int m){
	int one = b-1 >=0 ? s[a][b-1] : 0;
	int two = a-1 >=0 ? c[a-1][b] : 0;
	return (one > 0) + (two > 0) + ( (s[a][m-1] - s[a][b]) > 0 ) + ( (c[n-1][b] - c[a][b]) > 0 );
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,m;
	cin>>n>>m;
	
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			cin>>mat[i][j];
			s[i][j] = mat[i][j];
			c[i][j] = mat[i][j];
		}
	
	for(int i=0;i<n;i++)
		for(int j=1;j<m;j++)
			s[i][j] += s[i][j-1];
	for(int i=0;i<m;i++)
		for(int j=1;j<n;j++)
			c[j][i] += c[j-1][i];

	int r = 0;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			if(!mat[i][j])
				r += S(i, j, n, m);
	cout<<r<<endl;
	return 0;
}
