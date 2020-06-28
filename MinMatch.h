#ifndef PROYECTO_MINMATCH_H
#define PROYECTO_MINMATCH_H

#include <vector>
#include <limits>
#include <utility>
#include <algorithm>
#include <iterator>
#include <ctime>
#include <fstream>

using namespace std;

class MinMatch {
private:
    ///Vectores de 1s y 0s
    vector<int> A;
    vector<int> B;
    ///Vectores de pesos
    vector<float> pesosA;
    vector<float> pesosB;
    ///Matrices de 1s y 0s
    vector< vector<int> > matrizA;
    vector< vector<int> > matrizB;
    ///Matriz de pesos
    vector< vector<float> > pesosMA;
    vector< vector<float> > pesosMB;

    ///Matriz utilizadad por el algoritmo memoizado y el de programacion dinamica
    pair< vector< pair<int, int> > , float >** Matrix = nullptr;

public:

    ///Constructor
    MinMatch(const vector<int>& _A, const vector<int>& _B) {
        for (int i : _A) {
            A.push_back(i);
        }

        for (int i : _B) {
            B.push_back(i);
        }

        setPesos();
    }

    MinMatch(const vector< vector<int> >& _A, const vector< vector<int> >& _B) {
        matrizA.resize(_A.size());
        for (int i = 0; i < _A.size(); ++i) {
            matrizA[i].resize(_A[i].size());
            for (int j = 0; j < _A[i].size(); ++j) {
                matrizA[i][j] = _A[i][j];
            }
        }

        matrizB.resize(_B.size());
        for (int i = 0; i < _B.size(); ++i) {
            matrizB[i].resize(_B[i].size());
            for (int j = 0; j < _B[i].size(); ++j) {
                matrizB[i][j] = _B[i][j];
            }
        }

        setPesosM();

        for (auto & i : pesosMA) {
            for (float j : i) {
                cout << j << " ";
            }
            cout << endl;
        }

        cout << "Fin" << endl;

        for (auto & i : pesosMB) {
            for (float j : i) {
                cout << j << " ";
            }
            cout << endl;
        }

    }

    MinMatch(const vector<int>& _A, const vector<int>& _B, const vector< vector<int> >& __A, const vector< vector<int> >& __B) {
        for (int i : _A) {
            A.push_back(i);
        }

        for (int i : _B) {
            B.push_back(i);
        }

        matrizA.resize(__A.size());
        for (int i = 0; i < __A.size(); ++i) {
            matrizA[i].resize(__A[i].size());
            for (int j = 0; j < __A[i].size(); ++j) {
                matrizA[i][j] = __A[i][j];
            }
        }

        matrizB.resize(__B.size());
        for (int i = 0; i < __B.size(); ++i) {
            matrizB[i].resize(__B[i].size());
            for (int j = 0; j < __B[i].size(); ++j) {
                matrizB[i][j] = __B[i][j];
            }
        }

        setPesosM();
        setPesos();
    }

    ///Mascaras
    pair< vector< pair< vector<int>, vector<int> > >, float > greedy() {
        ///Medir tiempo
        unsigned t0, t1;

        ///Respuesta.first contiene el matching (en un vector de pairs), respuesta.second contiene el peso minimo.
        t0 = clock();
        pair< vector< pair< vector<int>, vector<int> > >, float > respuesta = algoritmoGreedy(pesosA, pesosB);
        t1 = clock();

        cout <<endl<< "Algoritmo greedy. Tiempo de ejecucion: " << (double(t1-t0)/CLOCKS_PER_SEC) << " segundos." << endl;
        cout << "El peso es: " << respuesta.second << "\nEl matching es: ";
        cout << endl << "__________________________" << endl;
        for(int i = 0; i< respuesta.first.size(); ++i){
            cout <<"C"<< i+1 << " Indices(s) en A': ";
            for(int j = 0; j < respuesta.first[i].first.size(); ++j){
                cout << respuesta.first[i].first[j] << " ";
            }
            cout << endl << endl;
            cout <<"C"<< i+1 << " Indices(s) en B': ";
            for(int k = 0; k < respuesta.first[i].second.size(); ++k){
                cout << respuesta.first[i].second[k] << " ";
            }
            cout << endl << "__________________________" << endl;
        }

        return respuesta;
    }

