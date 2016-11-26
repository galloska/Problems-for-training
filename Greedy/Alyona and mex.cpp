#include <bits/stdc++.h>
#define endl '\n'
#define pii pair<int,int>
#define psi pair<int,pii>

using namespace std;

const int MAXN = 100001;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,m;
	int a,b;
	cin>>n>>m;
	int mini = 1e8;
	for(int i=0;i<m;i++){
		cin>>a>>b;
		mini = min( mini , b - a + 1 );
	}
	cout<<mini<<endl;
	
	for(int i=0;i<n;i++)
		cout<<i%mini<<' ';
	cout<<endl;
	return 0;
}