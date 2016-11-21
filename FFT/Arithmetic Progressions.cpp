#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
 
using namespace std;
 
typedef complex<double> base;
 
const int MAXV = 101;
const int MAXN = 100001;
const double ERROR = 0.5;
const int MAX_GROUP = 2000;
const int MAX_VALUE = 30001;
const double PI = acos(-1.0);
 
int num[MAXN];
vector<lli> A,B;
vector<int> grupos[101];
int cont[3 * MAX_VALUE];
int sum[MAXV][3 * MAX_VALUE];
 
void fft (vector<base> & a, bool invert) {
	lli n = (lli) a.size();
 
	for (int i=1, j=0; i<n; ++i) {
		lli bit = n >> 1;
		for (; j>=bit; bit>>=1)
			j -= bit;
		j += bit;
		if (i < j)
			swap (a[i], a[j]);
	}
 
	for (int len=2; len<=n; len<<=1) {
		double ang = 2*PI/len * (invert ? -1 : 1);
		base wlen (cos(ang), sin(ang));
		for (int i=0; i<n; i+=len) {
			base w (1);
			for (int j=0; j<len/2; ++j) {
				base u = a[i+j],  v = a[i+j+len/2] * w;
				a[i+j] = u + v;
				a[i+j+len/2] = u - v;
				w *= wlen;
			}
		}
	}
	if (invert)
		for (int i=0; i<n; ++i)
			a[i] /= n;
}
 
vector<lli> multiply(const vector<lli> & a, const vector<lli> & b) {
	vector<base> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
	size_t n = 1;
	while (n < max (a.size(), b.size()))  n <<= 1;
	n <<= 1;
	fa.resize (n),  fb.resize (n);
 
	fft (fa, false),  fft (fb, false);
	for (size_t i=0; i<n; ++i)
		fa[i] *= fb[i];
	fft (fa, true);
 
	vector<lli> convolucion(n, 0);
	for (size_t i=0; i<n; ++i)
		convolucion[i] = (lli) (fa[i].real() + ERROR);
	return convolucion;
}
 
void Llena(int i){
	for(int j=0;j<grupos[i].size();j++)
		sum[i][grupos[i][j] + MAX_VALUE - 1]++;
	
	if(i){
		for(int j=0;j<3*MAX_VALUE;j++)
			sum[i][j] += sum[i-1][j];
	}
}
 
lli Caso1(int g){
	for(int i=1;i<3*MAX_VALUE;i++)
		cont[i] = 0ll;
 
	lli r = 0;
	int	n = grupos[g].size();
	for(int j=n-1;j>=0;j--){
		for(int i=j-1;i>=0;i--)
			r += (lli) cont[ 2 * grupos[g][j] - grupos[g][i] + MAX_VALUE - 1 ];
		cont[ grupos[g][j] + MAX_VALUE - 1 ]++;
	}
	
	return r;
}
 
lli S(int a,int b,int c){
	return sum[b][c] - ( a-1>=0 ? sum[a-1][c] : 0ll );
}
 
lli Caso2(int g,int total){
	
	lli r = 0;
	int	n = grupos[g].size();
	if(g+1<total){
		for(int j=n-1;j>=0;j--)
			for(int i=j-1;i>=0;i--)
				r += S(g+1, total - 1, 2 * grupos[g][j] - grupos[g][i] + MAX_VALUE - 1);
	}
	
	if(g-1>=0){
		for(int k=n-1;k>=0;k--)
			for(int j=k-1;j>=0;j--)
				r += S(0, g - 1, 2 * grupos[g][j] - grupos[g][k] + MAX_VALUE - 1);
	}
	
	return r;
}
 
lli Caso3(int g){
	
	lli r = 0;
	int	n = grupos[g].size();
	for(int i=0;i<n;i++)
		B[ grupos[g][i] ]--;
	
	vector<lli> C = multiply(A, B);
	for(int i=0;i<n;i++)
		r += C[2 * grupos[g][i]];
	
	for(int i=0;i<n;i++)
		A[ grupos[g][i] ]++;
	
	return r;
}
 
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	for(int i=0;i<MAX_VALUE;i++){
		A.push_back(0);
		B.push_back(0);
	}
	int n;
	cin>>n;
	
	int id = 0, total = 0;
	for(int i=0;i<n;i++){
		cin>>num[i];
		B[num[i]]++;
		if(!grupos[id].size()) total++;
		grupos[id].push_back( num[i] );
		if(grupos[id].size()==MAX_GROUP) id++;
	}
	
	for(int i=0;i<total;i++)
		Llena(i);
	
	lli res = 0;
	for(int i=0;i<total;i++){
		res += Caso1(i);
		res += Caso2(i, total);
		res += Caso3(i);
	}
	
	cout<<res<<endl;
	return 0;
} 
