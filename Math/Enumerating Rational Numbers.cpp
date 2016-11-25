#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int

using namespace std;

const int MAXN = 200001;

lli num[MAXN];

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
	num[0] = 1;
	for(int i=1;i<MAXN;i++)
		num[i] = EulerPhi(i) + num[i-1];
	lli n;
	while(cin>>n && n){
		int id = lower_bound( num, num + MAXN, n ) - num;
		if(!id) cout<<"0/1"<<endl;
		else{
			n -= num[id - 1];
			for(int i=1;i<=id;i++){
				if(__gcd(id, i)==1) n--;
				if(!n){
					cout<<i<<"/"<<id<<endl;
					break;
				}
			}
		}
	}
	return 0;
}