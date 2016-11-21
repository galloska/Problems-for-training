#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

const int MAXN = 101;

int num[MAXN];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int ini = 0,c,s,n;
	num[ini] = 1;
	cin>>n>>c>>s;
	
	int a;
	while(c--){
		cin>>a;
		if(a==1) ini = (ini + 1) % n;
		else ini = ( ini - 1 + n ) % n;
		num[ini]++;
	}
	
	cout<<num[s-1]<<endl;
	return 0;
}
