#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int

using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	string cad;
	cin>>n>>cad;
	
	int f = 0;
	for(int i=0;i<n;){
		if(!f && i+2 < n && cad[i]=='o' && cad[i+1]=='g' && cad[i+2]=='o'){
			f = 1;
			i += 3;
		} else if(!f) {
			cout<<cad[i];
			i++;
		} else if(f && i+1<n && cad[i]=='g' && cad[i+1]=='o'){
			i += 2;
		} else {
			cout<<"***";
			f = 0;
		}
	}
	if(f) cout<<"***";
	cout<<endl;
	return 0;
}