    pair< vector< pair<int, int> > , float > recursivo() {
        ///Medir tiempo
        unsigned t0, t1;

        ///Respuesta.first contiene el matching (en un vector de pairs), respuesta.second contiene el peso minimo.
        t0 = clock();
        pair< vector< pair<int, int> > , float > respuesta = algoritmoRecursivo(pesosA, pesosB);
        t1 = clock();

        cout << "Algoritmo recursivo. Tiempo de ejecucion: " << (double(t1-t0)/CLOCKS_PER_SEC) << " segundos." << endl;
        cout << "El peso es: " << respuesta.second << "\nEl matching es: " << endl;

        for (auto & i : respuesta.first) {
            cout << i.first << " " << i.second << " | ";
        }
        cout << endl;
        return respuesta;
    }

    pair< vector< pair<int, int> > , float > memoizado() {
        ///Medir tiempo
        unsigned t0, t1;

        ///Llenar la matriz de infinito
        Matrix = crearMatriz();

        ///Respuesta.first contiene el matching (en un vector de pairs), respuesta.second contiene el peso minimo.
        t0 = clock();
        pair< vector< pair<int, int> > , float > respuesta = algoritmoMemoizado(pesosA, pesosB);
        t1 = clock();

        cout << "\nAlgoritmo memoizado. Tiempo de ejecucion: " << (double(t1-t0)/CLOCKS_PER_SEC) << " segundos.";
        cout << "\nEl peso es: " << respuesta.second << "\nEl matching es: " << endl;

        for (auto & i : respuesta.first) {
            cout << i.first << " " << i.second << " | ";
        }
        cout << endl;

        ///Limpiar la matriz
        borrarMatriz();

        return respuesta;
    }

    pair< vector< pair<int, int> > , float > dinamico() {
        ///Medir tiempo
        unsigned t0, t1;

        ///Llenar la matriz de infinito
        Matrix = crearMatriz();

        ///Respuesta.first contiene el matching, respuesta.second contiene el peso minimo.
        t0 = clock();
        pair< vector< pair<int, int> > , float > respuesta = algoritmoDinamico(pesosA, pesosB);
        t1 = clock();

        cout << "\nAlgoritmo dinamico. Tiempo de ejecucion: " << (double(t1-t0)/CLOCKS_PER_SEC);
        cout << "\nEl peso es: " << respuesta.second << "\nEl matching es: " << endl;

        for (auto & i : respuesta.first) {
            cout << i.first << " " << i.second << " | ";
        }
        cout << endl;

        ///Limpiar la matriz
        borrarMatriz();

        return respuesta;
    }

    vector < pair< vector< pair<int, int> > , float > > dinamicoM() {
        ///Medir tiempo
        unsigned t0, t1;

        ///Llenar la matriz de infinito
        Matrix = crearMatriz();

        vector < pair< vector< pair<int, int> > , float > > Vrespuesta;
        pair< vector< pair<int, int> > , float > respuesta;

        ///Respuesta.first contiene el matching, respuesta.second contiene el peso minimo.
        t0 = clock();
        for (int i = 0; i < matrizA.size(); ++i) {
            Matrix = crearMatriz();
            respuesta = algoritmoDinamico(pesosMA[i], pesosMB[i]);
            Vrespuesta.push_back(respuesta);
        }
        t1 = clock();

        cout << "\nTransformacion dinamica. Tiempo de ejecucion: " << (double(t1-t0)/CLOCKS_PER_SEC);

        //TODO: Print bellaco
        float totalSum = 0;
        for (auto & i : Vrespuesta) {
            totalSum += i.second;
        }

        cout << "\nEl peso es: " << totalSum << "\nEl matching es: " << endl;

        for (int i = 0; i < Vrespuesta.size(); ++i) {
            for (int j = 0; j < Vrespuesta[i].first.size(); ++j) {
                cout << Vrespuesta[i].first[j].first << " " << Vrespuesta[i].first[j].second << " | ";
            }
            cout << "\n\n";
        }

        ///Limpiar la matriz
        borrarMatriz();

        return Vrespuesta;
    }

