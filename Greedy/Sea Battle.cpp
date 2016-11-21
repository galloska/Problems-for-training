#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define pii pair<int,int>

using namespace std;

int C(int a,int b, int c){
	if(b<a) return 0;
	return (b-a+1) / c;
}

int M(int ini,int fin, int b){
	return fin - b + 1;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,a,b,k;
	string cad;
	cin>>n>>a>>b>>k;
	cin>>cad;
	
	int ini = 0;
	int cont = 0, sum = 0;
	priority_queue<pii> q;
	for(int i=0;i<n;i++){
		if(cad[i]=='0'){
			cont++;
			if(cont==1) ini = i;
		} else {
			if(cont && i - ini >= b){
				sum += (i - ini) / b;
				q.push( pii( i - ini , ini) );
			}
			cont = 0;
		}
	}
	if(cont && n - ini >= b){
		sum += (n - ini) / b;
		q.push( pii( n - ini , ini) );
	}
	
	vector<int> res;
	while(sum>=a) {
		int ini = q.top().second;
		int len = q.top().first;
		q.pop();
		
		int fin = ini + len - 1;
		int med = M(ini, fin, b);
		sum -= len / b;
		res.push_back( med );
		med--;
		if(med>=ini && med-ini+1>=b){
			sum += (med - ini + 1) / b;
			q.push( pii( med - ini + 1, ini ) );
		}
		
		med+=2;
		if(med<=fin && fin-med+1>=b){
			sum += (fin - med + 1) / b;
			q.push( pii( fin - med + 1, med ) );
		}
	}
	
	cout<<res.size()<<endl;
	for(int i=0;i<res.size();i++)
		cout<<res[i] + 1<<' ';
	if(res.size()) cout<<endl;
	return 0;
}
