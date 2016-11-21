#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int

using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,k;
	cin>>n>>k;
	
	priority_queue<int, vector<int>, greater<int> > q;
	int cont = 0, a;
	int s = 0;
	for(int i=0;i<n;i++){
		cin>>a;
		if(cont==k){
			q.push(a);
			cont = 0;
		}
		else{
			cont++;
			if(!q.size()){
				s += a;
				continue;
			}
			
			int aux = q.top();
			q.pop();
			
			q.push( max( aux , a ) );
			s += min( aux , a );

		}
	}
	
	cout<<s<<endl;
	return 0;
}
