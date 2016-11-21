#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int

using namespace std;

typedef long long Long;

const double ERROR = 1e-9;
const double M_2PI = 2 * M_PI;

bool Igual(double a, double b) { 
    return fabs(a - b) < ERROR;
}

struct Punto {
    double x, y;

    Punto() : x(), y() {}
    Punto(double X, double Y) : x(X), y(Y) {}

    bool operator<(const Punto& cmp) const {
        if (!Igual(x, cmp.x)) return x < cmp.x;
        return Igual(y, cmp.y)? false: y < cmp.y;
    }
 
    bool operator==(const Punto& cmp) const {
        return Igual(x, cmp.x) && Igual(y, cmp.y);
    } 
};

Punto Rotar(const Punto& p, double rad) {
    return Punto(p.x*cos(rad) - p.y*sin(rad),
                 p.x*sin(rad) + p.y*cos(rad));
}

double Cruz(const Punto& v, const Punto& w) {
    return v.x * w.y - v.y * w.x;
}

typedef vector<Punto> Poligono;

double Area(const Poligono& P) {
    double area = 0;
    for (int i = 1; i < P.size(); ++i)
        area += Cruz(P[i - 1], P[i]);
    return fabs(area) / 2.0;
}

const int MAXN = 100001;

double num[MAXN];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cout<<fixed<<setprecision(3);
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>num[i];
	
	sort( num , num + n );
	Poligono P;
	int j = 0, s = 1;
	double a = 0;
	for(int i=0;i<n;i++){
		Punto p = Rotar( Punto( 0.0 , num[j] ) , a );
		P.push_back(p);
		a += M_2PI / n;
		j += 2 * s;
		
		if (j>=n) {
			s = -1;
			if(!(n&1)) j--;
			else j -= 3;
		}
	}
	P.push_back( P[0] );
	
	cout<<Area(P)<<endl;
	return 0;
}
