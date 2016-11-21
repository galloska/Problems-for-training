#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int

using namespace std;

bool S(lli n){
	for(lli i=2;i*i<=n;i++)
		if(n%i==0)
			return 0;
	return 1;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin>>n;
	
	while(!S(n)) n--;
	cout<<n<<endl;
	return 0;
}
