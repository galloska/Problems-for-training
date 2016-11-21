#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

int num[5];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int s = 0;
	for(int i=0;i<4;i++){
		cin>>num[i];
		s += num[i];
	}
	
	int mini = 1e8;
	for(int i=0;i<4;i++)
		for(int j=i+1;j<4;j++)
			mini = min( mini , abs( (s - num[i] - num[j]) - (num[i] + num[j]) ) );
		
	cout<<mini<<endl;
	return 0;
}
