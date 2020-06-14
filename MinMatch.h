#ifndef PROYECTO_MINMATCH_H
#define PROYECTO_MINMATCH_H

#include <vector>
#include <limits>
#include <utility>
#include <algorithm>
#include <iterator>
#include <ctime>

using namespace std;

class MinMatch {
private:
    ///Vectores de 1s y 0s
    vector<int> A;
    vector<int> B;
    ///Vectores de pesos
    vector<float> pesosA;
    vector<float> pesosB;
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

        setPesosYRangos();
    }

    ///Mascaras
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

        cout << "\n\nAlgoritmo memoizado. Tiempo de ejecucion: " << (double(t1-t0)/CLOCKS_PER_SEC) << " segundos.";
        cout << "\nEl peso es: " << respuesta.second << "\nEl matching es: " << endl;

        for (auto & i : respuesta.first) {
            cout << i.first << " " << i.second << " | ";
        }

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

        cout << "\n\nAlgoritmo dinamico. Tiempo de ejecucion: " << (double(t1-t0)/CLOCKS_PER_SEC);
        cout << "\nEl peso es: " << respuesta.second << "\nEl matching es: " << endl;

        for (auto & i : respuesta.first) {
            cout << i.first << " " << i.second << " | ";
        }

        ///Limpiar la matriz
        borrarMatriz();

        return respuesta;
    }

    //Destructor
    ~MinMatch()= default;

private:
    ///Metodos importantes
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
        float pesoAux = pesosA[0];
        for (int i = 1; i < n; ++i) {
            pesoAux += pesosA[i];
            helper.emplace_back(i, 0);
            Matrix[i][0].first = helper;
            Matrix[i][0].second = pesoAux / pesosB[0];
        }

        ///Caso cuando i = 1
        helper.clear();
        helper.emplace_back(0,0);
        pesoAux = pesosB[0];
        for (int j = 1; j < m; ++j) {
            pesoAux += pesosB[j];
            helper.emplace_back(0, j);
            Matrix[0][j].first = helper;
            Matrix[0][j].second = pesosA[0] / pesoAux;
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
                        sum += pesosB[l];
                        helper.emplace_back(i,l);
                    }
                    auto aux = Matrix[i-1][k];
                    weight = aux.second + (pesosA[i] / sum);

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
                        sum += pesosA[l];
                        helper.emplace_back(l,j);
                    }
                    auto aux = Matrix[k][j-1];
                    weight = aux.second + (sum / pesosB[j]);

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
                weight = (pesosA[i] / pesosB[j]) + aux.second;
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
    void setPesosYRangos() {
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


#endif //PROYECTO_MINMATCH_H
