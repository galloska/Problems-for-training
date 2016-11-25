#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int

using namespace std;

lli EulerPhi(lli n){
	lli res = n;
	for(lli i=2;i*i<=n;i++)
		if(n%i==0){
			while(n%i==0) n /= i;
			res -= res / i;
		}
	if(n>1) res -= res / n;
	return res;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	lli n;
	while(cin>>n && n){
		cout<<EulerPhi(n)<<endl;
	}
	return 0;
}