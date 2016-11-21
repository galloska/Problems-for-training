#include <bits/stdc++.h>
#define endl '\n'
 
using namespace std;
 
typedef vector<double> Vector;
 
const double ERROR = 0.5;
const double M_2PI = 2 * M_PI;
 
struct Complejo {
    double real, imag;
    Complejo() : real(), imag() {}
    Complejo(double r, double i) : real(r), imag(i) {}
 
    Complejo operator+(const Complejo& c) {
        return Complejo(real + c.real, imag + c.imag);
    }
    Complejo operator-(const Complejo& c) {
        return Complejo(real - c.real, imag - c.imag);
    }
    Complejo operator*(const Complejo& c) {
        return Complejo(real * c.real - imag * c.imag,
                        real * c.imag + imag * c.real);
    }
};
 
vector<Complejo> FastAndFourier(
    const vector<Complejo>& a, int k = 1) {
 
    int n = a.size();
    if (n == 1) return a;
    vector<Complejo> par, impar;
    for (int i = 0; i < n; ++i)
        if (i & 1) par.push_back(a[i]);
        else impar.push_back(a[i]);
    impar = FastAndFourier(impar, k);
    par = FastAndFourier(par, k);
 
    vector<Complejo> fourier(n);
    Complejo w(1, 0), wn(cos(-k * M_2PI/n),
                         sin(-k * M_2PI/n));
    for (int i = 0; i < n/2; w = w * wn, ++i) {
        fourier[i + n/2] = impar[i] - w * par[i];
        fourier[i] = impar[i] + w * par[i];
    }
    return fourier;
}
 
vector<Complejo> InvFastAndFourier(
    const vector<Complejo>& a) {
 
    vector<Complejo> ifft = FastAndFourier(a, -1);
    for (int i = 0; i < ifft.size(); ++i)
        ifft[i].real /= ifft.size(),
        ifft[i].imag /= ifft.size();
    return ifft;
}
 
Vector ConvolucionDiscreta(
    const Vector& a, const Vector& b) {
 
    int n = a.size() + b.size() - 1;
    int p = 1; while (p < n) p <<= 1;
 
    vector<Complejo> A(p), B(p), C(p);
    for (int i = 0; i < a.size(); ++i)
        A[i] = Complejo(a[i], 0);
    for (int i = 0; i < b.size(); ++i)
        B[i] = Complejo(b[i], 0);
 
    A = FastAndFourier(A);
    B = FastAndFourier(B);
    for (int i = 0; i < p; ++i)
        C[i] = A[i] * B[i];
    C = InvFastAndFourier(C);
 
    Vector convolucion(n);
    for (int i = 0; i < n; ++i)
        convolucion[i] = C[i].real + ERROR;
    return convolucion;
}
 
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t,i;
	string cad;
	cin>>t;
	
	while(t--){
		cin>>cad;
		
		vector<double> A, B;
 
		i = 0;
		while(i<cad.size() && cad[i]=='0') i++;
		for(;i<cad.size();i++)
			A.push_back( cad[i] - 48 );
		
		cin>>cad;
		i = 0;
		while(i<cad.size() && cad[i]=='0') i++;
		for(;i<cad.size();i++)
			B.push_back( cad[i] - 48 );
		
		if(!A.size() || !B.size()){
			cout<<0<<endl;
			continue;
		}
 
		A = ConvolucionDiscreta( A , B );
		
		int aca = 0;
		vector<int> res;
		for(i=A.size()-1;i>=0;i--){
			res.push_back( (int) (A[i] + aca) % 10 );
			aca = (A[i] + aca) / 10;
		}
		
		if(aca) res.push_back( aca );
		
		reverse( res.begin() , res.end() );
		i = 0;
		while(i<res.size() && !res[i]) i++;
		for(;i<res.size();i++)
			cout<<res[i];
		cout<<endl;
	}
	return 0;
} 
