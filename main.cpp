#include <iostream>
#include <vector>
#include "MinMatch.h"

using namespace std;

int main() {
    int respuesta;
    vector<int> A;
    vector<int> B;

    do {
        cout << "Ingresar arrays (1) o usar arrays (2): ";
        cin >> respuesta;
    } while (respuesta < 1 || respuesta > 2);

    switch (respuesta) {
        case 1: {
            int n, m, x;
            cout << "Ingresar tamaño de A: ";
            cin >> n;
            cout << "Ingresar tamaño de B: ";
            cin >> m;

            cout << "Array de A" << endl;
            for (int i = 0; i < n; ++i) {
                cin >> x;
                A.push_back(x);
            }

            cout << "Array de B" << endl;
            for (int i = 0; i < m; ++i) {
                cin >> x;
                A.push_back(x);
            }

            auto minMatch = new MinMatch(A, B);

            minMatch->greedy();
            minMatch->recursivo();
            minMatch->memoizado();

            delete (minMatch);
            break;
        }
        case 2: {
            ///Vectores
            /*
             *  awk '{gsub(/( )+/,",")}1' numbers.txt > numberscomma.txt
             *  Convierte el archivo numbers.txt (1 0 0 1 1 1 0 1 0) a
             *  numberscomma.txt (1,0,0,1,1,1,0,1,0)
             */

            A = {0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1,
                 1, 1,
                 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1};
            B = {0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1,
                 1, 1,
                 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1};

            auto minMatch = new MinMatch(A, B);
            ///Algoritmos
            minMatch->greedy();
            minMatch->recursivo();
            minMatch->memoizado();

            delete (minMatch);
        }
    }


    return 0;
}
