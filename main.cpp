#include <iostream>
#include <vector>
#include "MinMatch.h"
#include "MatrixTransformer.h"

using namespace std;

int main() {
    int respuesta;
    int nDeImagenes = 0;
    vector<int> A;
    vector<int> B;
    vector< vector<int> > matrizA;
    vector< vector<int> > matrizB;
    srand(time(nullptr));

    do {
        cout << "Ingresar valores (1) o usar valores por defecto (2): ";
        cin >> respuesta;
    } while (respuesta < 1 || respuesta > 2);

    switch (respuesta) {
        case 1: {
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

            auto minMatch = new MinMatch(A, B);

            /// Pedirle al usuario que algoritmo quiere usar IMPROVED_DYNAMIC, DYNAMIC, GREEDY o PIXEL_BY_PIXEL
            do {
                cout << "Metodo greedy (1), dinamico (2), dinamico mejorado (3) o pixel por pixel (4): ";
                cin >> respuesta;
            } while (respuesta < 1 || respuesta > 3);

            /// Cambia las matrices por las imagenes.
            minMatch->lecturaDeImagen(_601, 125.0f, "bush.png", "arnold.png");

            do {
                cout << "Ingrese un numero de imagenes: ";
                cin >> nDeImagenes;
            } while (nDeImagenes < 1);

            switch (respuesta) {
                case 1:
                    minMatch->animacion(GREEDY, nDeImagenes);
                    break;
                case 2:
                    minMatch->animacion(DYNAMIC, nDeImagenes);
                    break;
                case 3:
                    minMatch->animacion(IMPROVED_DYNAMIC, nDeImagenes);
                    break;
                case 4:
                    minMatch->animacion(PIXEL_BY_PIXEL, nDeImagenes);
                    break;
                default:
                    break;
            }

            /// Demostracion de greedyMatriz(), dinamicoMatriz(), dinamicoMejorado()
            minMatch->greedyMatriz();
            minMatch->dinamicoMatriz();
            minMatch->dinamicoMejorado();

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

            /// Pedirle al usuario que algoritmo quiere usar IMPROVED_DYNAMIC, DYNAMIC, GREEDY o PIXEL_BY_PIXEL
            do {
                cout << "Metodo greedy (1), dinamico (2), dinamico mejorado (3) o pixel por pixel (4): ";
                cin >> respuesta;
            } while (respuesta < 1 || respuesta > 4);

            /// Cambia las matrices por las imagenes.
            minMatch->lecturaDeImagen(_601, 125.0f, "bush.png", "arnold.png");

            do {
                cout << "Ingrese un numero de imagenes: ";
                cin >> nDeImagenes;
            } while (nDeImagenes < 1);

            switch (respuesta) {
                case 1:
                    minMatch->animacion(GREEDY, nDeImagenes);
                    break;
                case 2:
                    minMatch->animacion(DYNAMIC, nDeImagenes);
                    break;
                case 3:
                    minMatch->animacion(IMPROVED_DYNAMIC, nDeImagenes);
                    break;
                case 4:
                    minMatch->animacion(PIXEL_BY_PIXEL, nDeImagenes);
                    break;
                default:
                    break;
            }

            /// Demostracion de greedyMatriz(), dinamicoMatriz(), dinamicoMejorado()
            minMatch->greedyMatriz();
            minMatch->dinamicoMatriz();
            minMatch->dinamicoMejorado();

            delete (minMatch);
        }
        default:
            break;
    }

    return 0;
}
