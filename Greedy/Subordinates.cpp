#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int

using namespace std;

const int MAXN = 200001;

int num[MAXN];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,s;
	cin>>n>>s;
	int r = 0, range = 0;
	vector<int> q;
	for(int i=0;i<n;i++){
		cin>>num[i];
		if(num[i] && i!=s-1) q.push_back(num[i]);
		else if(i!=s-1) q.push_back(1e8);
	}
	sort( q.begin() , q.end() );
	if(num[s-1]!=0) r++;
	
	int ini = 0, fin = q.size() - 1;
	while(ini<=fin){
		// cout<<q[ini]<<" "<<q[fin]<<" "<<range+1<<endl;
		if(q[ini]<=range+1){
			if(q[ini]==range+1) range++;
			ini++;
		} else {
			fin--;
			r++;
			range++;
		}
	}
	
	cout<<r<<endl;
	return 0;
}
