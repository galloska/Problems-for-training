#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define pii pair<int,lli>

using namespace std;

typedef vector<int> Lista;

struct BIT{

	int N;
	vector<int> A;

	BIT(int N_) : N(N_) , A(N_) {}

	void update(int pos,int v){
		while(pos<N){
			A[pos] += v;
			pos += pos&(-pos);
		}
	}
	
	void update(int a,int b,int v){
		if(a>b) swap(a, b);
		update(a, v );
		update(b + 1, -v );
	}

	int query(int pos){
		int res = 0;

		while(pos>0){
			res += A[pos];
			pos -= pos&(-pos);
		}

		return res;
	}
};

struct HeavyLight{

    int n, conteo;
    Lista nivel, tamano, up;
    Lista indice, super, top;
    vector<Lista> aristas;
	vector<BIT> DS;

    HeavyLight(int N) : n(N), conteo(),
        top(N), nivel(N), tamano(N), up(N),
        indice(N), super(N), aristas(N) {}

    void AgregarArista(int u, int v) {
        aristas[u].push_back(v);
        aristas[v].push_back(u);
    }

    void CalcularNivel(int u, int p) {
        for (int i = 0; i < aristas[u].size(); ++i) {
            int v = aristas[u][i]; if (p == v) continue;
            if (super[u] == super[v]) nivel[v] = nivel[u];
            else nivel[v] = nivel[u] + 1;
            CalcularNivel(v, u);
        }
    }

    // Construir realiza todas las operaciones para
    // trabajar con Heavy-Light. Por defecto, la raiz del
    // arbol se establece como el nodo 0. Si quieren definir
    // una raiz diferente, llamen Construir(r) donde el
    // parametro r indica cual sera la raiz del arbol.

    int Construir(int u = 0, int p = -1) {
        int tam_subarbol = 0;
        up[u] = p, super[u] = -1;

        for (int i = 0; i < aristas[u].size(); ++i) {
            int v = aristas[u][i]; if (p == v) continue;
            tam_subarbol += Construir(v, u);
        }
        for (int i = 0; i < aristas[u].size(); ++i) {
            int v = aristas[u][i]; if (p == v) continue;
            if (tamano[v] > tam_subarbol / 2)
                indice[u] = indice[v] + 1,
                super[u] = super[v],
                top[super[v]] = u;
        }
        if (super[u] == -1) super[u] = conteo,
                            top[conteo++] = u;
        if (p == -1) CalcularNivel(u, p);
        return tamano[u] = tam_subarbol + 1;
    }

    int LCA(int u, int v) {
        if (nivel[v] > nivel[u]) swap(u, v);
        while (nivel[u] > nivel[v]) u = up[top[super[u]]];
        while (super[u] != super[v]) u = up[top[super[u]]],
                                     v = up[top[super[v]]];
        return (indice[u] > indice[v])? u: v;
    }

	//Creamos e iniciamos la Estructura de datos
	//Ejemplo : Aqui hacemos un BIT para manejar distancias
	void Iniciar(){
		for(int i=0;i<conteo;i++)
			DS.push_back(BIT( indice[ top[i] ] + 2 ));
	}

	void ActPath(int u, int raiz,int v){
		while(nivel[u]!=nivel[raiz]){
			int ini = indice[ top[ super[u] ] ] + 1;

			//Esta parte cambia dependiendo de la estructura de datos
			DS[super[u]].update( indice[u] + 1 , ini, v );
			//Esta parte cambia dependiendo de la estructura de datos

			u = up[ top[ super[u] ] ];
		}
		DS[ super[raiz] ].update( indice[u] + 1 , indice[raiz] + 1, v );
	}
	
	void ActPath(int u,int v){
		int raiz = LCA( u, v );
		ActPath(u, raiz, 1 );
		ActPath(v, raiz, 1 );
		ActPath(raiz, raiz, -1 );
	}

	int query(int u){
		return DS[super[u]].query( indice[u] + 1 );
	}
};

const int MAXLOG = 19;
const int MAXN = 200001;

lli num[MAXN];
int loga[MAXN];
int level[MAXN];
int parent[MAXN];
int dp[MAXN][MAXLOG];
lli len[MAXN][MAXLOG];
vector<int> lista[MAXN];

void bfs(int s,int n){
	queue<int> q;
	fill( level, level + n, 1e8 );
	level[s] = parent[s] = len[s][0] = 0;
	q.push(s);
	
	while(!q.empty()){
		int u = q.front();
		q.pop();
		
		for(int i=0;i<lista[u].size();i++){
			int v = lista[u][i];
			if(level[u]+1<level[v]){
				level[v] = level[u] + 1;
				parent[v] = u;
				q.push(v);
			}
		}
	}
}

void DP(int n){
	for(int i=0;i<n;i++)
		dp[i][0] = parent[i];
	
	for(int j=1;j<=loga[n];j++)
		for(int i=0;i<n;i++){
			dp[i][j] = dp[ dp[i][j-1] ][j-1];
			len[i][j] = len[i][j-1] + len[ dp[i][j-1] ][j-1];
		}
}

int query(int u,lli maxi,int n){
	lli l = 0ll;
	for(int i=loga[n];i>=0;i--)
		if(l + len[u][i]<=maxi){
			l += len[u][i];
			u = dp[u][i];
		}
	return u;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,a;
	lli b;
	for(int i=2;i<MAXN;i++)
		loga[i] = loga[i>>1] + 1;
	cin>>n;
	
	for(int i=0;i<n;i++)
		cin>>num[i];
	
	HeavyLight tree(n);
	for(int i=1;i<n;i++){
		cin>>a>>b;
		a--;
		len[i][0] = b;
		tree.AgregarArista( i , a );
		lista[i].push_back(a);
		lista[a].push_back(i);
	}
	tree.Construir();
	tree.Iniciar();
	
	bfs(0, n);
	DP(n);
	
	for(int i=0;i<n;i++){
		int v = query(i, num[i], n);
		tree.ActPath( i , v );
	}
	
	for(int i=0;i<n;i++)
		cout<<tree.query(i)-1<<" ";
	cout<<endl;
	return 0;
}