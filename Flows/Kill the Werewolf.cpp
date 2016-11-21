#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

typedef int Dato; // Ajustable.
typedef vector<Dato> Vec;
typedef vector<Vec> Mat;
typedef vector<int> Lista;

const Dato INF = 1 << 30;

struct Flujo {

    int n;
    Lista padre;
    Mat cap, flujo;
    vector<Dato> dist;
    vector<Lista> aristas;

    Flujo(int N) : dist(N), padre(N), aristas(N),
        cap(N, Vec(N)), flujo(N, Vec(N)), n(N) {}

    void AgregarArista(int u, int v, Dato c) {
        flujo[v][u] += c; // Solo dirigidas!
        cap[u][v] += c, cap[v][u] += c;
        aristas[u].push_back(v);
        aristas[v].push_back(u);
    }

    // Flujo maximo mediante Dinic O(V^2E).

    Dato FlujoBloqueante(int u, int t, Dato f) {
        if (u == t) return f; Dato fluido = 0;
        for (int i = 0; i < aristas[u].size(); ++i) {
            if (fluido == f) break; int v = aristas[u][i];
            if (dist[u] + 1 > dist[v]) continue;
            Dato fv = FlujoBloqueante(v, t,
                min(f - fluido, cap[u][v] - flujo[u][v]));
            flujo[u][v] += fv, fluido += fv;
            flujo[v][u] -= fv;
        }
        return fluido;
    }

    Dato Dinic(int s, int t) {
        Dato flujo_maximo = dist[t] = 0;
        while (dist[t] < INF) {
            fill(dist.begin(), dist.end(), INF);
            queue<int> q; q.push(s); dist[s] = 0;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int i = 0; i < aristas[u].size(); ++i) {
                    int v = aristas[u][i];
                    if (flujo[u][v] == cap[u][v] ||
                        dist[v] <= dist[u] + 1) continue;
                    dist[v] = dist[u] + 1, q.push(v);
                }
            }
            if (dist[t] < INF) flujo_maximo +=
                FlujoBloqueante(s, t, INF);
        }
        return flujo_maximo;
    }
};

const int MAXN = 51;

int A[2][MAXN];
bool valid[MAXN];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>A[0][i]>>A[1][i];
		A[0][i]--;
		A[1][i]--;
	}
	
	int r = 0;
	for(int i=0;i<n;i++){
		Flujo graph(n + n + 2);
		fill( valid , valid + n , 1 );
		int cont = 0;
		valid[i] = 0;
		int total = n - 1;
		for(int j=0;j<n;j++)
			if(A[0][j]==i || A[1][j]==i){
				valid[j] = 0;
				cont++;
				total--;
			}
		if(cont<=1){
			r++;
			continue;
		}
		
		for(int j=0;j<n;j++)
			if(valid[j])
				graph.AgregarArista( n + n , j , 1 );

		for(int j=0;j<n;j++){
			if(!valid[j]) continue;
			graph.AgregarArista( j , A[0][j] + n , 1 );
			graph.AgregarArista( j , A[1][j] + n , 1 );
		}
		
		for(int j=0;j<n;j++){
			if(A[0][i]==j || A[1][i]==j)
				graph.AgregarArista( j + n , n + n + 1 , cont - 2 );
			else
				graph.AgregarArista( j + n , n + n + 1 , cont - 1 );
		}			
		int f = graph.Dinic(n + n, n + n + 1);
		if(f != total) r++;
	}

	cout<<r<<endl;
	return 0;
}
