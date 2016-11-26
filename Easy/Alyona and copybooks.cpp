#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int

using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	lli n,a,b,c;
	cin>>n>>a>>b>>c;
	b = min( b , a + a );
	c = min( a + a + a , min( b + a , c ) );
	lli r2 = 1LL<<60;
	for(int i=0;i<100;i++){
		if((n+i)%4!=0) continue;
		int m = i;
		lli r = 0;
		while(m){
			if(m>=3){
				r += c;
				m -= 3;
			} else if(m>=2){
				r += b;
				m -= 2;
			} else {
				r += a;
				m--;
			}
		}
		
		r2 = min( r , r2 );
	}
	cout<<r2<<endl;
	return 0;
}