    //Destructor
    ~MinMatch()= default;

private:
    ///Metodos importantes
     pair< vector< pair< vector<int>, vector<int> > >, float > algoritmoGreedy(vector<float> a, vector<float> b){

        vector< pair< vector<int>, vector<int> > > R;
        vector<int> A_aux;
        vector<int> B_aux;
        int m = a.size();
        int n = b.size();
        int i = 0;
        int j = 0;
        pair< vector<int>, vector<int> > holder;
        float suma = 0.0;
        float valA = 0.0;
        float valB = 0.0;

        while( i < m-1 && j < n-1){
            if( a[i] == b[j] ){
                A_aux.push_back(i);
                valA = float(a[i]);

                B_aux.push_back(j);
                valB = float(a[j]);

                holder.first = A_aux;
                holder.second = B_aux;

                R.push_back( holder );
                suma += (valA / valB);
                i++;
                j++;
            } else if( a[i] > b[j]) {
                A_aux.push_back(i);
                valA = float(a[i]);

                while( (valA > valB)   && (j < n-1)){

                    B_aux.push_back(j);
                    valB += float(b[j]);
                    j++;
                }
                holder.first = A_aux;
                holder.second = B_aux;

                R.push_back( holder );
                suma += (valA / valB);
                i++;
            } else if( a[i] < b[j] ) {
                B_aux.push_back(j);
                valB = float(b[j]);

                while( (valB > valA ) && (i < m-1) ){
                    A_aux.push_back(i);
                    valA += float(a[i]) ;
                    i++;
                }

                holder.first = A_aux;
                holder.second = B_aux;

                R.push_back( holder );
                suma += (valA / valB);
                j++;
            }
            valA = 0;
            valB = 0;
            A_aux.clear();
            B_aux.clear();
        }

        while(i < m){
            A_aux.push_back(i);
            valA += float(a[i]);
            i++;
        }
        while(j < n){
            B_aux.push_back(j);
            valB += float(b[j]);
            j++;
        }

        holder.first = A_aux;
        holder.second = B_aux;

        R.push_back( holder );
        suma += ( valA / valB );

        pair< vector< pair< vector<int>, vector<int> > >, float > aux;

        aux.second = suma;
        aux.first = R;

        return aux;
    }
    
