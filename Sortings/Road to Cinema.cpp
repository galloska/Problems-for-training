#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int

using namespace std;

const int MAXN = 200001;

int m;
int p[MAXN];
int c[MAXN];
int gap[MAXN];
int sum[MAXN];
int num[MAXN];

bool Solve(int i, int t){
	if(c[i]<gap[m-1]) return false;
	int id = upper_bound( gap , gap + m , c[i] / 2 ) - gap;
	id--;
	int tiempo = (id>=0 ? sum[id] : 0);
	//cout<<tiempo<<endl;
	int extra = sum[m-1] - (id>=0 ? sum[id] : 0);
	//cout<<id<<" -> "<<m<<endl;
	int len = m - id - 1;
	tiempo += extra * 2 - ( len * c[i] - extra );
	//cout<<extra<<" . "<<tiempo<<endl;
	return tiempo <= t;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,k,s,t;
	cin>>n>>k>>s>>t;
	for(int i=0;i<n;i++)
		cin>>p[i]>>c[i];
	
	for(int i=0;i<k;i++)
		cin>>num[i];
	sort( num , num + k );
	for(int i=0;i<k;i++,m++){
		if(!i) gap[m] = num[i];
		else gap[m] = num[i] - num[i-1];
	}
	gap[m] = s - num[m-1];
	m++;
	sort( gap , gap + m );
	sum[0] = gap[0];
	for(int i=1;i<m;i++)
		sum[i] = gap[i] + sum[i-1];
	
	int mini = 1<<30;
	for(int i=0;i<n;i++)
		if(Solve(i, t))
			mini = min( mini , p[i] );
	
	if(mini==1<<30) mini = -1;
	cout<<mini<<endl;
	return 0;
}
