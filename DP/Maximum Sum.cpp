#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

const int MAXN = 101;

int mat[MAXN][MAXN];

int Kadane(const vector<int>& num){
	int maxi = num[0], sum = 0, ini = 0;
	for(int i=0;i<num.size();i++){
		maxi = max(maxi, num[i]);
		sum += num[i];
		maxi = max(maxi, sum);
		if(sum<0) sum = 0;
	}
	return maxi;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin>>n;
	
	int maxi = -127;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			cin>>mat[i][j];
		
	for(int i=0;i<n;i++)
		for(int j=1;j<n;j++)
			mat[i][j] += mat[i][j-1];

	for(int i=0;i<n;i++)
		for(int j=i;j<n;j++){
			vector<int> num;
			for(int h=0;h<n;h++)
				num.push_back(mat[h][j] - (i ? mat[h][i-1] : 0));
			maxi = max(maxi, Kadane(num));
		}
	cout<<maxi<<endl;
	return 0;
}