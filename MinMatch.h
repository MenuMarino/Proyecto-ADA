#ifndef PROYECTO_MINMATCH_H
#define PROYECTO_MINMATCH_H

#include <vector>
#include <limits>
#include <utility>
#include <algorithm>
#include <iterator>

using namespace std;

class MinMatch {
private:
    vector<int> A;
    vector<int> B;
    vector<int> pesosA;
    vector<int> pesosB;
    vector< pair<int, int> > rangosA;
    vector< pair<int, int> > rangosB;

public:

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
        ///Respuesta.first contiene el matching, respuesta.second contiene el peso minimo.
        pair< vector< pair<int, int> > , float > respuesta = algoritmoRecursivo(pesosA, pesosB);

        cout << "El peso es: " << respuesta.second << "\nEl matching es: " << endl;

        for (auto & i : respuesta.first) {
            cout << i.first << " " << i.second << endl;
        }

        return respuesta;
    }

    //Destructor
    ~MinMatch() = default;

private:
    ///Metodos importantes
    ///El pair contiene el matching y el peso
    static pair< vector< pair<int, int> > , float > algoritmoRecursivo(vector<int> a, vector<int> b) {
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

        vector <int> auxA = a;
        vector <int> auxB = b;
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

    ///Metodos de apoyo
    void setPesosYRangos() {
        int temp = 0;
        bool enabled = false;
        int i;
        int x, y;
        pair<int, int> aux;

        for (i = 0; i < A.size(); ++i) {
            if (A[i] == 1) {
                if (!enabled) {
                    x = i;
                }
                enabled = true;
                ++temp;
                if (i == A.size() - 1) {
                    pesosA.push_back(temp);
                    aux = make_pair(x, i);
                    rangosA.push_back(aux);
                }

            } else if (enabled) {
                y = i-1;
                enabled = false;
                pesosA.push_back(temp);
                temp = 0;
                aux = make_pair(x, y);
                rangosA.push_back(aux);
            }
        }

        enabled = false;
        temp = 0;
        for (i = 0; i < B.size(); ++i) {
            if (B[i] == 1) {
                if (!enabled) {
                    x = i;
                }
                enabled = true;
                ++temp;
                if (i == B.size() - 1) {
                    pesosB.push_back(temp);
                    aux = make_pair(x, i);
                    rangosB.push_back(aux);
                }

            } else if (enabled) {
                y = i-1;
                enabled = false;
                pesosB.push_back(temp);
                temp = 0;
                aux = make_pair(x, y);
                rangosB.push_back(aux);
            }
        }
    }
};


#endif //PROYECTO_MINMATCH_H
