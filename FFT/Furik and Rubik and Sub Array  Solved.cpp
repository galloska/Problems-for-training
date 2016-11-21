#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
 
using namespace std;
 
typedef complex<double> base;
const double PI = acos(-1.0);
 
const int MAXN = 20000001;
 
const double ERROR = 0.5;
 
bool mark[MAXN];
 
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
 
lli num[2000001];
 
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin>>n;
	
	for(int i=1;i<=n;i++)
		cin>>num[i];
	
	if(n<=2000){
		set<lli> s;
		for(int i=1;i<=n;i++){
			lli sum = 0ll;
			for(int j=i;j<=n;j++){
				sum += num[j];
				s.insert( sum );
			}
		}
		cout<<s.size() - 1<<endl;
	}
	else if(n<=20000){
		int res = 0;
		for(int i=1;i<=n;i++){
			int sum = 0;
			for(int j=i;j<=n;j++){
				sum += (int) num[j];
				if(!mark[sum]) res++;
				mark[sum] = 1;
			}
		}
		cout<<res-1<<endl;
	}
	else{
		int sum = 0;
		for(int i=1;i<=n;i++){
			sum += num[i];
			num[i] += num[i-1];
		}
 
		vector<lli> A( sum + 1 , 0 );
		for(int i=0;i<=n;i++)
			A[num[i]] = 1.0;
 
		vector<lli> B( sum + 1 , 0 );
		for(int i=0;i<=n;i++)
			B[-num[i] + sum] = 1.0;
		
		int res = 0;
		A = multiply(A , B);
		for(int i=sum+1;i<A.size();i++)
			if(A[i] > 0)
				res++;
 
		cout<<res - 1<<endl;
	}
	return 0;
} 
