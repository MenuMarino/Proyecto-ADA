#include <iostream>
#include <vector>
#include "MinMatch.h"
#include "MatrixTransformer.h"

using namespace std;

int main() {
    int respuesta;
    vector<int> A;
    vector<int> B;
    vector< vector<int> > matrizA;
    vector< vector<int> > matrizB;
    srand(time(nullptr));

    do {
        cout << "Ingresar arrays y matrices (1) o usar arrays y matrices (2): ";
        cin >> respuesta;
    } while (respuesta < 1 || respuesta > 2);

    switch (respuesta) {
        case 1: {
            //TODO: Matrices
  			string a;
  			string b;

  			cout << "Ingrese el array A (0101010101): "; cin >> a;
  			cout << "Ingrese el array B (1101101101): "; cin >> b;

  			for (char i : a) {
  				if (i != '1' && i != '0') {
  					cout << "Valor invalido!" << endl;
  					exit(-1);
  				}

  				A.push_back( (int) i - 48);
  			}

  			for (char i : b) {
  				if (i != '1' && i != '0') {
                      cout << "Valor invalido!" << endl;
                      exit(-1);
                  }
  				B.push_back( (int) i - 48);
  			}

            ///Leer las matrices
            // TODO: Input de matrices?

            auto minMatch = new MinMatch(A, B/*matrizA, matrizB*/);
            /// Cambia las matrices por las imagenes.
            minMatch->lecturaDeImagen(_601, 125.0f, "bush.png", "arnold.png");
            minMatch->greedyMatriz();
            minMatch->dinamicoMatriz();

            delete (minMatch);
            break;
        }
        case 2: {
            ///Matrices
            matrizA = { {0,1,1,1}, {1,1,1,1}, {0,0,0,0}, {1,0,1,0} };
            matrizB = { {1,1,1,1}, {1,1,0,1}, {0,0,0,0}, {0,0,1,0} };

            ///Vectores
            A = {1,1,1,0,1,0,1,1,0,1,1,0,1,1,1,0,1,0,0};
            B = {0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,1,1,1,1};

            auto minMatch = new MinMatch(A, B, matrizA, matrizB);
            /// Cambia las matrices por las imagenes.
            minMatch->lecturaDeImagen(_601, 125.0f, "bush.png", "arnold.png");

            /// Pedirle al usuario que algoritmo quiere usar IMPROVED_DYNAMIC, DYNAMIC o GREEDY
            minMatch->animacion(IMPROVED_DYNAMIC, 4);

            /// Demostracion de greedyMatriz(), dinamicoMejorado(), dinamicoMatriz()
            // TODO: llamar a las funciones para demostrar su uso

            delete (minMatch);
        }
        default:
            break;
    }

    return 0;
}