    ///El pair contiene el matching y el peso
    static pair< vector< pair<int, int> > , float > algoritmoRecursivo(vector<float> a, vector<float> b) {
        ///Variables para ayudar
        int n = a.size();
        int m = b.size();
        vector< pair<int, int> > match;
        float peso = 0;
        pair< vector< pair<int, int> > , float > respuesta;

        ///Casos base
        if (n == 1 && m == 1) {
            respuesta.first.emplace_back(0,0);
            respuesta.second = (float) a[0] / (float) b[0];
            return respuesta;
        }

        if (m == 1) {
            int tmpA = 0;
            for (int i = 0; i < n; ++i) {
                tmpA += a[i];
                respuesta.first.emplace_back(i,0);
            }
            respuesta.second = (float) tmpA / (float) b[0];
            return respuesta;
        }

        if (n == 1) {
            int tmpB = 0;
            for (int i = 0; i < m; ++i) {
                tmpB += b[i];
                respuesta.first.emplace_back(0,i);
            }
            respuesta.second = (float) a[0] / (float) tmpB;
            return respuesta;
        }
        ///Fin de casos base

        float min = std::numeric_limits<float>::max();

        ///El caso cuando el ultimo de A se va a dividir en bloques de B
        vector <float> auxA = a;
        vector <float> auxB = b;
        auxA.pop_back();
        for (int k = m-1; k >= 1; --k) {
            float auxDen = 0;
            vector<pair <int, int>> tmpA;

            for (int auxK = k; auxK < m; ++auxK) {
                //TODO: Matriz de sumas
                auxDen += b[auxK];
                tmpA.emplace_back(n-1, auxK);
            }

            float auxPeso = a[n-1]/auxDen;

            auxB.pop_back();
            auto aux = algoritmoRecursivo(auxA, auxB);

            if (aux.second + auxPeso < min) {
                for (auto & i : aux.first) {
                    tmpA.emplace_back(i.first, i.second);
                }
                respuesta.first.clear();
                for (auto & i : tmpA) {
                    respuesta.first.emplace_back(i.first, i.second);
                }
                min = aux.second + auxPeso;
            }
        }

        ///El caso cuando el ultimo de A se va a agrupar con otros bloques de A en el ultimo de B
        auxA = a;
        auxB = b;
        auxB.pop_back();
        for (int k = n-1; k >= 1; --k) {
            float auxNom = 0;
            vector<pair <int, int>> tmpB;

            for (int auxK = k; auxK < n; ++auxK) {
                auxNom += a[auxK];
                tmpB.emplace_back(auxK, m-1);
            }
            float auxPeso = auxNom / b[m-1];

            auxA.pop_back();
            auto aux = algoritmoRecursivo(auxA, auxB);

            if (aux.second + auxPeso < min) {
                for (auto & i : aux.first) {
                    tmpB.emplace_back(i.first, i.second);
                }
                respuesta.first.clear();
                for (auto & i : tmpB) {
                    respuesta.first.emplace_back(i.first, i.second);
                }
                min = aux.second + auxPeso;
            }
        }

        respuesta.second = min;
        return respuesta;
    }

    pair< vector< pair<int, int> > , float > algoritmoMemoizado(const vector<float>& a, const vector<float>& b) {
        int n = a.size();
        int m = b.size();
        vector< pair<int, int> > match;
        float peso = 0;
        pair< vector< pair<int, int> > , float > respuesta;
        float inf = std::numeric_limits<float>::max();

        ///Revisar si ya se calculo
        if (Matrix[n-1][m-1].second != inf)
            return Matrix[n-1][m-1];

        ///Casos base
        if (n == 1 && m == 1) {
            if (Matrix[0][0].second == inf) {
                respuesta.first.emplace_back(0, 0);
                respuesta.second = (float) a[0] / (float) b[0];
                Matrix[0][0] = respuesta;
            }
            return Matrix[0][0];
        }

        if (m == 1) {
            if (Matrix[n-1][0].second == inf) {
                int tmpA = 0;
                for (int i = 0; i < n; ++i) {
                    tmpA += a[i];
                    respuesta.first.emplace_back(i, 0);
                }
                respuesta.second = (float) tmpA / (float) b[0];
                Matrix[n-1][0] = respuesta;
            }
            return Matrix[n-1][0];
        }

        if (n == 1) {
            if (Matrix[0][m-1].second == inf) {
                int tmpB = 0;
                for (int i = 0; i < m; ++i) {
                    tmpB += b[i];
                    respuesta.first.emplace_back(0, i);
                }
                respuesta.second = (float) a[0] / (float) tmpB;
                Matrix[0][m-1] = respuesta;
            }
            return Matrix[0][m-1];
        }
        ///Fin de casos base

        float min = inf;

        ///El caso cuando el ultimo de A se va a dividir en bloques de B
        vector <float> auxA = a;
        vector <float> auxB = b;
        auxA.pop_back();
        for (int k = m - 1; k >= 1; --k) {
            float auxDen = 0;
            vector<pair <int, int>> tmpA;

            for (int auxK = k; auxK < m; ++auxK) {
                auxDen += b[auxK];
                tmpA.emplace_back(n-1, auxK);
            }

            float auxPeso = (float) a[n-1]/auxDen;

            auxB.pop_back();
            auto aux = algoritmoMemoizado(auxA, auxB);

            if (aux.second + auxPeso < min) {
                for (auto & i : aux.first) {
                    tmpA.emplace_back(i.first, i.second);
                }
                respuesta.first.clear();
                for (auto & i : tmpA) {
                    respuesta.first.emplace_back(i.first, i.second);
                }
                min = aux.second + auxPeso;
            }
        }

        ///El caso cuando el ultimo de A se va a agrupar con otros bloques de A en el ultimo de B
        auxA = a;
        auxB = b;
        auxB.pop_back();
        for (int k = n - 1; k >= 1; --k) {
            float auxNom = 0;
            vector<pair <int, int>> tmpB;

            for (int auxK = k; auxK < n; ++auxK) {
                auxNom += a[auxK];
                tmpB.emplace_back(auxK, m-1);
            }
            float auxPeso = auxNom / (float) b[m-1];

            auxA.pop_back();
            auto aux = algoritmoMemoizado(auxA, auxB);

            if (aux.second + auxPeso < min) {
                for (auto & i : aux.first) {
                    tmpB.emplace_back(i.first, i.second);
                }
                respuesta.first.clear();
                for (auto & i : tmpB) {
                    respuesta.first.emplace_back(i.first, i.second);
                }
                min = aux.second + auxPeso;
            }
        }

        respuesta.second = min;
        Matrix[n-1][m-1] = respuesta;
        return Matrix[n-1][m-1];
    }

