#include <iostream>
#include <vector>
#include "MinMatch.h"
#include "MatrixTransformer.h"

using namespace std;

int main() {

    MatrixTransformer matrixTransformer = MatrixTransformer(
            "/Users/gabrielspranger/Desktop/OpenCV/Pregunta8/yo-1.png",
            _709,
            128.0f
    );

    vector<vector<bool>> m = matrixTransformer.transform();

    matrixTransformer.print_transformed_img();

    matrixTransformer.show_image();

    int respuesta;
    vector<int> A;
    vector<int> B;
    vector< vector<int> > matrizA;
    vector< vector<int> > matrizB;

    do {
        cout << "Ingresar arrays y matrices (1) o usar arrays y matrices (2): ";
        cin >> respuesta;
    } while (respuesta < 1 || respuesta > 2);

    switch (respuesta) {
        //TODO: Input de matrices
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

            minMatch->greedy();
            minMatch->recursivo();
            minMatch->memoizado();
            minMatch->dinamico();

            delete (minMatch);
            break;
        }
        case 2: {
            ///Matrices
            matrizA = { {0,1,1,1}, {1,1,1,1}, {1,0,1,1}, {1,0,1,0} };
            matrizB = { {1,1,1,1}, {1,1,0,1}, {1,0,1,0}, {0,0,1,0} };

            ///Vectores
            A = {1,1,1,0,1,0,1,1,0,1,1,0,1,1,1,0,1,0,0};
            B = {0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,1,1,1,1};

            auto minMatch = new MinMatch(A, B, matrizA, matrizB);
            minMatch->greedyMatriz();
            /*
            ///Algoritmos
            minMatch->greedy();
            //minMatch->recursivo();
            minMatch->memoizado();
            minMatch->dinamico();
            */
            delete (minMatch);
        }
        default:
            break;
    }

    return 0;
}
