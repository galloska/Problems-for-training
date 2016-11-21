#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
 
using namespace std;
 
typedef complex<double> base;
 
const double ERROR = 0.5;
const double PI = acos(-1.0);
 
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
 
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t,n;
	cin>>t;
	
	while(t--){
		cin>>n;
		
		n++;
		vector<lli> A(n , 0),B(n , 0 );
		for(int i=0;i<n;i++)
			cin>>A[i];
		
		for(int i=0;i<n;i++)
			cin>>B[i];
	
		A = multiply( A , B );
		
		for(int i=0;i<B.size() + B.size()-1;i++){
			if(i) cout<<" ";
			cout<<A[i];
		}
		cout<<endl;
	}
	return 0;
} 