    pair< vector< pair<int, int> > , float > algoritmoDinamico(const vector<float>& a, const vector<float>& b) {
        int n = a.size();
        int m = b.size();
        vector< pair<int, int> > match;
        float peso = 0;
        pair< vector< pair<int, int> > , float > respuesta;
        float inf = std::numeric_limits<float>::max();

        ///Llenar la matriz con los casos base
        Matrix[0][0].first.emplace_back(0, 0);
        Matrix[0][0].second = a[0] / b[0];


        ///Caso cuando j = 1
        vector< pair<int, int> > helper;
        helper.emplace_back(0,0);
        float pesoAux = a[0];
        for (int i = 1; i < n; ++i) {
            pesoAux += a[i];
            helper.emplace_back(i, 0);
            Matrix[i][0].first = helper;
            Matrix[i][0].second = pesoAux / b[0];
        }

        ///Caso cuando i = 1
        helper.clear();
        helper.emplace_back(0,0);
        pesoAux = b[0];
        for (int j = 1; j < m; ++j) {
            pesoAux += b[j];
            helper.emplace_back(0, j);
            Matrix[0][j].first = helper;
            Matrix[0][j].second = a[0] / pesoAux;
        }
        ///Fin de casos base


        float sum = 0;
        float weight = 0;
        float _min;
        helper.clear();
        vector< pair<int, int> > tmp;

        for (int i = 1; i < n; ++i) {
            for (int j = 1; j < m; ++j) {
                tmp.clear();
                _min = inf;
                helper.clear();

                ///El caso cuando A[i] se divide
                for (int k = j - 1; k >= 0; --k) {
                    sum = 0;
                    helper.clear();
                    for (int l = k + 1; l <= j; ++l) {
                        sum += b[l];
                        helper.emplace_back(i,l);
                    }
                    auto aux = Matrix[i-1][k];
                    weight = aux.second + (a[i] / sum);

                    if (weight < _min) {
                        tmp.clear();
                        for (auto & q : aux.first) {
                            tmp.emplace_back(q.first, q.second);
                        }
                        for (auto & q : helper) {
                            tmp.emplace_back(q.first, q.second);
                        }
                        _min = weight;
                    }
                }

                helper.clear();
                ///El caso cuando en B[i] se agrupa
                for (int k = i - 1; k >= 0; --k) {
                    sum = 0;
                    helper.clear();
                    for (int l = k + 1; l <= i; ++l) {
                        sum += a[l];
                        helper.emplace_back(l,j);
                    }
                    auto aux = Matrix[k][j-1];
                    weight = aux.second + (sum / b[j]);

                    if (weight < _min) {
                        tmp.clear();
                        for (auto & q : aux.first) {
                            tmp.emplace_back(q.first, q.second);
                        }
                        for (auto & q : helper) {
                            tmp.emplace_back(q.first, q.second);
                        }
                        _min = weight;
                    }
                }

                helper.clear();
                ///Conexion 1 a 1 (A[i] y B[i])
                auto aux = Matrix[i-1][j-1];
                weight = (a[i] / b[j]) + aux.second;
                if (weight < _min) {
                    tmp.clear();
                    for (auto & q : aux.first) {
                        tmp.emplace_back(q.first, q.second);
                    }
                    tmp.emplace_back(i, j);
                    _min = weight;
                }

                Matrix[i][j].first = tmp;
                Matrix[i][j].second = _min;
            }
        }
        return Matrix[n-1][m-1];
    }

