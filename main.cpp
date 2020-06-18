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
			string a;
			string b;

			cout << "Ingrese el array A (0101010101): "; cin >> a;
			cout << "Ingrese el array B (1101101101): "; cin >> b;
			
			for (int i = 0; i < a.length(); ++i) {
				if (a[i] != '1' && a[i] != '0') {
					cout << "Valor invalido!" << endl;
					exit(-1);
				}
					
				A.push_back( (int) a[i] - 48);
			}

			for (int i = 0; i < b.length(); ++i) {
				if (b[i] != '1' && b[i] != '0') {
                    cout << "Valor invalido!" << endl;
                    exit(-1);
                }
				B.push_back( (int) b[i] - 48);
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

            A = {1,1,1,0,1,0,1,1,0,1,1,0,1,1,1,0,1,0,0,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1};
            B = {0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0};

            auto minMatch = new MinMatch(A, B);
            ///Algoritmos
            minMatch->greedy();
            minMatch->recursivo();
            minMatch->memoizado();

            delete (minMatch);
        }
        default:
            break;
    }

    return 0;
}
