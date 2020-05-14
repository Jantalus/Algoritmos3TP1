#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <set>
#include <map>

using namespace std;

bool poda_factibilidad = true; // define si la poda por factibilidad esta habilitada.
bool poda_optimalidad = true; // define si la poda por optimalidad esta habilitada.
int INFINITO = -1;

int n, R;
vector<int> S;
vector<int> RS;

// R resistencia del tubo, r minima resistencia restante acumulada, k cantidad de elementos guardados en el tubo, S cinta de elementos
// n cantidad de elementos en la cinta

int FB(int i, int r, int k){
    if(i == n){
        return (r < 0)? INFINITO:k;
    }
    return(max(FB(i+1, r, k), FB(i+1, min(r - S[i], RS[i]), k+1)));
}
int K = INFINITO;

int BT(int i, int r, int k){
    if(i == n){
        if(r < 0) return INFINITO;
        if(k > K) K = k;
        return K;//devuelvo el K grande
    }
    if(poda_factibilidad && r < 0){
        return INFINITO;
    }

    if(poda_optimalidad){
        int a = k+(S.size() -1 -i); int b = K;
        if(a <= b){
            return INFINITO;
        }
    }

    return(max(BT(i+1, r, k), BT(i+1, min(r - S[i], RS[i]), k+1)));
}

vector<vector<int>> M;
int PD(int i, int r){

    if(r < 0) return -1;
    if(i == n) return 0;

    int peso = S[i];int resistencia = RS[i];

    if(M[i][r] == INFINITO) M[i][r] = max(PD(i+1, r), 1 + PD(i+1, min(r - peso, resistencia)));

    return M[i][r];


/*    if(n == 0) return 0;

    int matriz[n][R+1];
    for (int i =0; i < n; i++){
        for(int j = 0; j < R+1; j++){
            matriz[i][j] = -1;
        }
    }

    matriz[0][R] = 0; matriz[0][min(RS[0] , R - S[0])] = 1;
    int r;
    for (int i =0; i < n-1; i++){
        for(int j = 0; j < R+1; j++){

            if(matriz[i][j] != -1){
               if(matriz[i][j] > matriz[i+1][j]) matriz[i+1][j] = matriz[i][j]; //NO LO AGREGO

               if((j - S[i+1]) >= 0){ //SI NO ME QUEDA RESISTENCIA PARA AGREGAR NO HAGO NADA
                   r = min(RS[i+1] , j - S[i+1]);
                   if(matriz[i][j] + 1 > matriz[i+1][r]) matriz[i+1][r] = matriz[i][j] +1 ;// LO AGREGO
               }
            }
        }
    }

    int max = 0;
    for(int j = 0; j < R+1; j++){
        if(matriz[n-1][j] > max) max = matriz[n-1][j];
    }
*/
}

int main(int argc, char** argv){
    map<string, string> algoritmosImplementados = {{"FB", "Fuerza Bruta"},{"BT", "Backtracking"},{"BT-F", "Backtracking con poda por factibilidad"}
    , {"BT-O", "Backtracking con poda por optimilidad"}, {"DP", "Programacion dinámica"}
    };

    if(argc < 2 || algoritmosImplementados.find(argv[1]) == algoritmosImplementados.end()){
        cerr << "Algoritmo no encontrado: " << argv[1] << endl;
        cerr << "Los algoritmos existentes son: " << endl;
        for (auto& alg_desc: algoritmosImplementados) cerr << "\t- " << alg_desc.first << ": " << alg_desc.second << endl;
        return 0;
    }
    string algoritmo = argv[1];

    cin >> n >> R;
    S.assign(n, 0); RS.assign(n, 0);
    for(int i = 0; i < n; i++){
        cin >> S[i];
        cin >> RS[i];
    }

    auto start = chrono::steady_clock::now();

    int res = INFINITO;
    if(algoritmo == "FB"){
        res = FB(0,R,0);
    }
    if(algoritmo == "BT"){
        poda_factibilidad = true;
        res = BT(0,R,0);
    }
    if(algoritmo == "BT-F"){
        poda_factibilidad = true;
        poda_optimalidad = false;
        res = BT(0,R,0);
    }
    if(algoritmo == "BT-O"){
        poda_factibilidad = false;
        poda_optimalidad = true;
        res = BT(0,R,0);
    }
    else if (algoritmo == "DP")
    {
        M = vector<vector<int>>(n, vector<int>(R+1, -1));

        res = PD(0,R);
    }

    auto end = chrono::steady_clock::now();
    double total_time = chrono::duration<double, milli>(end - start).count();

    // Imprimimos el tiempo de ejecución por stderr.
    clog << total_time << endl;

    cout << (res == INFINITO? -1 : res) << endl;

    return 0;
}