    ///Metodos de apoyo
    void setPesos() {
        int temp = 0;
        bool enabled = false;
        int i;

        ///Contar los bloques de A
        for (i = 0; i < A.size(); ++i) {
            if (A[i] == 1) {
                enabled = true;
                ++temp;
                if (i == A.size() - 1) {
                    pesosA.push_back(temp);
                }

            } else if (enabled) {
                enabled = false;
                pesosA.push_back(temp);
                temp = 0;
            }
        }

        ///Contar los bloques de B
        enabled = false;
        temp = 0;
        for (i = 0; i < B.size(); ++i) {
            if (B[i] == 1) {
                enabled = true;
                ++temp;
                if (i == B.size() - 1) {
                    pesosB.push_back(temp);
                }

            } else if (enabled) {
                enabled = false;
                pesosB.push_back(temp);
                temp = 0;
            }
        }
    }

    void setPesosM(){
        int temp = 0;
        bool enabled = false;
        int i;

        ///Contar los bloques de A
        vector <float> tmpA;
        pesosMA.resize(matrizA.size());
        for (i = 0; i < matrizA.size(); ++i) {
            tmpA.clear();
            temp = 0;
            for (int j = 0; j < matrizA[i].size(); ++j) {
                if (matrizA[i][j] == 1) {
                    enabled = true;
                    ++temp;
                    if (j == matrizA[i].size() - 1) {
                        tmpA.push_back(temp);
                    }
                } else if (enabled) {
                    enabled = false;
                    tmpA.push_back(temp);
                    temp = 0;
                }
            }
            pesosMA[i].resize(tmpA.size());
            for (int x = 0; x < tmpA.size(); ++x) {
                pesosMA[i][x] = tmpA[x];
            }
        }

        ///Contar los bloques de B
        vector <float> tmpB;
        pesosMB.resize(matrizB.size());
        enabled = false;
        temp = 0;
        for (i = 0; i < matrizB.size(); ++i) {
            tmpB.clear();
            temp = 0;
            for (int j = 0; j < matrizB[i].size(); ++j) {
                if (matrizB[i][j] == 1) {
                    enabled = true;
                    ++temp;
                    if (j == matrizB.size() - 1) {
                        tmpB.push_back(temp);
                    }
                } else if (enabled) {
                    enabled = false;
                    tmpB.push_back(temp);
                    temp = 0;
                }
            }
            pesosMB[i].resize(tmpB.size());
            for (int x = 0; x < tmpB.size(); ++x) {
                pesosMB[i][x] = tmpB[x];
            }
        }
    }

    pair< vector< pair<int, int> > , float >** crearMatriz() {
        pair< vector< pair<int, int> > , float >** array2D = nullptr;
        int N = pesosA.size();
        int M = pesosB.size();
        float inf = std::numeric_limits<float>::max();

        ///Inicializar matriz de dimensiones N y M llena con infinito
        array2D = new pair< vector< pair<int, int> > , float >*[N];
        for (int i = 0; i < N; ++i) {
            array2D[i] = new pair< vector< pair<int, int> > , float >[M];
            for (int j = 0; j < M; ++j) {
                array2D[i][j].second = inf;
            }
        }

        return array2D;
    }

    void borrarMatriz() {
        ///Borrar la matriz para uso posterior
        for(int i = 0 ; i < pesosA.size() ; ++i){
            delete[] Matrix[i];
        }
        delete[] Matrix;
        Matrix = nullptr;
    }
};


class value;

#endif //PROYECTO_MINMATCH_H
