#include <bits/stdc++.h>

using namespace std;

const int inf = 1<<30;
const int MAXN = 4001;

int dp[MAXN][801];
int mat[MAXN][MAXN];
int costo[MAXN][MAXN];

void Solve(int total, int l,int r,int left, int right) {
	if(l>r) return;
	int id = (l + r) >> 1;
	int bestIndex = left, lim = min(id, right);
	
	dp[id][total] = inf;
	for(int j=left;j<=lim;j++) {
		int c = dp[j - 1][total - 1] + costo[j][id];
		if (c < dp[id][total]) {
			dp[id][total] = c;
			bestIndex = j;
		}
	}
	
	Solve(total, l, id - 1, left, bestIndex);
	Solve(total, id + 1, r, bestIndex, right);
}

int ReadInt() {
	bool minus = false;
	int result = 0;
	char ch;
	ch = getchar();
	while (true) {
		if (ch == '-') break;
		if (ch >= '0' && ch <= '9') break;
		ch = getchar();
	}
	if (ch == '-') minus = true; else result = ch-'0';
	while (true) {
		ch = getchar();
		if (ch < '0' || ch > '9') break;
		result = result*10 + (ch - '0');
	}
	if (minus)
		return -result;
	else
		return result;
}

int main(){
	int n,k;
	char c;
	n = ReadInt();
	k = ReadInt();
	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			mat[i][j] = ReadInt() +  mat[i][j-1];
		
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			costo[i][j] = costo[i][j-1] + mat[j][j] - mat[j][i-1];
		
	for(int i=1;i<=n;i++)
		dp[i][0] = inf;
	
	/*
	** Original DP function
	**
	for(int id=1;id<=n;id++)
		for(int total=1;total<=k;total++)
			for(int j=1;j<=id;j++)
				dp[id][total] = min(dp[id][total], dp[j - 1][total - 1] + costo[j][id]);
	**
	*/
	
	// Applying Divide & Conquer
	for(int i=1;i<=k;i++)
		Solve(i, 1, n, 1, n);
	
	printf("%d\n", dp[n][k]);
	return 0;
}