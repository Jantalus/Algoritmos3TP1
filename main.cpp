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
int INFINITO = 0;

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
        if(k+(S.size() -1 -i) <= K){
            return INFINITO;
        }
    }

    return(max(BT(i+1, r, k), BT(i+1, min(r - S[i], RS[i]), k+1)));
}


int PD(int n, int R){
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
    for(int j = 0; j < R+1 && n > 0; j++){
        if(matriz[n-1][j] > max) max = matriz[n-1][j];
    }

    return max;
}

/* int main(int argc, char** argv){
    map<string, string> algoritmosImplementados = {{"FB", "Fuerza Bruta"},{"BT", "Backtracking"},{"BT-F", "Backtracking con poda por factibilidad"}
    , {"BT-O", "Backtracking con poda por optimilidad"}};

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
    cout << (res == INFINITO? -1 : res) << endl;

} */
